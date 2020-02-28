/* DE1: $Id: sys_network.c,v 1.20 2004/09/21 07:27:39 skyjake Exp $
 * Copyright (C) 2004 Jaakko Ker�nen <jaakko.keranen@iki.fi>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not: http://www.opensource.org/
 */

/*
 * sys_network.c: Low-Level Sockets Networking
 *
 * TCP sockets are periodically polled for activity (Net_Update ->
 * N_Listen).
 */

// HEADER FILES ------------------------------------------------------------

#ifdef MACOSX
#  include <SDL_net/SDL_net.h>
#else
#  include <SDL_net.h>
#endif

#include "de_base.h"
#include "de_network.h"
#include "de_console.h"
#include "de_system.h"
#include "de_misc.h"

// MACROS ------------------------------------------------------------------

/* The randomized transmitted is only used for simulating a poor
 * network connection. */
#undef TRANSMIT_RANDOMIZER
#define RANDOMIZER_DROP_PERCENT 1
#define RANDOMIZER_MAX_DELAY    500

/* Defining PRINT_PACKETS will cause the UDP transmitter and receiver
 * to print a message each time they send or receive a packet. */
#undef PRINT_PACKETS

#define MAX_NODES 			32
#define MAX_DATAGRAM_SIZE	1300

// TYPES -------------------------------------------------------------------

/*
 * Each network node has a send queue. The queue contains a number of
 * sqpacks.
 */
typedef struct sqpack_s {
	struct sqpack_s *next;
	struct netnode_s *node;
	UDPpacket *packet;
#ifdef TRANSMIT_RANDOMIZER
	// The packet won't be sent until this time.
	uint    dueTime;
#endif
} sqpack_t;

/*
 * On serverside, each client has its own network node. A node
 * represents the TCP connection between the client and the server. On
 * clientside, the node zero is used always.
 */
typedef struct netnode_s {
	TCPsocket sock;
	char    name[128];

	// The node is owned by a client in the game.  This becomes true
	// when the client issues the JOIN request.
	boolean hasJoined;

	// This is the UDP address that the client listens to.
	IPaddress addr;

	// Send queue statistics.
	int     mutex;
	uint    numWaiting;
	uint    bytesWaiting;
} netnode_t;

typedef struct sendqueue_s {
	semaphore_t waiting;
	int     mutex;
	sqpack_t *first, *last;
	boolean online;				// Set to false to make transmitter stop.
} sendqueue_t;

typedef struct foundhost_s {
	boolean valid;
	serverinfo_t info;
	IPaddress addr;
} foundhost_t;

// EXTERNAL FUNCTION PROTOTYPES --------------------------------------------

// PUBLIC FUNCTION PROTOTYPES ----------------------------------------------

void    N_IPToString(char *buf, IPaddress *ip);

// PRIVATE FUNCTION PROTOTYPES ---------------------------------------------

// EXTERNAL DATA DECLARATIONS ----------------------------------------------

// PUBLIC DATA DEFINITIONS -------------------------------------------------

uint    maxDatagramSize = MAX_DATAGRAM_SIZE;

char   *nptIPAddress = "";
int     nptIPPort = 0;			// This is the port *we* use to communicate.
int     nptUDPPort = 0;
int     defaultTCPPort = DEFAULT_TCP_PORT;
int     defaultUDPPort = DEFAULT_UDP_PORT;

// Operating mode of the currently active service provider.
boolean netIsActive = false;
boolean netServerMode = false;

// PRIVATE DATA DEFINITIONS ------------------------------------------------

static TCPsocket serverSock;
static volatile UDPsocket inSock;
static Uint16 recvUDPPort;
static int mutexInSock;
static netnode_t netNodes[MAX_NODES];
static SDLNet_SocketSet sockSet;
static int hReceiver, hTransmitter;
static sendqueue_t sendQ;
static foundhost_t located;
static volatile boolean stopReceiver;

// CODE --------------------------------------------------------------------

void N_Register(void)
{
	C_VAR_CHARPTR("net-ip-address", &nptIPAddress, 0, 0, 0,
				  "TCP/IP address for searching servers.");
	C_VAR_INT("net-ip-port", &nptIPPort, CVF_NO_MAX, 0, 0,
			  "TCP port to use for control connections.");
	C_VAR_INT("net-port-control", &nptIPPort, CVF_NO_MAX, 0, 0,
			  "TCP port to use for control connections.");
	C_VAR_INT("net-port-data", &nptUDPPort, CVF_NO_MAX, 0, 0,
			  "UDP port to use for client data traffic.");
}

/*
 * Free any packets still waiting in the queue.
 */
static void N_ClearQueue(sendqueue_t *q)
{
	sqpack_t *pack;

	while((pack = q->first) != NULL)
	{
		q->first = pack->next;
		SDLNet_FreePacket(pack->packet);
		free(pack);
	}
}

/*
 * Send the packet using UDP.  If the packet is associated with no
 * node, nothing will be sent because we don't know the destination
 * address.
 */
static void N_UDPSend(sqpack_t * pack)
{
	if(!pack->node)
		return;

#ifdef PRINT_PACKETS
	{
		char    buf[80];

		N_IPToString(buf, &pack->packet->address);
		printf("Send: len=%i to %s\n", pack->packet->len, buf);
	}
#endif

	if(pack->node->hasJoined)
	{
		// Commence sending.
		SDLNet_UDP_Send(inSock, -1, pack->packet);
	}

	// Update the node's counters.
	Sem_P(pack->node->mutex);
	pack->node->numWaiting--;
	pack->node->bytesWaiting -= pack->packet->len;
	Sem_V(pack->node->mutex);
}

#ifdef TRANSMIT_RANDOMIZER
/*
 * The randomized version of the UDP transmitter.  This can be used to
 * simulate a real-life connection where UDP packets are received
 * sometimes in the wrong order or get lost entirely.
 */
static int N_UDPTransmitter(void *parm)
{
	sendqueue_t *q = parm;
	sqpack_t *pack;
	uint    nowTime = 0;

	// When using the randomized transmitter, the send queue is always
	// sorted by the due times.

	while(q->online)
	{
		// If there are packets waiting, see if they should be sent now.
		Sem_P(q->mutex);

		nowTime = Sys_GetRealTime();

		while((pack = q->first) != NULL)
		{
			if(pack->dueTime > nowTime)
			{
				// Too early.
				break;
			}

			// Remove the packet from the queue.
			q->first = pack->next;

			N_UDPSend(pack);

			// Now that the packet has been sent, we can discard the data.
			SDLNet_FreePacket(pack->packet);
			free(pack);
		}

		Sem_V(q->mutex);

		// Sleep for a short while before starting another loop.
		Sys_Sleep(2);
	}

	N_ClearQueue(q);
	return 0;
}

#else							/* !TRANSMIT_RANDOMIZER */

/*
 * A UDP transmitter thread takes messages off a network node's send
 * queue and sends them one by one. On serverside, each client has its
 * own transmitter thread.
 *
 * 'parm' is a pointer to the network node of this transmitter.
 */
static int N_UDPTransmitter(void *parm)
{
	sendqueue_t *q = parm;
	sqpack_t *pack;

	while(q->online)
	{
		// We will wait until there are messages to send.  The
		// semaphore is incremented when a new message is added to the
		// queue.  Waiting for this semaphore causes us to sleep
		// until there are messages to send.
		Sem_P(q->waiting);

		// Lock the send queue.
		Sem_P(q->mutex);

		// There should be a message waiting.
		if(!q->online || !q->first)
		{
			Sem_V(q->mutex);
			continue;
		}

		// Extract the next message from the FIFO queue.
		pack = q->first;
		q->first = q->first->next;
		if(!q->first)
			q->last = NULL;

		// Release the send queue.
		Sem_V(q->mutex);

		N_UDPSend(pack);

		// Now that the packet has been sent, we can discard the data.
		SDLNet_FreePacket(pack->packet);
		free(pack);
	}

	// Free any packets still waiting in the queue.
	N_ClearQueue(q);
	return 0;
}
#endif

/*
 * The UDP receiver thread waits for UDP packets and places them into
 * the incoming message buffer. The UDP receiver is started when the
 * TCP/IP service is initialized. The thread is stopped when the
 * service is shut down.
 */
static int N_UDPReceiver(void *parm)
{
	SDLNet_SocketSet set;
	UDPpacket *packet = NULL;

	// Put the UDP socket in our socket set so we can wait for it.
	set = SDLNet_AllocSocketSet(1);
	SDLNet_UDP_AddSocket(set, inSock);

	while(!stopReceiver)
	{
		// Most of the time we will be sleeping here, waiting for
		// incoming packets.
		if(SDLNet_CheckSockets(set, 750) <= 0)
			continue;

		for(;;)
		{
			// There is activity on the socket. Allocate a new packet
			// to store the data into. The packet will be released later,
			// in N_ReturnBuffer.
			if(!packet)
			{
				// Allocate a new packet.
				packet = SDLNet_AllocPacket(maxDatagramSize);
			}

			// The mutex will prevent problems when new channels are
			// bound to the socket.
			Sys_Lock(mutexInSock);
			if(SDLNet_UDP_Recv(inSock, packet) > 0)
			{
				netmessage_t *msg = NULL;

				Sys_Unlock(mutexInSock);
#ifdef PRINT_PACKETS
				{
					char    buf[80];

					N_IPToString(buf, &packet->address);
					printf("Recv: ch=%i len=%i %s\n", packet->channel,
						   packet->len, buf);
				}
#endif

				// If we don't know the sender, discard the packet.
				if(packet->channel < 0)
					continue;

				// Successfully received a packet.
				msg = (netmessage_t *) calloc(sizeof(netmessage_t), 1);

				msg->sender = packet->channel;
				msg->data = packet->data;
				msg->size = packet->len;
				msg->handle = packet;

				// The message queue will handle the message from now on.
				N_PostMessage(msg);

				// This packet has now been used.
				packet = NULL;
			}
			else
			{
				Sys_Unlock(mutexInSock);
				break;
			}
		}
	}

	if(packet)
		SDLNet_FreePacket(packet);

	SDLNet_FreeSocketSet(set);
	return 0;
}

/*
 * Free a message buffer.
 */
void N_ReturnBuffer(void *handle)
{
	if(!handle)
		return;
	SDLNet_FreePacket(handle);
}

/*
 * Read a packet from the TCP connection and put it in the incoming
 * packet queue.  This function blocks until the entire packet has
 * been read, so large packets should be avoided during normal
 * gameplay.
 *
 * Returns true if a packet was successfully received.
 */
boolean N_ReceiveReliably(nodeid_t from)
{
	ushort  size = 0;
	TCPsocket sock = netNodes[from].sock;
	UDPpacket *packet = NULL;

	if(SDLNet_TCP_Recv(sock, &size, 2) != 2)
		return false;

	// Read the entire packet's data.
	packet = SDLNet_AllocPacket(size);
	if(SDLNet_TCP_Recv(sock, packet->data, size) == size)
	{
		netmessage_t *msg = calloc(sizeof(netmessage_t), 1);

		msg->sender = from;
		msg->data = packet->data;
		msg->size = size;
		msg->handle = packet;

		// The message queue will handle the message from now on.
		N_PostMessage(msg);
	}
	else
	{
		SDLNet_FreePacket(packet);
		return false;
	}

	return true;
}

/*
 * Send the data buffer over the control link, which is a TCP
 * connection.
 */
void N_SendDataBufferReliably(void *data, int size, nodeid_t destination)
{
	netnode_t *node = &netNodes[destination];
	ushort  packetSize = size;

	if(size <= 0 || !node->sock || !node->hasJoined)
		return;

	SDLNet_TCP_Send(node->sock, &packetSize, 2);
	SDLNet_TCP_Send(node->sock, data, packetSize);
}

/*
 * Send the buffer to the destination. For clients, the server is the
 * only possible destination (doesn't depend on the value of
 * 'destination').
 */
void N_SendDataBuffer(void *data, uint size, nodeid_t destination)
{
	sqpack_t *pack;
	UDPpacket *p;
	netnode_t *node;

	// If the send queue is not active, we can't send anything.
	if(!sendQ.online)
		return;

#ifdef TRANSMIT_RANDOMIZER
	// There is a chance that the packet is dropped.
	if(M_FRandom() < RANDOMIZER_DROP_PERCENT / 100.0)
	{
		Con_Message("N_SendDataBuffer: Randomizer dropped packet to %i "
					"(%i bytes).\n", destination, size);
		return;
	}
#endif

	//#ifdef _DEBUG
	if(size > maxDatagramSize)
	{
		Con_Error("N_SendDataBuffer: Too large packet (%i), risk of "
				  "fragmentation (MTU=%i).\n", size, maxDatagramSize);
	}
	//#endif

	// This memory is freed after the packet is sent.
	pack = malloc(sizeof(sqpack_t));
	p = pack->packet = SDLNet_AllocPacket(size);

	// The destination node.
	pack->node = node = netNodes + destination;

	// Init the packet's data.
	p->channel = -1;
	memcpy(p->data, data, size);
	p->len = size;
	memcpy(&p->address, &node->addr, sizeof(p->address));

#ifdef TRANSMIT_RANDOMIZER
	pack->dueTime = Sys_GetRealTime() + M_FRandom() * RANDOMIZER_MAX_DELAY;
#endif

	// Add the packet to the send queue.
	Sem_P(sendQ.mutex);
#ifndef TRANSMIT_RANDOMIZER
	if(!sendQ.first)
	{
		sendQ.first = sendQ.last = pack;
	}
	else
	{
		sendQ.last->next = pack;
		sendQ.last = pack;
	}
	pack->next = NULL;
#else
	// Insertion sort.
	if(sendQ.first)
	{
		// Does the new packet come before all others? 
		if(pack->dueTime < sendQ.first->dueTime)
		{
			pack->next = sendQ.first;
			sendQ.first = pack;
		}
		else
		{
			// Find the packet after which the new packet belongs.
			sqpack_t *i = sendQ.first;

			for(; i; i = i->next)
			{
				if(!i->next || i->next->dueTime >= pack->dueTime)
				{
					// Add after this one.
					pack->next = i->next;
					i->next = pack;
					break;
				}
			}
		}
	}
	else
	{
		sendQ.first = pack;
		pack->next = NULL;
	}
#endif
	Sem_V(sendQ.mutex);

	// Increment the statistics.
	Sem_P(node->mutex);
	node->numWaiting++;
	node->bytesWaiting += size;
	Sem_V(node->mutex);

	// Signal the transmitter to start working.
	Sem_V(sendQ.waiting);
}

/*
 * Returns the number of messages waiting in the player's send queue.
 */
uint N_GetSendQueueCount(int player)
{
	netnode_t *node = netNodes + player;
	uint    count;

	Sem_P(node->mutex);
	count = node->numWaiting;
	Sem_V(node->mutex);
	return count;
}

/*
 * Returns the number of bytes waiting in the player's send queue.
 */
uint N_GetSendQueueSize(int player)
{
	netnode_t *node = netNodes + player;
	uint    bytes;

	Sem_P(node->mutex);
	bytes = node->bytesWaiting;
	Sem_V(node->mutex);
	return bytes;
}

/*
 * Blocks until all the send queues have been emptied.
 */
void N_FlushOutgoing(void)
{
	int     i;
	boolean allClear = false;

	while(!allClear)
	{
		allClear = true;

		for(i = 0; i < DDMAXPLAYERS; i++)
			if(netNodes[i].hasJoined && N_GetSendQueueCount(i))
				allClear = false;

		Sys_Sleep(5);
	}
}

/*
 * Initialize the transmitter thread and the send queue.
 */
static void N_StartTransmitter(sendqueue_t *q)
{
	q->online = true;
	q->waiting = Sem_Create(0);
	q->mutex = Sem_Create(1);
	q->first = NULL;
	q->last = NULL;

	hTransmitter = Sys_StartThread(N_UDPTransmitter, q, 0);
}

/* 
 * Blocks until the transmitter thread has been exited.
 */
static void N_StopTransmitter(sendqueue_t *q)
{
	int     i;

	if(!hTransmitter)
		return;

	// Tell the transmitter to stop sending.
	q->online = false;

	// Increment the semaphore without adding a new message: this'll
	// make the transmitter "run dry."
	for(i = 0; i < 10; ++i)
		Sem_V(q->waiting);

	// Wait until the transmitter thread finishes.
	Sys_WaitThread(hTransmitter);
	hTransmitter = 0;

	// Destroy the semaphores.
	Sem_Destroy(q->waiting);
	Sem_Destroy(q->mutex);
}

/*
 * Start the UDP receiver thread.
 */
static void N_StartReceiver(void)
{
	stopReceiver = false;
	mutexInSock = Sys_CreateMutex("UDPIncomingMutex");
	hReceiver = Sys_StartThread(N_UDPReceiver, NULL, 0);
}

/*
 * Blocks until the UDP receiver thread has exited.
 */
static void N_StopReceiver(void)
{
	stopReceiver = true;

	// Close the incoming UDP socket.
	SDLNet_UDP_Close(inSock);

	// Wait for the receiver thread the stop.
	Sys_WaitThread(hReceiver);
	hReceiver = 0;

	inSock = NULL;

	Sys_DestroyMutex(mutexInSock);
	mutexInSock = 0;
}

/*
 * Bind or unbind the address to/from the incoming UDP socket.  When
 * the address is bound, packets from it will be accepted.
 */
void N_BindIncoming(IPaddress *addr, nodeid_t id)
{
	if(!inSock)
		return;

	Sys_Lock(mutexInSock);
	if(addr)
	{
		SDLNet_UDP_Bind(inSock, id, addr);
	}
	else
	{
		SDLNet_UDP_Unbind(inSock, id);
	}
	Sys_Unlock(mutexInSock);
}

/*  
 * Initialize the low-level network subsystem. This is called always 
 * during startup (via Sys_Init()).
 */
void N_SystemInit(void)
{
	// The MTU can be customized.
	if(ArgCheckWith("-mtu", 1))
	{
		maxDatagramSize = strtol(ArgNext(), NULL, 0);
		Con_Message("N_SystemInit: Custom MTU: %i bytes.\n", maxDatagramSize);
	}

	if(!SDLNet_Init())
	{
		VERBOSE(Con_Message("N_SystemInit: OK\n"));
	}
	else
	{
		Con_Message("N_SystemInit: %s\n", SDLNet_GetError());
	}
}

/*
 * Shut down the low-level network interface. Called during engine 
 * shutdown (not before).
 */
void N_SystemShutdown(void)
{
	N_ShutdownService();
	SDLNet_Quit();
}

/*
 * Convert an IPaddress to a string.
 */
void N_IPToString(char *buf, IPaddress *ip)
{
	uint    host = SDLNet_Read32(&ip->host);

	sprintf(buf, "%i.%i.%i.%i:%i", host >> 24, (host >> 16) & 0xff,
			(host >> 8) & 0xff, host & 0xff, SDLNet_Read16(&ip->port));
}

/* 
 * Opens an UDP socket.  The used port number is returned.  If the
 * socket cannot be opened, 'sock' is set to NULL.  'defaultPort'
 * should never be zero.
 */
Uint16 N_OpenUDPSocket(UDPsocket *sock, Uint16 preferPort, Uint16 defaultPort)
{
	Uint16  port = (!preferPort ? defaultPort : preferPort);
	int     tries = 1000;

	*sock = NULL;

	// Try opening the port, advance to next one if the opening fails.
	for(; tries > 0; tries--)
	{
		if((*sock = SDLNet_UDP_Open(port)) == NULL)
			port++;
		else
			return port;
	}
	// Failure!
	return 0;
}

/*
 * Initialize the chosen service provider each in server or client
 * mode.  If a service provider has already been initialized, it will
 * be shut down first.  Returns true if successful.
 */
boolean N_InitService(boolean inServerMode)
{
	IPaddress ip;
	Uint16  port;

	if(N_IsAvailable() && netServerMode == inServerMode)
	{
		// Nothing to change.
		return true;
	}

	// Get rid of the currently active service provider.
	N_ShutdownService();

	if(inServerMode)
	{
		port = (!nptIPPort ? defaultTCPPort : nptIPPort);

		Con_Message("N_InitService: Listening TCP socket on port %i.\n", port);

		// Open a listening TCP socket. It will accept client
		// connections.
		if(SDLNet_ResolveHost(&ip, NULL, port))
		{
			Con_Message("N_InitService: %s\n", SDLNet_GetError());
			return false;
		}
		if(!(serverSock = SDLNet_TCP_Open(&ip)))
		{
			Con_Message("N_InitService: %s\n", SDLNet_GetError());
			return false;
		}

		// Allocate a socket set, which we'll use for listening to the
		// client sockets.
		if(!(sockSet = SDLNet_AllocSocketSet(MAX_NODES)))
		{
			Con_Message("N_InitService: %s\n", SDLNet_GetError());
			return false;
		}
	}
	else
	{
		// Let's forget about servers found earlier.
		located.valid = false;
	}

	// Open the socket that will be used for UDP communications.
	recvUDPPort =
		N_OpenUDPSocket((UDPsocket *) &inSock, nptUDPPort, defaultUDPPort);
	Con_Message("N_InitService: In/out UDP port %i.\n", recvUDPPort);

	// Success.
	netIsActive = true;
	netServerMode = inServerMode;

	// Did we fail in opening the UDP port?
	if(!inSock)
	{
		Con_Message("N_InitService: Failed to open in/out UDP port.\n");
		Con_Message("  %s\n", SDLNet_GetError());
		N_ShutdownService();
		return false;
	}

	// Start the UDP receiver right away.
	N_StartReceiver();

	// Start the UDP transmitter.
	N_StartTransmitter(&sendQ);

	return true;
}

/*
 * Shut down the TCP/IP network services.
 */
void N_ShutdownService(void)
{
	int     i;

	if(!N_IsAvailable())
		return;					// Nothing to do.

	if(netgame)
	{
		// We seem to be shutting down while a netgame is running.
		Con_Execute(isServer ? "net server close" : "net disconnect", true);
	}

	// Any queued messages will be destroyed.
	N_ClearMessages();

	// Kill the transmission threads.
	N_StopTransmitter(&sendQ);
	N_StopReceiver();

	if(netServerMode)
	{
		// Close the listening socket.
		SDLNet_TCP_Close(serverSock);
		serverSock = NULL;

		// Clear the client nodes.
		for(i = 0; i < MAX_NODES; i++)
			N_TerminateNode(i);

		// Free the socket set.
		SDLNet_FreeSocketSet(sockSet);
		sockSet = NULL;
	}
	else
	{
		// Let's forget about servers found earlier.
		located.valid = false;
	}

	netIsActive = false;
	netServerMode = false;
}

/*
 * Returns true if the low-level network routines have been initialized
 * and are expected to be working.
 */
boolean N_IsAvailable(void)
{
	return netIsActive;
}

/*
 * Returns true if the internet is available.
 */
boolean N_UsingInternet(void)
{
	return netIsActive;
}

boolean N_GetHostInfo(int index, struct serverinfo_s *info)
{
	if(!located.valid || index != 0)
		return false;
	memcpy(info, &located.info, sizeof(*info));
	return true;
}

int N_GetHostCount(void)
{
	return located.valid ? 1 : 0;
}

const char *N_GetProtocolName(void)
{
	return "TCP/IP";
}

/*
 * Returns the player name associated with the given network node.
 */
boolean N_GetNodeName(nodeid_t id, char *name)
{
	if(!netNodes[id].sock)
	{
		strcpy(name, "-unknown-");
		return false;
	}
	strcpy(name, netNodes[id].name);
	return true;
}

/*
 * The client is removed from the game immediately. This is used when
 * the server needs to terminate a client's connection abnormally.
 */
void N_TerminateNode(nodeid_t id)
{
	netnode_t *node = &netNodes[id];
	netevent_t netEvent;
	sqpack_t *i;

	if(!node->sock)
		return;					// There is nothing here...

	if(netServerMode && node->hasJoined)
	{
		// This causes a network event.
		netEvent.type = NE_CLIENT_EXIT;
		netEvent.id = id;
		N_NEPost(&netEvent);
	}

	// Remove the node from the set of active sockets.
	SDLNet_TCP_DelSocket(sockSet, node->sock);

	// Close the socket and forget everything about the node.
	SDLNet_TCP_Close(node->sock);

	// Remove the address binding from the incoming UDP socket.  This
	// means we'll reject all packets from the address.
	N_BindIncoming(NULL, id);

	// Cancel this node's packets in the send queue by setting their
	// node pointers to NULL.
	Sem_P(sendQ.mutex);
	for(i = sendQ.first; i; i = i->next)
		if(i->node == node)
			i->node = NULL;
	Sem_V(sendQ.mutex);

	// Clear the node's data.
	Sem_Destroy(node->mutex);
	memset(node, 0, sizeof(*node));
}

/*
 * Registers a new TCP socket as a client node.  There can only be a
 * limited number of nodes at a time.  This is only used by a server.
 */
static boolean N_RegisterNewSocket(TCPsocket sock)
{
	int     i;
	netnode_t *node;

	// Find a free node.
	for(i = 1, node = netNodes + 1; i < MAX_NODES; i++, node++)
		if(!node->sock)
		{
			// This'll do.
			node->sock = sock;

			// We don't know the name yet.
			memset(node->name, 0, sizeof(node->name));

			// Add this socket to the set of client sockets.
			SDLNet_TCP_AddSocket(sockSet, sock);

			return true;
		}
	// There were no free nodes.
	return false;
}

/*
 * A network node wishes to become a real client. Returns true if we
 * allow this.
 */
static boolean N_JoinNode(nodeid_t id, Uint16 port, const char *name)
{
	netnode_t *node;
	netevent_t netEvent;
	IPaddress *ip;

	// If the server is full, attempts to connect are canceled.
	if(Sv_GetNumConnected() >= sv_maxPlayers)
		return false;

	node = &netNodes[id];

	// The UDP address where we should be sending data.
	if(!(ip = SDLNet_TCP_GetPeerAddress(node->sock)))
	{
		// This is a strange situation...
		return false;
	}
	memcpy(&node->addr, ip, sizeof(IPaddress));
	SDLNet_Write16(port, &node->addr.port);

	if(verbose)
	{
		char    buf[80];

		N_IPToString(buf, &node->addr);
		Con_Message("N_JoinNode: Node %i listens at %s (UDP).\n", id, buf);
	}

	// Convert the network node into a real client node.
	node->hasJoined = true;

	// FIXME: We should use more discretion with the name. It has
	// been provided by an untrusted source.
	strncpy(node->name, name, sizeof(node->name) - 1);

	// Prepare the transmission stats for the node.
	node->numWaiting = 0;
	node->bytesWaiting = 0;
	node->mutex = Sem_Create(1);

	// Bind the address to the incoming UDP socket, so we'll recognize
	// the sender.
	N_BindIncoming(&node->addr, id);

	// Inform the higher levels of this occurence.
	netEvent.type = NE_CLIENT_ENTRY;
	netEvent.id = id;
	N_NEPost(&netEvent);

	return true;
}

/*
 * Maybe it would be wisest to run this in a separate thread?
 */
boolean N_LookForHosts(const char *address, int port)
{
	TCPsocket sock;
	char    buf[256];
	ddstring_t *response;

	// We must be a client.
	if(!N_IsAvailable() || netServerMode)
		return false;

	if(!port)
		port = DEFAULT_TCP_PORT;

	// Get rid of previous findings.
	memset(&located, 0, sizeof(located));

	// Let's determine the address we will be looking into.
	SDLNet_ResolveHost(&located.addr, address, port);

	// I say, anyone there?
	sock = SDLNet_TCP_Open(&located.addr);
	if(!sock)
	{
		Con_Message("N_LookForHosts: No reply from %s (port %i).\n", address,
					port);
		return false;
	}

	// Send an INFO query.
	SDLNet_TCP_Send(sock, "INFO\n", 5);

	// Let's listen to the reply.
	memset(buf, 0, sizeof(buf));
	response = Str_New();
	while(!strstr(Str_Text(response), "END\n"))
	{
		int     result = SDLNet_TCP_Recv(sock, buf, sizeof(buf) - 1);

		if(result <= 0)
			break;				// Terminated?
		Str_Appendf(response, buf);
	}

	// Close the connection; that was all the information we need.
	SDLNet_TCP_Close(sock);

	// Did we receive what we expected to receive?
	if(strstr(Str_Text(response), "BEGIN\n"))
	{
		const char *ch;
		ddstring_t *line;

		located.valid = true;

		// Convert the string into a serverinfo_s.
		line = Str_New();
		ch = Str_Text(response);
		do
		{
			ch = Str_GetLine(line, ch);
			Sv_StringToInfo(Str_Text(line), &located.info);
		}
		while(*ch);
		Str_Delete(line);
		Str_Delete(response);

		// Show the information in the console.
		Con_Printf("%i server%s been found.\n", N_GetHostCount(),
				   N_GetHostCount() != 1 ? "s have" : " has");
		Net_PrintServerInfo(0, NULL);
		Net_PrintServerInfo(0, &located.info);
		return true;
	}
	else
	{
		Str_Delete(response);
		Con_Message("N_LookForHosts: Reply from %s (port %i) was invalid.\n",
					address, port);
		return false;
	}
}

/*
 * Connect a client to the server identified with 'index'.  We enter
 * clientside mode during this routine.
 */
boolean N_Connect(int index)
{
	netnode_t *svNode;
	foundhost_t *host;
	char    buf[128], *pName;

	if(!N_IsAvailable() || netServerMode || index != 0)
		return false;

	Demo_StopPlayback();

	// Call game DLL's NetConnect.
	gx.NetConnect(true);

	host = &located;

	// We'll use node number zero for all communications.
	svNode = &netNodes[0];
	if(!(svNode->sock = SDLNet_TCP_Open(&host->addr)))
	{
		N_IPToString(buf, &host->addr);
		Con_Message("N_Connect: No reply from %s.\n", buf);
		return false;
	}
	memcpy(&svNode->addr, &located.addr, sizeof(IPaddress));

	// Connect by issuing: "JOIN (my-udp) (myname)"
	pName = playerName;
	if(!pName || !pName[0])
		pName = "Anonymous";
	sprintf(buf, "JOIN %04x %s\n", recvUDPPort, pName);
	SDLNet_TCP_Send(svNode->sock, buf, strlen(buf));

	VERBOSE(Con_Printf("N_Connect: %s", buf));

	// What is the reply?
	memset(buf, 0, sizeof(buf));
	if(SDLNet_TCP_Recv(svNode->sock, buf, 64) <= 0 ||
	   strncmp(buf, "ENTER ", 6))
	{
		SDLNet_TCP_Close(svNode->sock);
		memset(svNode, 0, sizeof(svNode));
		Con_Message("N_Connect: Server refused connection.\n");
		if(buf[0])
			Con_Message("  Reply: %s", buf);
		return false;
	}

	VERBOSE(Con_Message("  Server responds: %s", buf));

	// The server tells us which UDP port we should send packets to.
	SDLNet_Write16(strtol(buf + 6, NULL, 16), &svNode->addr.port);

	// Bind the server's address to our incoming UDP port, so we'll
	// recognize the packets from the server.
	N_BindIncoming(&svNode->addr, 0);

	// Put the server's socket in a socket set so we may listen to it.
	sockSet = SDLNet_AllocSocketSet(1);
	SDLNet_TCP_AddSocket(sockSet, svNode->sock);

	// Clients are allowed to send packets to the server.
	svNode->hasJoined = true;

	allowSending = true;
	handshakeReceived = false;
	netgame = true;				// Allow sending/receiving of packets.
	isServer = false;
	isClient = true;

	// Call game's NetConnect.
	gx.NetConnect(false);

	// G'day mate!  The client is responsible for beginning the
	// handshake.
	Cl_SendHello();
	return true;
}

/*
 * Disconnect from the server.
 */
boolean N_Disconnect(void)
{
	netnode_t *svNode;

	if(!N_IsAvailable())
		return false;

	// Tell the Game that a disconnection is about to happen.
	if(gx.NetDisconnect)
		gx.NetDisconnect(true);

	Net_StopGame();
	N_ClearMessages();

	// Tell the Game that the disconnection is now complete.
	if(gx.NetDisconnect)
		gx.NetDisconnect(false);

	// This'll prevent the sending of further packets.
	svNode = &netNodes[0];
	svNode->hasJoined = false;
	N_BindIncoming(NULL, 0);

	// Close the control connection.  This will let the server know
	// that we are no more.
	SDLNet_TCP_Close(svNode->sock);

	SDLNet_FreeSocketSet(sockSet);
	sockSet = NULL;

	return true;
}

boolean N_ServerOpen(void)
{
	if(!N_IsAvailable())
		return false;

	Demo_StopPlayback();

	// Let's make sure the correct service provider is initialized
	// in server mode.
	if(!N_InitService(true))
	{
		Con_Message("N_ServerOpen: Failed to initialize server mode.\n");
		return false;
	}

	// The game module may have something that needs doing before we
	// actually begin.
	if(gx.NetServerStart)
		gx.NetServerStart(true);

	Sv_StartNetGame();

	// The game DLL might want to do something now that the
	// server is started.
	if(gx.NetServerStart)
		gx.NetServerStart(false);

	if(masterAware && N_UsingInternet())
	{
		// Let the master server know that we are running a public server.
		N_MasterAnnounceServer(true);
	}
	return true;
}

boolean N_ServerClose(void)
{
	if(!N_IsAvailable())
		return false;

	if(masterAware && N_UsingInternet())
	{
		// Bye-bye, master server.
		N_MAClear();
		N_MasterAnnounceServer(false);
	}
	if(gx.NetServerStop)
		gx.NetServerStop(true);
	Net_StopGame();

	// Exit server mode.
	N_InitService(false);

	if(gx.NetServerStop)
		gx.NetServerStop(false);
	return true;
}

/*
 * Validate and process the command, which has been sent by a remote
 * agent. Anyone is free to connect to a server using telnet and issue
 * queries.
 *
 * If the command is invalid, the node is immediately closed. We don't
 * have time to fool around with badly behaving clients.
 */
static boolean N_DoNodeCommand(nodeid_t node, const char *input, int length)
{
	char    command[80], *ch, buf[256];
	const char *in;
	TCPsocket sock = netNodes[node].sock;
	serverinfo_t info;
	ddstring_t msg;
	Uint16  port;

	// If the command is too long, it'll be considered invalid.
	if(length >= 80)
	{
		N_TerminateNode(node);
		return false;
	}

	// Make a copy of the command.
	memset(command, 0, sizeof(command));
	for(ch = command, in = input;
		*in && *in != '\r' && *in != '\n' && in - input < length;)
		*ch++ = *in++;

	//Con_Message("N_DoNodeCommand: %s\n", command);

	// Status query?
	if(!strcmp(command, "INFO"))
	{
		Sv_GetInfo(&info);
		Str_Init(&msg);
		Str_Appendf(&msg, "BEGIN\n");
		Sv_InfoToString(&info, &msg);
		Str_Appendf(&msg, "END\n");
		SDLNet_TCP_Send(sock, Str_Text(&msg), Str_Length(&msg));
		Str_Free(&msg);
	}
	else if(!strncmp(command, "JOIN ", 5) && length > 10)
	{
		// Which UDP port does the client use?
		memset(buf, 0, 5);
		strncpy(buf, command + 5, 4);
		port = strtol(buf, &ch, 16);
		if(*ch || !port)
		{
			N_TerminateNode(node);
			return false;
		}

		// Read the client's name and convert the network node into a
		// real client network node (which has a transmitter).
		if(N_JoinNode(node, port, command + 10))
		{
			// Successful! Send a reply.
			sprintf(buf, "ENTER %04x\n", recvUDPPort);
			SDLNet_TCP_Send(sock, buf, strlen(buf));
		}
		else
		{
			// Couldn't join the game, so close the connection.
			SDLNet_TCP_Send(sock, "BYE\n", 4);
			N_TerminateNode(node);
		}
	}
	else if(!strcmp(command, "TIME"))
	{
		sprintf(buf, "%.3f\n", Sys_GetSeconds());
		SDLNet_TCP_Send(sock, buf, strlen(buf));
	}
	else if(!strcmp(command, "BYE"))
	{
		// Request for the server to terminate the connection.
		N_TerminateNode(node);
	}
	else
	{
		// Too bad, scoundrel! Goodbye.
		SDLNet_TCP_Send(sock, "Huh?\n", 5);
		N_TerminateNode(node);
		return false;
	}

	// Everything was OK.
	return true;
}

/*
 * Poll all TCP sockets for activity.  Client commands are processed.
 * The logic ain't very pretty, but hopefully functional.
 */
void N_Listen(void)
{
	TCPsocket sock;
	int     i, result;
	char    buf[256];
	netnode_t *node;

	if(netServerMode)
	{
		// Any incoming connections on the listening socket?
		// FIXME: Include this in the set of sockets?
		while((sock = SDLNet_TCP_Accept(serverSock)) != NULL)
		{
			// A new client is attempting to connect. Let's try to
			// register the new socket as a network node.
			if(!N_RegisterNewSocket(sock))
			{
				// There was a failure, close the socket.
				SDLNet_TCP_Close(sock);
			}
		}

		// Any activity on the client sockets? (Don't wait.)
		if(SDLNet_CheckSockets(sockSet, 0) > 0)
		{
			for(i = 0; i < MAX_NODES; i++)
			{
				node = netNodes + i;

				// Does this socket have got any activity?
				if(!SDLNet_SocketReady(node->sock))
					continue;

				if(!node->hasJoined)
				{
					result = SDLNet_TCP_Recv(node->sock, buf, sizeof(buf));
					if(result <= 0)
					{
						// Close this socket & node.
						VERBOSE2(Con_Message
								 ("N_Listen: Connection closed on "
								  "node %i.\n", i));
						N_TerminateNode(i);
					}
					else
					{
						// FIXME: Read into a buffer, execute when newline
						// received.

						// Process the command; we will need to answer, or
						// do something else.
						N_DoNodeCommand(i, buf, result);
					}
				}
				else
				{
					if(!N_ReceiveReliably(i))
					{
						Con_Message("N_Listen: Connection closed on "
									"node %i.\n", i);
						N_TerminateNode(i);
					}
				}
			}
		}
	}
	else
	{
		// Clientside listening.  On clientside, the socket set only
		// includes the server's socket.
		if(sockSet && SDLNet_CheckSockets(sockSet, 0) > 0)
		{
			if(!N_ReceiveReliably(0))
			{
				netevent_t nev;

				nev.id = 0;
				nev.type = NE_END_CONNECTION;
				N_NEPost(&nev);
			}
		}
	}
}

/*
 * Called from "net info".
 */
void N_PrintInfo(void)
{
	// TODO: Print information about send queues, ports, etc.
}
