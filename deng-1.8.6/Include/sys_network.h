/* DE1: $Id: sys_network.h,v 1.16 2004/06/16 18:28:46 skyjake Exp $
 * Copyright (C) 2003, 2004 Jaakko Ker�nen <jaakko.keranen@iki.fi>
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
 * sys_network.h: Low-Level Network Services
 */

#ifndef __DOOMSDAY_SYSTEM_NETWORK_H__
#define __DOOMSDAY_SYSTEM_NETWORK_H__

#include "dd_share.h"
#include "net_buf.h"

#ifdef __cplusplus
extern          "C" {
#endif

#include "con_decl.h"

#define DEFAULT_TCP_PORT	13209
#define DEFAULT_UDP_PORT	13209

	// If a master action fails, the action queue is emptied.
	typedef enum {
		MAC_REQUEST,			   // Retrieve the list of servers from the master.
		MAC_WAIT,				   // Wait for the server list to arrive.
		MAC_LIST				   // Print the server list in the console.
	} masteraction_t;

	extern unsigned int maxDatagramSize;
	extern boolean  allowSending;
	extern int      maxQueuePackets;

	extern boolean  netServerMode;

	extern char    *nptIPAddress;
	extern int      nptIPPort;
	extern int      nptUDPPort;

	extern char    *serverName, *serverInfo, *playerName;
	extern int      serverData[];

	extern char    *masterAddress;
	extern int      masterPort;
	extern char    *masterPath;

	void            N_Register(void);
	void            N_SystemInit(void);
	void            N_SystemShutdown(void);
	boolean         N_InitService(boolean inServerMode);
	void            N_ShutdownService(void);
	boolean         N_IsAvailable(void);
	boolean         N_UsingInternet(void);
	void            N_PrintInfo(void);
	boolean         N_LookForHosts(const char *address, int port);
	void            N_Listen(void);

	boolean         N_Connect(int index);
	boolean         N_Disconnect(void);
	boolean         N_ServerOpen(void);
	boolean         N_ServerClose(void);

	void            N_SendDataBuffer(void *data, uint size,
									 nodeid_t destination);
	void            N_SendDataBufferReliably(void *data, int size,
											 nodeid_t destination);
	void            N_ReturnBuffer(void *handle);
	uint            N_GetSendQueueCount(int player);
	uint            N_GetSendQueueSize(int player);
	void            N_TerminateNode(nodeid_t id);
	void            N_FlushOutgoing(void);

	boolean         N_GetNodeName(nodeid_t id, char *name);
	const char     *N_GetProtocolName(void);

	int             N_GetHostCount(void);
	boolean         N_GetHostInfo(int index, struct serverinfo_s *info);

#ifdef __cplusplus
}
#endif
#endif
