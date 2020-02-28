/* DE1: $Id: ui_panel.c,v 1.27 2004/09/01 05:44:00 skyjake Exp $
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
 * ui_panel.c: Control Panel
 *
 * Doomsday Control Panel (opened with the "panel" command).
 * During netgames the game is NOT PAUSED while the UI is active.
 */

// HEADER FILES ------------------------------------------------------------

#include "de_base.h"
#include "de_console.h"
#include "de_graphics.h"
#include "de_ui.h"

#include "rend_main.h"

// MACROS ------------------------------------------------------------------

#define NUM_CP_BUTTONS	11
#define NUMITEMS(x)		(sizeof(x)/sizeof(uidata_listitem_t))
#define RES(x, y)		(x | (y<<16))
#define CPID_FRAME		(UIF_ID0 | UIF_ID1)
#define CPID_RES_X		UIF_ID0
#define CPID_RES_Y		UIF_ID1
#define CPID_SET_RES	UIF_ID2
#define CPID_RES_LIST	UIF_ID3
#define CPG_VIDEO		2
#define HELP_OFFSET		(screenWidth*290/1000)

// TYPES -------------------------------------------------------------------

typedef struct cvarbutton_s {
	char    active;
	const char *cvarname;
	const char *yes;
	const char *no;
} cvarbutton_t;

// EXTERNAL FUNCTION PROTOTYPES --------------------------------------------

// PUBLIC FUNCTION PROTOTYPES ----------------------------------------------

// PRIVATE FUNCTION PROTOTYPES ---------------------------------------------

void    CP_ClosePanel(ui_object_t *ob);
void    CP_ChooseGroup(ui_object_t *ob);
void    CP_DrawLogo(ui_object_t *ob);
void    CP_DrawBorder(ui_object_t *ob);
void    CP_CvarButton(ui_object_t *ob);
void    CP_CvarList(ui_object_t *ob);
void    CP_CvarEdit(ui_object_t *ob);
void    CP_CvarSlider(ui_object_t *ob);
int     CP_KeyGrabResponder(ui_object_t *ob, event_t *ev);
void    CP_KeyGrabDrawer(ui_object_t *ob);
void    CP_TexReset(ui_object_t *ob);
void    CP_QuickFOV(ui_object_t *ob);
void    CP_ResolutionInfo(ui_object_t *ob);
void    CP_ResolutionList(ui_object_t *ob);
void    CP_SetDefaultRes(ui_object_t *ob);
void    CP_SetRes(ui_object_t *ob);
void    CP_ResChanged(ui_object_t *ob);

// EXTERNAL DATA DECLARATIONS ----------------------------------------------

// PUBLIC DATA DEFINITIONS -------------------------------------------------

char    panel_buttons[NUM_CP_BUTTONS] = { true };	// The first is active.
char    panel_sv_password[100], panel_res_x[40], panel_res_y[40];
int     panel_help_active = false;
int     panel_help_offset = 0;	// Zero means the help is completely hidden.
int     panel_show_help = true;	// cvar
int     panel_show_tips = true;	// cvar
ui_object_t *panel_help_source;
void   *panel_help;

cvarbutton_t cvarbuttons[] = {
	{0, "con-progress"},
	{0, "con-var-silent"},
	{0, "con-dump"},
	{0, "con-key-show"},
	{0, "con-fps"},
	{0, "con-text-shadow"},
	{0, "ui-panel-help"},
	{0, "ui-panel-tips"},
	{0, "input-mouse-y-inverse"},
	{0, "input-mouse-x-disable"},
	{0, "input-mouse-y-disable"},
	{0, "input-mouse-filter"},
	{0, "input-joy"},
	{0, "input-key-show-scancodes"},
	{0, "net-nosleep"},
	{0, "net-dev"},
	{0, "net-queue-show"},
	{0, "sound-16bit"},
	{0, "sound-3d"},
	{0, "sound-info"},
	{0, "rend-particle"},
	{0, "rend-camera-smooth"},
	{0, "rend-mobj-smooth-turn"},
	{0, "rend-sprite-precache"},
	{0, "rend-sprite-noz"},
	{0, "rend-sprite-blend"},
	{0, "rend-sprite-lit"},
	{0, "rend-model"},
	{0, "rend-model-inter"},
	{0, "rend-model-precache"},
	{0, "rend-model-mirror-hud"},
	{0, "rend-model-shiny-multitex", "Shiny", "Shiny"},
	{0, "rend-tex"},
	{0, "rend-tex-filter-sprite"},
	{0, "rend-tex-filter-raw"},
	{0, "rend-tex-filter-smart"},
	{0, "rend-tex-detail"},
	{0, "rend-tex-detail-multitex", "Detail", "Detail"},
	{0, "rend-tex-anim-smooth"},
	{0, "rend-light"},
	{0, "rend-light-decor"},
	{0, "rend-light-multitex", "Lights", "Lights"},
	{0, "rend-halo-realistic"},
	{0, "rend-glow"},
	{0, "rend-glow-wall"},
	{0, "rend-info-tris"},
	{0, "rend-sky-full"},
	{0, "rend-shadow"},
	{0, "rend-fakeradio"},
	{0, 0}
};

uidata_listitem_t lstit_con_completion[] = {
	{"List with values", 0},
	{"Cycle through", 1}
};
uidata_list_t lst_con_completion = {
	lstit_con_completion, NUMITEMS(lstit_con_completion), "con-completion"
};

uidata_listitem_t lstit_music_source[] = {
	{"MUS lumps", 0},
	{"External files", 1},
	{"CD", 2}
};
uidata_list_t lst_music_source = {
	lstit_music_source, NUMITEMS(lstit_music_source), "music-source"
};

uidata_listitem_t lstit_sound_rate[] = {
	{"11025 Hz (1x)", 11025},
	{"22050 Hz (2x)", 22050},
	{"44100 Hz (4x)", 44100}
};
uidata_list_t lst_sound_rate = {
	lstit_sound_rate, NUMITEMS(lstit_sound_rate), "sound-rate"
};

uidata_listitem_t lstit_smooth_move[] = {
	{"Disabled", 0},
	{"Models only", 1},
	{"Models and sprites", 2}
};
uidata_list_t lst_smooth_move = {
	lstit_smooth_move, NUMITEMS(lstit_smooth_move), "rend-mobj-smooth-move"
};

uidata_listitem_t lstit_sprite_align[] = {
	{"Camera", 0},
	{"View plane", 1},
	{"Camera (limited)", 2},
	{"View plane (limited)", 3}
};
uidata_list_t lst_sprite_align = {
	lstit_sprite_align, NUMITEMS(lstit_sprite_align), "rend-sprite-align"
};

uidata_listitem_t lstit_mipmap[] = {
	{"No filter, no mip", 0},
	{"Linear filter, no mip", 1},
	{"No filter, near mip", 2},
	{"Linear filter, near mip", 3},
	{"No filter, linear mip", 4},
	{"Linear filter, linear mip", 5}
};
uidata_list_t lst_mipmap = {
	lstit_mipmap, NUMITEMS(lstit_mipmap), "rend-tex-mipmap"
};

uidata_listitem_t lstit_blend[] = {
	{"Multiply", 0},
	{"Add", 1},
	{"Process wo/rendering", 3}
};
uidata_list_t lst_blend = {
	lstit_blend, NUMITEMS(lstit_blend), "rend-light-blend"
};

uidata_listitem_t lstit_resolution[] = {
	{"320 x 240", RES(320, 240)},
	{"400 x 300", RES(400, 300)},
	{"512 x 384", RES(512, 384)},
	{"640 x 480", RES(640, 480)},
	{"800 x 600", RES(800, 600)},
	{"1024 x 768", RES(1024, 768)},
	{"1152 x 864", RES(1152, 864)},
	{"1280 x 960", RES(1280, 960)},
	{"1280 x 1024", RES(1280, 1024)},
	{"1600 x 1200", RES(1600, 1200)}
};
uidata_list_t lst_resolution = {
	lstit_resolution, NUMITEMS(lstit_resolution)
};

uidata_slider_t sld_con_alpha = { 0, 100, 0, 1, false, "con-alpha" };
uidata_slider_t sld_con_light = { 0, 100, 0, 1, false, "con-light" };
uidata_slider_t sld_joy_sensi = { 0, 9, 0, 1, false, "input-joy-sensi" };
uidata_slider_t sld_joy_dead = { 0, 90, 0, 1, false, "input-joy-deadzone" };
uidata_slider_t sld_keywait1 = { 50, 1000, 0, 1, false, "input-key-delay1" };
uidata_slider_t sld_keywait2 = { 20, 1000, 0, 1, false, "input-key-delay2" };
uidata_slider_t sld_client_pos_interval =
	{ 0, 70, 0, 1, false, "client-pos-interval" };
uidata_slider_t sld_server_frame_interval =
	{ 0, 35, 0, 1, false, "server-frame-interval" };
uidata_slider_t sld_sound_volume = { 0, 255, 0, 1, false, "sound-volume" };
uidata_slider_t sld_music_volume = { 0, 255, 0, 1, false, "music-volume" };
uidata_slider_t sld_reverb_volume =
	{ 0, 1, 0, .01f, true, "sound-reverb-volume" };
uidata_slider_t sld_particle_max =
	{ 0, 10000, 0, 10, false, "rend-particle-max", "Unlimited" };
uidata_slider_t sld_particle_rate =
	{ .1f, 10, 0, .01f, true, "rend-particle-rate" };
uidata_slider_t sld_particle_diffuse =
	{ 0, 20, 0, .01f, true, "rend-particle-diffuse" };
uidata_slider_t sld_particle_visnear =
	{ 0, 1000, 0, 1, false, "rend-particle-visible-near", "Disabled" };
uidata_slider_t sld_model_far =
	{ 0, 3000, 0, 1, false, "rend-model-distance", "Unlimited" };
uidata_slider_t sld_model_lights = { 0, 10, 0, 1, false, "rend-model-lights" };
uidata_slider_t sld_model_lod =
	{ 0, 1000, 0, 1, true, "rend-model-lod", "No LOD" };
uidata_slider_t sld_detail_scale =
	{ .1f, 32, 0, .01f, true, "rend-tex-detail-scale" };
uidata_slider_t sld_detail_strength =
	{ 0, 2, 0, .01f, true, "rend-tex-detail-strength" };
uidata_slider_t sld_detail_far =
	{ 1, 1000, 0, 1, true, "rend-tex-detail-far" };
uidata_slider_t sld_tex_quality = { 0, 8, 0, 1, false, "rend-tex-quality" };
uidata_slider_t sld_light_bright =
	{ 0, 1, 0, .01f, true, "rend-light-bright" };
uidata_slider_t sld_light_scale =
	{ .1f, 10, 0, .01f, true, "rend-light-radius-scale" };
uidata_slider_t sld_light_radmax =
	{ 64, 512, 0, 1, false, "rend-light-radius-max" };
uidata_slider_t sld_light_max =
	{ 0, 2000, 0, 1, false, "rend-light-num", "Unlimited" };
uidata_slider_t sld_light_fog_bright =
	{ 0, 1, 0, .01f, true, "rend-glow-fog-bright" };
uidata_slider_t sld_light_ambient =
	{ 0, 255, 0, 1, false, "rend-light-ambient" };
uidata_slider_t sld_glow_height = { 0, 1024, 0, 1, false, "rend-glow-height" };
uidata_slider_t sld_fov = { 1, 179, 0, .01f, true, "rend-camera-fov" };
uidata_slider_t sld_sky_distance =
	{ 1, 10000, 0, 10, true, "rend-sky-distance" };
uidata_slider_t sld_shadow_dark =
	{ 0, 1, 0, .01f, true, "rend-shadow-darkness" };
uidata_slider_t sld_shadow_far = { 0, 3000, 0, 1, false, "rend-shadow-far" };
uidata_slider_t sld_shadow_radmax =
	{ 0, 128, 0, 1, false, "rend-shadow-radius-max" };
uidata_slider_t sld_fakeradio_dark =
	{ 0, 2, 0, .01f, true, "rend-fakeradio-darkness" };
uidata_slider_t sld_vid_gamma = { .1f, 3, 0, .01f, true, "vid-gamma" };
uidata_slider_t sld_vid_contrast = { 0, 5, 0, .01f, true, "vid-contrast" };
uidata_slider_t sld_vid_bright = { -2, 2, 0, .01f, true, "vid-bright" };
uidata_slider_t sld_halo = { 0, 5, 0, 1, false, "rend-halo", "None" };
uidata_slider_t sld_halo_bright = { 0, 100, 0, 1, false, "rend-halo-bright" };
uidata_slider_t sld_halo_occlusion =
	{ 1, 256, 0, 1, false, "rend-halo-occlusion" };
uidata_slider_t sld_halo_size = { 0, 100, 0, 1, false, "rend-halo-size" };
uidata_slider_t sld_halo_seclimit =
	{ 0, 10, 0, .01f, true, "rend-halo-secondary-limit" };
uidata_slider_t sld_halo_dimfar =
	{ 0, 200, 0, .01f, true, "rend-halo-dim-far" };
uidata_slider_t sld_halo_dimnear =
	{ 0, 200, 0, .01f, true, "rend-halo-dim-near" };
uidata_slider_t sld_halo_zmagdiv =
	{ 1, 200, 0, .01f, true, "rend-halo-zmag-div" };
uidata_slider_t sld_halo_radmin =
	{ 1, 80, 0, .01f, true, "rend-halo-radius-min" };

uidata_edit_t ed_server_password =
	{ panel_sv_password, 100, "server-password" };
uidata_edit_t ed_res_x = { panel_res_x, 40 };
uidata_edit_t ed_res_y = { panel_res_y, 40 };

ui_page_t page_panel;

/* *INDENT-OFF* */
ui_object_t ob_panel[] =
{
	{ UI_BUTTON2,	1,	UIF_LEFT_ALIGN,	10, 210, 240, 60,	"Video",	UIButton_Drawer, UIButton_Responder, 0,				CP_ChooseGroup, &panel_buttons[0] },
	{ UI_BUTTON2,	1,	UIF_LEFT_ALIGN,	10, 275, 240, 60,	"Audio",	UIButton_Drawer, UIButton_Responder, 0,				CP_ChooseGroup, &panel_buttons[1] },
	{ UI_BUTTON2,	1,	UIF_LEFT_ALIGN,	10, 340, 240, 60,	"Input",	UIButton_Drawer, UIButton_Responder, 0,				CP_ChooseGroup, &panel_buttons[2] },
	{ UI_BUTTON2,	1,	UIF_LEFT_ALIGN,	10, 405, 240, 60,	"Graphics",	UIButton_Drawer, UIButton_Responder, 0,				CP_ChooseGroup, &panel_buttons[3] },
	{ UI_BUTTON2,	1,	UIF_LEFT_ALIGN,	40, 467, 210, 60,	"Lights",	UIButton_Drawer, UIButton_Responder, 0,				CP_ChooseGroup, &panel_buttons[4] },
	{ UI_BUTTON2,	1,	UIF_LEFT_ALIGN,	40, 529, 210, 60,	"Halos",	UIButton_Drawer, UIButton_Responder, 0,				CP_ChooseGroup, &panel_buttons[5] },
	{ UI_BUTTON2,	1,	UIF_LEFT_ALIGN,	40, 591, 210, 60,	"Textures",	UIButton_Drawer, UIButton_Responder, 0,				CP_ChooseGroup, &panel_buttons[6] },
	{ UI_BUTTON2,	1,	UIF_LEFT_ALIGN,	40, 653, 210, 60,	"Objects",	UIButton_Drawer, UIButton_Responder, 0,				CP_ChooseGroup, &panel_buttons[7] },
	{ UI_BUTTON2,	1,	UIF_LEFT_ALIGN,	40, 715, 210, 60,	"Particles", UIButton_Drawer, UIButton_Responder, 0,			CP_ChooseGroup, &panel_buttons[8] },
	{ UI_BUTTON2,	1,	UIF_LEFT_ALIGN,	10, 780, 240, 60,	"Network",	UIButton_Drawer, UIButton_Responder, 0,				CP_ChooseGroup, &panel_buttons[9] },
	{ UI_BUTTON2,	1,	UIF_LEFT_ALIGN,	10, 845, 240, 60,	"Console",	UIButton_Drawer, UIButton_Responder, 0,				CP_ChooseGroup, &panel_buttons[10] },
	{ UI_BUTTON,	0,	0,				10, 940, 240, 60,	"Close Panel (Esc)", UIButton_Drawer, UIButton_Responder, 0,	CP_ClosePanel },
	{ UI_BOX,		0,	0,				8, -20, 250, 250,	"",			CP_DrawLogo },
	{ UI_BOX,		0,	CPID_FRAME,		280, 55, 720, 945,	"",			CP_DrawBorder },

	{ UI_META,		2 },
	{ UI_TEXT,		0,	0,				280, 0, 0, 50,		"Video Options", UIText_Drawer },
	{ UI_TEXT,		0,	0,				300, 70, 0, 55,		"Gamma correction", UIText_Drawer },
	{ UI_SLIDER,	0,	0,				680, 70, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_vid_gamma },
	{ UI_TEXT,		0,	0,				300, 130, 0, 55,	"Display contrast", UIText_Drawer },
	{ UI_SLIDER,	0,	0,				680, 130, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_vid_contrast },
	{ UI_TEXT,		0,	0,				300, 190, 0, 55,	"Display brightness", UIText_Drawer },
	{ UI_SLIDER,	0,	0,				680, 190, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_vid_bright },
	{ UI_LIST,		0,	CPID_RES_LIST,	680, 250, 300, 175,	"",			UIList_Drawer, UIList_Responder, UIList_Ticker, CP_ResolutionList, &lst_resolution },
	{ UI_TEXT,		0,	0,				300, 430, 0, 55,	"Horizontal resolution", UIText_Drawer },
	{ UI_EDIT,		0,	CPID_RES_X,		680, 430, 100, 55,	"",			UIEdit_Drawer, UIEdit_Responder, 0, CP_ResChanged, &ed_res_x },
	{ UI_TEXT,		0,	0,				300, 490, 0, 55,	"Vertical resolution", UIText_Drawer },
	{ UI_EDIT,		0,	CPID_RES_Y,		680, 490, 100, 55,	"",			UIEdit_Drawer, UIEdit_Responder, 0, CP_ResChanged, &ed_res_y },
	{ UI_TEXT,		0,	0,				300, 550, 0, 55,	"Default resolution", UIText_Drawer },
	{ UI_BOX,		0,	0,				680, 550, 0, 55,	"default",	CP_ResolutionInfo },
	{ UI_BUTTON,	0,	0,				680, 610, 170, 60,	"Set Default", UIButton_Drawer, UIButton_Responder, 0, CP_SetDefaultRes },
	{ UI_BUTTON,	0,	CPID_SET_RES,	680, 910, 300, 60,	"",			UIButton_Drawer, UIButton_Responder, 0, CP_SetRes },
	{ UI_BOX,		0,	0,				300, 910, 0, 60,	"",			CP_ResolutionInfo },

	{ UI_META,		3 },
	{ UI_TEXT,		0,	0,				280, 0, 0, 50,		"Audio Options", UIText_Drawer },
	{ UI_TEXT,		0,	0,				300, 70, 0, 55,		"Sound volume", UIText_Drawer },
	{ UI_SLIDER,	0,	0,				680, 70, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_sound_volume },
	{ UI_TEXT,		0,	0,				300, 130, 0, 55,	"Music volume", UIText_Drawer },
	{ UI_SLIDER,	0,	0,				680, 130, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_music_volume },
	{ UI_TEXT,		0,	0,				300, 190, 0, 55,	"Preferred music source", UIText_Drawer },
	{ UI_LIST,		0,	0,				680, 190, 300, 150,	"",			UIList_Drawer, UIList_Responder, UIList_Ticker, CP_CvarList, &lst_music_source },
	{ UI_TEXT,		0,	0,				300, 345, 0, 55,	"16-bit sound effects", UIText_Drawer },
	{ UI_BUTTON2,	0,	0,				680, 345, 70, 55,	"sound-16bit", UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },
	{ UI_TEXT,		0,	0,				300, 405, 0, 55,	"Sound effects sample rate", UIText_Drawer },
	{ UI_LIST,		0,	0,				680, 405, 300, 150,	"",			UIList_Drawer, UIList_Responder, UIList_Ticker, CP_CvarList, &lst_sound_rate },
	{ UI_TEXT,		0,	0,				300, 560, 0, 55,	"3D sounds", UIText_Drawer },
	{ UI_BUTTON2,	0,	0,				680, 560, 70, 55,	"sound-3d", UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },
	{ UI_TEXT,		0,	0,				300, 620, 0, 55,	"General reverb strength", UIText_Drawer },
	{ UI_SLIDER,	0,	0,				680, 620, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_reverb_volume },
	{ UI_TEXT,		0,	0,				300, 680, 0, 55,	"Show status of channels", UIText_Drawer },
	{ UI_BUTTON2,	0,	0,				680, 680, 70, 55,	"sound-info", UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },

	{ UI_META,		4 },
	{ UI_TEXT,		0,	0,				280, 0, 0, 50,		"Input Options", UIText_Drawer },
	{ UI_TEXT,		0,	0,				300, 70, 0, 55,		"Invert mouse Y axis", UIText_Drawer },
	{ UI_BUTTON2,	0,	0,				680, 70, 70, 55,	"input-mouse-y-inverse", UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },
	{ UI_META,		4,	0,				0, 60 },
	{ UI_TEXT,		0,	0,				300, 70, 0, 55,		"Filter mouse movement", UIText_Drawer },
	{ UI_BUTTON2,	0,	0,				680, 70, 70, 55,	"input-mouse-filter", UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },
	{ UI_TEXT,		0,	0,				300, 130, 0, 55,	"Disable mouse X axis", UIText_Drawer },
	{ UI_BUTTON2,	0,	0,				680, 130, 70, 55,	"input-mouse-x-disable", UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },
	{ UI_TEXT,		0,	0,				300, 190, 0, 55,	"Disable mouse Y axis", UIText_Drawer },
	{ UI_BUTTON2,	0,	0,				680, 190, 70, 55,	"input-mouse-y-disable", UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },
	{ UI_TEXT,		0,	0,				300, 250, 0, 55,	"Enable joystick", UIText_Drawer },
	{ UI_BUTTON2,	0,	0,				680, 250, 70, 55,	"input-joy", UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },
	{ UI_TEXT,		0,	0,				300, 310, 0, 55,	"Joystick sensitivity", UIText_Drawer },
	{ UI_SLIDER,	0,	0,				680, 310, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_joy_sensi },
	{ UI_TEXT,		0,	0,				300, 370, 0, 55,	"Joystick dead zone (%)", UIText_Drawer },
	{ UI_SLIDER,	0,	0,				680, 370, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_joy_dead },
	{ UI_TEXT,		0,	0,				300, 430, 0, 55,	"Key repeat delay (ms)", UIText_Drawer },
	{ UI_SLIDER,	0,	0,				680, 430, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_keywait1 },
	{ UI_TEXT,		0,	0,				300, 490, 0, 55,	"Key repeat rate (ms)", UIText_Drawer },
	{ UI_SLIDER,	0,	0,				680, 490, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_keywait2 },
	{ UI_TEXT,		0,	0,				300, 550, 0, 55,	"Print scancodes of pressed keys", UIText_Drawer },
	{ UI_BUTTON2,	0,	0,				680, 550, 70, 55,	"input-key-show-scancodes", UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },

	{ UI_META,		5 },
	{ UI_TEXT,		0,	0,				280, 0, 0, 50,		"Graphics Options", UIText_Drawer },
	{ UI_META,		5,  0,				0, -60 },
//	{ UI_TEXT,		0,	0,				300, 70, 0, 55,		"Smooth camera movement", UIText_Drawer },
//	{ UI_BUTTON2,	0,	0,				680, 70, 70, 55,	"rend-camera-smooth", UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },
	{ UI_TEXT,		0,	0,				300, 130, 0, 55,	"Field Of View angle", UIText_Drawer },
	{ UI_SLIDER,	0,	0,				680, 130, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_fov },
	{ UI_BUTTON,	0,	0,				680, 190, 70, 60,	"90",		UIButton_Drawer, UIButton_Responder, 0, CP_QuickFOV },
	{ UI_BUTTON,	0,	0,				755, 190, 70, 60,	"95",		UIButton_Drawer, UIButton_Responder, 0, CP_QuickFOV },
	{ UI_BUTTON,	0,	0,				830, 190, 70, 60,	"100",		UIButton_Drawer, UIButton_Responder, 0, CP_QuickFOV },
	{ UI_BUTTON,	0,	0,				905, 190, 70, 60,	"110",		UIButton_Drawer, UIButton_Responder, 0, CP_QuickFOV },
	{ UI_TEXT,		0,	0,				300, 255, 0, 55,	"Mirror player weapon models", UIText_Drawer },
	{ UI_BUTTON2,	0,	0,				680, 255, 70, 55,	"rend-model-mirror-hud", UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },
	{ UI_META,		5,	0,				0, 60 },	
	{ UI_TEXT,		0,	0,				300, 255, 0, 55,	"Sky sphere radius", UIText_Drawer },
	{ UI_SLIDER,	0,	0,				680, 255, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_sky_distance },
	{ UI_TEXT,		0,	0,				300, 315, 0, 55,	"Always render full sky", UIText_Drawer },
	{ UI_BUTTON2,	0,	0,				680, 315, 70, 55,	"rend-sky-full", UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },
	{ UI_TEXT,		0,	0,				300, 375, 0, 55,	"Objects cast shadows", UIText_Drawer },
	{ UI_BUTTON2,	0,	0,				680, 375, 70, 55,	"rend-shadow", UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },
	{ UI_TEXT,		0,	0,				300, 435, 0, 55,	"Shadow darkness factor", UIText_Drawer },
	{ UI_SLIDER,	0,	0,				680, 435, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_shadow_dark },
	{ UI_TEXT,		0,	0,				300, 495, 0, 55,	"Shadow visible distance", UIText_Drawer },
	{ UI_SLIDER,	0,	0,				680, 495, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_shadow_far },
	{ UI_TEXT,		0,	0,				300, 555, 0, 55,	"Maximum shadow radius", UIText_Drawer },
	{ UI_SLIDER,	0,	0,				680, 555, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_shadow_radmax },
	{ UI_TEXT,		0,	0,				300, 615, 0, 55,	"Simulate radiosity", UIText_Drawer },
	{ UI_BUTTON2,	0,	0,				680, 615, 70, 55,	"rend-fakeradio", UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },
	{ UI_TEXT,		0,	0,				300, 675, 0, 55,	"Radiosity shadow darkness", UIText_Drawer },
	{ UI_SLIDER,	0,	0,				680, 675, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_fakeradio_dark },
	
	{ UI_META,		6 },
	{ UI_TEXT,		0,	0,				280, 0, 0, 50,		"Graphics Options: Lights", UIText_Drawer },
	{ UI_TEXT,		0,	0,				300, 70, 0, 55,		"Enable dynamic lights", UIText_Drawer },
	{ UI_BUTTON2,	0,	0,				680, 70, 70, 55,	"rend-light", UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },
	{ UI_TEXT,		0,	0,				300, 130, 0, 55,	"Blending mode", UIText_Drawer },
	{ UI_LIST,		0,	0,				680, 130, 300, 115,	"",			UIList_Drawer, UIList_Responder, UIList_Ticker, CP_CvarList, &lst_blend },
	{ UI_TEXT,		0,	0,				300, 250, 0, 55,	"Dynamic light brightness", UIText_Drawer },
	{ UI_SLIDER,	0,	0,				680, 250, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_light_bright },
	{ UI_TEXT,		0,	0,				300, 310, 0, 55,	"Dynamic light radius factor", UIText_Drawer },
	{ UI_SLIDER,	0,	0,				680, 310, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_light_scale },
	{ UI_TEXT,		0,	0,				300, 370, 0, 55,	"Maximum dynamic light radius", UIText_Drawer },
	{ UI_SLIDER,	0,	0,				680, 370, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_light_radmax },
	{ UI_TEXT,		0,	0,				300, 430, 0, 55,	"Maximum number of dynamic lights", UIText_Drawer },
	{ UI_SLIDER,	0,	0,				680, 430, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_light_max },
//	{ UI_TEXT,		0,	0,				300, 490, 0, 55,	"Clip dynamic lights", UIText_Drawer },
//	{ UI_BUTTON2,	0,	0,				680, 490, 70, 55,	"rend-light-clip", UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },
	{ UI_META,		6,	0,				0, -120 },
//	{ UI_TEXT,		0,	0,				300, 550, 0, 55,	"Lightpoly edge shrink units", UIText_Drawer },
//	{ UI_SLIDER,	0,	0,				680, 550, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_light_shrink },
	{ UI_TEXT,		0,	0,				300, 610, 0, 55,	"Ambient light level", UIText_Drawer },
	{ UI_SLIDER,	0,	0,				680, 610, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_light_ambient },
	{ UI_TEXT,		0,	0,				300, 670, 0, 55,	"Enable glowing textures", UIText_Drawer },
	{ UI_BUTTON2,	0,	0,				680, 670, 70, 55,	"rend-glow", UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },
	{ UI_TEXT,		0,	0,				300, 730, 0, 55,	"Floor/ceiling glow on walls", UIText_Drawer },
	{ UI_BUTTON2,	0,	0,				680, 730, 70, 55,	"rend-glow-wall", UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },
	{ UI_TEXT,		0,	0,				300, 790, 0, 55,	"Floor/ceiling glow height", UIText_Drawer },
	{ UI_SLIDER,	0,	0,				680, 790, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_glow_height },
	{ UI_TEXT,		0,	0,				300, 850, 0, 55,	"Glow brightness in fog", UIText_Drawer },
	{ UI_SLIDER,	0,	0,				680, 850, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_light_fog_bright },
	{ UI_TEXT,		0,	0,				300, 910, 0, 55,	"Enable decorations", UIText_Drawer },
	{ UI_BUTTON2,	0,	0,				680, 910, 70, 55,	"rend-light-decor", UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },

	{ UI_META,		7 },
	{ UI_TEXT,		0,	0,				280, 0, 0, 50,		"Graphics Options: Halos", UIText_Drawer },
	{ UI_TEXT,		0,	0,				300, 70, 0, 55,		"Number of flares per halo", UIText_Drawer },
	{ UI_SLIDER,	0,	0,				680, 70, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_halo },
	{ UI_TEXT,		0,	0,				300, 130, 0, 55,	"Use realistic halos", UIText_Drawer },
	{ UI_BUTTON2,	0,	0,				680, 130, 70, 55,	"rend-halo-realistic", UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },
	{ UI_META,      7,  0,              0,   60 },
	{ UI_TEXT,		0,	0,				300, 130, 0, 55,	"Halo brightness", UIText_Drawer },
	{ UI_SLIDER,	0,	0,				680, 130, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_halo_bright },
	{ UI_TEXT,		0,	0,				300, 190, 0, 55,	"Halo size factor", UIText_Drawer },
	{ UI_SLIDER,	0,	0,				680, 190, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_halo_size },
	{ UI_TEXT,		0,	0,				300, 250, 0, 55,	"Occlusion fade speed", UIText_Drawer },
	{ UI_SLIDER,	0,	0,				680, 250, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_halo_occlusion },
	{ UI_TEXT,		0,	0,				300, 310, 0, 55,	"Minimum halo radius", UIText_Drawer },
	{ UI_SLIDER,	0,	0,				680, 310, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_halo_radmin },
	{ UI_TEXT,		0,	0,				300, 370, 0, 55,	"Flare visibility limitation", UIText_Drawer },
	{ UI_SLIDER,	0,	0,				680, 370, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_halo_seclimit },
	{ UI_TEXT,		0,	0,				300, 430, 0, 55,	"Halo fading start", UIText_Drawer },
	{ UI_SLIDER,	0,	0,				680, 430, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_halo_dimnear },
	{ UI_TEXT,		0,	0,				300, 490, 0, 55,	"Halo fading end", UIText_Drawer },
	{ UI_SLIDER,	0,	0,				680, 490, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_halo_dimfar },
	{ UI_TEXT,		0,	0,				300, 550, 0, 55,	"Z magnification divisor", UIText_Drawer },
	{ UI_SLIDER,	0,	0,				680, 550, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_halo_zmagdiv },

	{ UI_META,		8 },
	{ UI_TEXT,		0,	0,				280, 0, 0, 50,		"Graphics Options: Textures", UIText_Drawer },
	{ UI_TEXT,		0,	0,				300, 70, 0, 55,		"Enable textures", UIText_Drawer },
	{ UI_BUTTON2,	0,	0,				680, 70, 70, 55,	"rend-tex", UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },
	{ UI_TEXT,		0,	0,				300, 130, 0, 55,	"Multitexturing", UIText_Drawer },
	{ UI_BUTTON2,	0,	0,				680, 130, 95, 55,	"rend-tex-detail-multitex", UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },
	{ UI_BUTTON2,	0,	0,				780, 130, 95, 55,	"rend-light-multitex", UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },
	{ UI_BUTTON2,	0,	0,				880, 130, 95, 55,	"rend-model-shiny-multitex", UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },
	{ UI_TEXT,		0,	0,				300, 190, 0, 55,	"Smooth texture animation", UIText_Drawer },
	{ UI_BUTTON2,	0,	0,				680, 190, 70, 55,	"rend-tex-anim-smooth", UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },
	{ UI_META,		8,	0,				0, 120 },
	{ UI_TEXT,		0,	0,				300, 130, 0, 55,	"Mipmapping and texture filter", UIText_Drawer },
	{ UI_LIST,		0,	0,				680, 130, 300, 175,	"",			UIList_Drawer, UIList_Responder, UIList_Ticker, CP_CvarList, &lst_mipmap },
	{ UI_TEXT,		0,	0,				300, 310, 0, 55,	"Texture quality", UIText_Drawer },
	{ UI_SLIDER,	0,	0,				680, 310, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_tex_quality },
	{ UI_TEXT,      0,  0,				300, 370, 0, 55,	"Smart texture filtering", UIText_Drawer },
	{ UI_BUTTON2,	0,	0,				680, 370, 70, 55,	"rend-tex-filter-smart", UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },
	{ UI_META,      8,  0,              0,   180 },
	{ UI_TEXT,		0,	0,				300, 370, 0, 55,	"Bilinear filtering for sprites", UIText_Drawer },
	{ UI_BUTTON2,	0,	0,				680, 370, 70, 55,	"rend-tex-filter-sprite", UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },
	{ UI_TEXT,		0,	0,				300, 430, 0, 55,	"Bilinear filtering for raw screens", UIText_Drawer },
	{ UI_BUTTON2,	0,	0,				680, 430, 70, 55,	"rend-tex-filter-raw", UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },
	{ UI_TEXT,		0,	0,				300, 490, 0, 55,	"Enable detail textures", UIText_Drawer },
	{ UI_BUTTON2,	0,	0,				680, 490, 70, 55,	"rend-tex-detail", UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },
	{ UI_TEXT,		0,	0,				300, 550, 0, 55,	"Detail texture scaling factor", UIText_Drawer },
	{ UI_SLIDER,	0,	0,				680, 550, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_detail_scale },
	{ UI_TEXT,		0,	0,				300, 610, 0, 55,	"Detail texture contrast", UIText_Drawer },
	{ UI_SLIDER,	0,	0,				680, 610, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_detail_strength },
	{ UI_TEXT,		0,	0,				300, 730, 0, 60,	"Force texture reset", UIText_Drawer },
	{ UI_BUTTON,	0,	0,				680, 730, 110, 60,	"Reset!", UIButton_Drawer, UIButton_Responder, 0, CP_TexReset },

	{ UI_META,		9 },
	{ UI_TEXT,		0,	0,				280, 0, 0, 50,		"Graphics Options: Objects", UIText_Drawer },
	{ UI_TEXT,		0,	0,				300, 70, 0, 55,		"Enable 3D models", UIText_Drawer },
	{ UI_BUTTON2,	0,	0,				680, 70, 70, 55,	"rend-model", UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },
	{ UI_TEXT,		0,	0,				300, 130, 0, 55,	"Interpolate between frames", UIText_Drawer },
	{ UI_BUTTON2,	0,	0,				680, 130, 70, 55,	"rend-model-inter", UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },
	{ UI_TEXT,		0,	0,				300, 190, 0, 55,	"3D model visibility limit", UIText_Drawer },
	{ UI_SLIDER,	0,	0,				680, 190, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_model_far },
	{ UI_TEXT,		0,	0,				300, 250, 0, 55,	"Precache 3D models", UIText_Drawer },
	{ UI_BUTTON2,	0,	0,				680, 250, 70, 55,	"rend-model-precache", UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },
	{ UI_TEXT,		0,	0,				300, 310, 0, 55,	"Max dynamic lights on 3D models", UIText_Drawer },
	{ UI_SLIDER,	0,	0,				680, 310, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_model_lights },
	{ UI_TEXT,		0,	0,				300, 370, 0, 55,	"LOD level zero distance", UIText_Drawer },
	{ UI_SLIDER,	0,	0,				680, 370, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_model_lod },
	{ UI_TEXT,		0,	0,				300, 430, 0, 55,	"Precache sprites (slow)", UIText_Drawer },
	{ UI_BUTTON2,	0,	0,				680, 430, 70, 55,	"rend-sprite-precache", UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },
	{ UI_TEXT,		0,	0,				300, 490, 0, 55,	"Disable Z-writes for sprites", UIText_Drawer },
	{ UI_BUTTON2,	0,	0,				680, 490, 70, 55,	"rend-sprite-noz", UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },
	{ UI_TEXT,		0,	0,				300, 550, 0, 55,	"Additive blending for sprites", UIText_Drawer },
	{ UI_BUTTON2,	0,	0,				680, 550, 70, 55,	"rend-sprite-blend", UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },
	{ UI_TEXT,		0,	0,				300, 610, 0, 55,	"Sprites lit by dynamic lights", UIText_Drawer },
	{ UI_BUTTON2,	0,	0,				680, 610, 70, 55,	"rend-sprite-lit", UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },
	{ UI_TEXT,		0,	0,				300, 670, 0, 55,	"Align sprites to...", UIText_Drawer },
	{ UI_LIST,		0,	0,				680, 670, 300, 115,	"",			UIList_Drawer, UIList_Responder, UIList_Ticker, CP_CvarList, &lst_sprite_align },
	{ UI_TEXT,		0,	0,				300, 790, 0, 55,	"Smooth actor rotation", UIText_Drawer },
	{ UI_BUTTON2,	0,	0,				680, 790, 70, 55,	"rend-mobj-smooth-turn", UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },
	{ UI_TEXT,		0,	0,				300, 850, 0, 55,	"Smooth actor movement", UIText_Drawer },
	{ UI_LIST,		0,	0,				680, 850, 300, 115,	"",			UIList_Drawer, UIList_Responder, UIList_Ticker, CP_CvarList, &lst_smooth_move },

	{ UI_META,		10 },
	{ UI_TEXT,		0,	0,				280, 0, 0, 50,		"Graphics Options: Particles", UIText_Drawer },
	{ UI_TEXT,		0,	0,				300, 70, 0, 55,		"Enable particle effects", UIText_Drawer },
	{ UI_BUTTON2,	0,	0,				680, 70, 70, 55,	"rend-particle", UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },
	{ UI_TEXT,		0,	0,				300, 130, 0, 55,	"Maximum number of particles", UIText_Drawer },
	{ UI_SLIDER,	0,	0,				680, 130, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_particle_max },
	{ UI_TEXT,		0,	0,				300, 190, 0, 55,	"Spawn rate factor", UIText_Drawer },
	{ UI_SLIDER,	0,	0,				680, 190, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_particle_rate },
	{ UI_TEXT,		0,	0,				300, 250, 0, 55,	"Near diffusion factor", UIText_Drawer },
	{ UI_SLIDER,	0,	0,				680, 250, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_particle_diffuse },
	{ UI_TEXT,		0,	0,				300, 310, 0, 55,	"Near clip distance", UIText_Drawer },
	{ UI_SLIDER,	0,	0,				680, 310, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_particle_visnear },

	{ UI_META,		11 },
	{ UI_TEXT,		0,	0,				280, 0, 0, 50,		"Network Options", UIText_Drawer },
	{ UI_TEXT,		0,	0,				300, 70, 0, 55,		"Continuous screen refresh", UIText_Drawer },
	{ UI_BUTTON2,	0,	0,				680, 70, 70, 55,	"net-nosleep", UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },
	{ UI_TEXT,		0,	0,				300, 130, 0, 55,	"Show development info", UIText_Drawer },
	{ UI_BUTTON2,	0,	0,				680, 130, 70, 55,	"net-dev", UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },
	{ UI_TEXT,		0,	0,				300, 190, 0, 55,	"Server login password", UIText_Drawer },
	{ UI_EDIT,		0,	0,				680, 190, 300, 55,	"",			UIEdit_Drawer, UIEdit_Responder, 0, CP_CvarEdit, &ed_server_password },
	{ UI_TEXT,		0,	0,				300, 250, 0, 55,	"Cl-to-sv pos transmit tics", UIText_Drawer },
	{ UI_SLIDER,	0,	0,				680, 250, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_client_pos_interval },
	{ UI_TEXT,		0,	0,				300, 310, 0, 55,	"Frame interval tics", UIText_Drawer },
	{ UI_SLIDER,	0,	0,				680, 310, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_server_frame_interval },

	{ UI_META,		12 },
	{ UI_TEXT,		0,	0,				280, 0, 0, 50,		"Console Options", UIText_Drawer },
	{ UI_TEXT,		0,	0,				300, 70, 0, 55,		"Display FPS counter", UIText_Drawer },
	{ UI_BUTTON2,	0,	0,				680, 70, 70, 55,	"con-fps",	UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },
	{ UI_META,		12, 0,				0, 60 },
	{ UI_TEXT,		0,	0,				300, 70, 0, 55,		"Display progress bar", UIText_Drawer },
	{ UI_BUTTON2,	0,	0,				680, 70, 70, 55,	"con-progress",	UIButton_Drawer, UIButton_Responder, 0,	CP_CvarButton },
	{ UI_TEXT,		0,	0,				300, 130, 0, 55,	"Display Control Panel help window", UIText_Drawer },
	{ UI_BUTTON2,	0,	0,				680, 130, 70, 55,	"ui-panel-help", UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },
	{ UI_TEXT,		0,	0,				300, 190, 0, 55,	"Display help indicators", UIText_Drawer },
	{ UI_BUTTON2,	0,	0,				680, 190, 70, 55,	"ui-panel-tips", UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },
	{ UI_META,		12,	0,				0, 180 },
	{ UI_TEXT,		0,	0,				300, 130, 0, 55,	"Silent console variables", UIText_Drawer },
	{ UI_BUTTON2,	0,	0,				680, 130, 70, 55,	"con-var-silent", UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },
	{ UI_TEXT,		0,	0,				300, 190, 0, 55,	"Dump messages to Doomsday.out", UIText_Drawer },
	{ UI_BUTTON2,	0,	0,				680, 190, 70, 55,	"con-dump", UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },
	{ UI_TEXT,		0,	0,				300, 250, 0, 55,	"Show ASCII codes of pressed keys", UIText_Drawer },
	{ UI_BUTTON2,	0,	0,				680, 250, 70, 55,	"con-key-show", UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },
	{ UI_TEXT,		0,	0,				300, 310, 0, 55,	"Command completion with Tab", UIText_Drawer },
	{ UI_LIST,		0,	0,				680, 310, 300, 120,	"",			UIList_Drawer, UIList_Responder, UIList_Ticker, CP_CvarList, &lst_con_completion },
	{ UI_TEXT,		0,	0,				300, 435, 0, 55,	"Background opacity", UIText_Drawer },
	{ UI_SLIDER,	0,	0,				680, 435, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_con_alpha },
	{ UI_TEXT,		0,	0,				300, 495, 0, 55,	"Background light", UIText_Drawer },
	{ UI_SLIDER,	0,	0,				680, 495, 300, 55,	"",			UISlider_Drawer, UISlider_Responder, UISlider_Ticker, CP_CvarSlider, &sld_con_light },
	{ UI_TEXT,		0,	0,				300, 555, 0, 55,	"Console text has shadows", UIText_Drawer },
	{ UI_BUTTON2,	0,	0,				680, 555, 70, 55,	"con-text-shadow", UIButton_Drawer, UIButton_Responder, 0, CP_CvarButton },
	{ UI_TEXT,		0,	0,				300, 615, 0, 55,	"Activation key", UIText_Drawer },
	{ UI_FOCUSBOX,	0,	0,				680, 615, 70, 55,	"con-key-activate",	CP_KeyGrabDrawer, CP_KeyGrabResponder },
	{ UI_TEXT,		0,	0,				680, 670, 0, 40,	"Click the box, press a key.", UIText_Drawer },

	{ UI_NONE }
};
/* *INDENT-ON* */

// PRIVATE DATA DEFINITIONS ------------------------------------------------

// CODE --------------------------------------------------------------------

//===========================================================================
// CP_ClosePanel
//===========================================================================
void CP_ClosePanel(ui_object_t *ob)
{
	UI_End();
}

//===========================================================================
// CP_ChooseGroup
//===========================================================================
void CP_ChooseGroup(ui_object_t *ob)
{
	int     i;

	memset(panel_buttons, 0, sizeof(panel_buttons));
	UI_FlagGroup(ob_panel, 1, UIF_ACTIVE, UIFG_CLEAR);
	*(char *) ob->data = true;
	ob->flags |= UIF_ACTIVE;
	// Hide/show the option controls.
	for(i = 0; i < NUM_CP_BUTTONS; i++)
		UI_FlagGroup(ob_panel, 2 + i, UIF_HIDDEN, !panel_buttons[i]);
}

//===========================================================================
// CP_DrawLogo
//===========================================================================
void CP_DrawLogo(ui_object_t *ob)
{
	UI_DrawLogo(ob->x, ob->y, ob->w, ob->h);
}

//===========================================================================
// CP_DrawBorder
//===========================================================================
void CP_DrawBorder(ui_object_t *ob)
{
	int     b = UI_BORDER;
	ui_object_t *it;
	void   *help_ptr;
	boolean shown;

	UIFrame_Drawer(ob);

	// Draw help window visual cues.
	if(panel_show_tips)
	{
		GL_BlendMode(BM_ADD);
		for(it = ob_panel; it->type; it++)
		{
			if(it->flags & UIF_HIDDEN || it->group < 2 || it->type != UI_TEXT)
				continue;
			// Try to find help for this.
			if((help_ptr = DH_Find(it->text)))
			{
				shown = (panel_help == help_ptr && panel_help_active);
				UI_HorizGradient(ob->x + b, it->y + it->h / 2 - ui_fonthgt / 2,
								 2 * ui_fonthgt, ui_fonthgt,
								 UI_COL(UIC_BRD_HI), 0, shown ? .8f : .2f, 0);
			}
		}
		GL_BlendMode(BM_NORMAL);
	}
}

//===========================================================================
// CP_CvarButton
//===========================================================================
void CP_CvarButton(ui_object_t *ob)
{
	cvarbutton_t *cb = ob->data;
	cvar_t *var = Con_GetVariable(cb->cvarname);

	strcpy(ob->text, cb->active ? cb->yes : cb->no);
	if(!strcmp(cb->cvarname, "rend-tex-filter-raw"))
	{
		GL_TextureFilterMode(DD_RAWSCREENS, cb->active);
		return;
	}
	if(!var)
		return;
	// Change state.
	//*(char *) var->ptr = cb->active;
	Con_SetInteger(cb->cvarname, cb->active);
}

//===========================================================================
// CP_CvarList
//===========================================================================
void CP_CvarList(ui_object_t *ob)
{
	uidata_list_t *list = ob->data;
	cvar_t *var = Con_GetVariable(list->data);
	int     value = ((uidata_listitem_t *) list->items)[list->selection].data;

	if(list->selection < 0)
		return;					// Hmm?
	if(!strcmp(list->data, "rend-tex-mipmap"))
	{
		Con_Executef(false, "mipmap %i", value);
		return;
	}
	if(!var)
		return;
	*(int *) var->ptr = value;
}

//===========================================================================
// CP_CvarEdit
//===========================================================================
void CP_CvarEdit(ui_object_t *ob)
{
	uidata_edit_t *ed = ob->data;

	Con_SetString(ed->data, ed->ptr);
}

//===========================================================================
// CP_CvarSlider
//===========================================================================
void CP_CvarSlider(ui_object_t *ob)
{
	uidata_slider_t *slid = ob->data;
	cvar_t *var = Con_GetVariable(slid->data);

	if(!var)
		return;
	if(var->type == CVT_FLOAT)
		*(float *) var->ptr = (int) (100 * slid->value + .5f) / 100.0f;
	else if(var->type == CVT_INT)
		*(int *) var->ptr = (int) (slid->value + 0.5f);
	else if(var->type == CVT_BYTE)
		*(byte *) var->ptr = (byte) (slid->value + 0.5f);
}

//===========================================================================
// CP_KeyGrabResponder
//===========================================================================
int CP_KeyGrabResponder(ui_object_t *ob, event_t *ev)
{
	if((ev->type == ev_mousebdown && UI_MouseInside(ob)) ||
	   (ev->type == ev_keydown && IS_ACTKEY(ev->data1)))
	{
		// We want the focus.
		return true;
	}
	// Only does something when has the focus.
	if(!(ob->flags & UIF_FOCUS))
		return false;
	if(ev->type == ev_keydown)
	{
		Con_SetInteger(ob->text, ev->data1);
		// All keydown events are eaten. 
		// Note that the UI responder eats all Tabs!
		return true;
	}
	return false;
}

//===========================================================================
// CP_KeyGrabDrawer
//===========================================================================
void CP_KeyGrabDrawer(ui_object_t *ob)
{
	boolean sel = (ob->flags & UIF_FOCUS) != 0;
	float   alpha = (ob->flags & UIF_DISABLED ? .2f : 1);
	char    buf[80];
	byte    key = Con_GetByte(ob->text);

	UI_GradientEx(ob->x, ob->y, ob->w, ob->h, UI_BORDER, UI_COL(UIC_SHADOW), 0,
				  1, 0);
	UI_Shade(ob->x, ob->y, ob->w, ob->h, UI_BORDER, UI_COL(UIC_BRD_HI),
			 UI_COL(UIC_BRD_LOW), alpha / 3, -1);
	UI_DrawRectEx(ob->x, ob->y, ob->w, ob->h, UI_BORDER * (sel ? -1 : 1),
				  false, UI_COL(UIC_BRD_HI), NULL, alpha, -1);
	sprintf(buf, "%i", key);
	UI_TextOutEx(buf, ob->x + ob->w / 2, ob->y + ob->h / 2, true, true,
				 UI_COL(UIC_TEXT), alpha);
}

//===========================================================================
// CP_TexReset
//===========================================================================
void CP_TexReset(ui_object_t *ob)
{
	Con_Execute("texreset", false);
}

//===========================================================================
// CP_QuickFOV
//===========================================================================
void CP_QuickFOV(ui_object_t *ob)
{
	Con_SetFloat("rend-camera-fov", sld_fov.value = atoi(ob->text));
}

//===========================================================================
// CP_ResolutionInfo
//===========================================================================
void CP_ResolutionInfo(ui_object_t *ob)
{
	char    buf[80];

	if(!strcmp(ob->text, "default"))
		sprintf(buf, "%i x %i", defResX, defResY);
	else
		sprintf(buf, "Current resolution: %i x %i", screenWidth, screenHeight);
	UI_TextOutEx(buf, ob->x, ob->y + ob->h / 2, false, true, UI_COL(UIC_TEXT),
				 1);
}

//===========================================================================
// CP_UpdateSetResButton
//===========================================================================
void CP_UpdateSetResButton(int w, int h)
{
	ui_object_t *ob = UI_FindObject(ob_panel, CPG_VIDEO, CPID_SET_RES);

	sprintf(ob->text, "Change To %i x %i", w, h);
	if(w == screenWidth && h == screenHeight)
		ob->flags |= UIF_DISABLED;
	else
		ob->flags &= ~UIF_DISABLED;
}

//===========================================================================
// CP_ResolutionList
//===========================================================================
void CP_ResolutionList(ui_object_t *ob)
{
	uidata_list_t *list = ob->data;
	int     seldata =
		((uidata_listitem_t *) list->items)[list->selection].data;

	sprintf(panel_res_x, "%i", seldata & 0xffff);
	sprintf(panel_res_y, "%i", seldata >> 16);

	strcpy(UI_FindObject(ob_panel, ob->group, CPID_RES_X)->text, panel_res_x);
	strcpy(UI_FindObject(ob_panel, ob->group, CPID_RES_Y)->text, panel_res_y);

	CP_ResChanged(ob);
}

//===========================================================================
// CP_SetDefaultRes
//===========================================================================
void CP_SetDefaultRes(ui_object_t *ob)
{
	int     x = atoi(panel_res_x), y = atoi(panel_res_y);

	if(!x || !y)
		return;
	defResX = x;
	defResY = y;
}

//===========================================================================
// CP_SetRes
//===========================================================================
void CP_SetRes(ui_object_t *ob)
{
	int     x = atoi(panel_res_x), y = atoi(panel_res_y);

	if(!x || !y)
		return;
	if(x < 320 || y < 240)
		return;
	ob->flags |= UIF_DISABLED;
	// Can't change the resolution while the UI is active (controls need to
	// be repositioned).
	UI_End();
	GL_ChangeResolution(x, y, 0);
	// Reactivate the panel.
	Con_Execute("panel", true);
}

//===========================================================================
// CP_ResChanged
//===========================================================================
void CP_ResChanged(ui_object_t *ob)
{
	CP_UpdateSetResButton(atoi(panel_res_x), atoi(panel_res_y));
}

//===========================================================================
// CP_FindHover
//  Returns the option, if any, the mouse is currently hovering on. The
//  check is based on the coordinates of the Text object.
//===========================================================================
ui_object_t *CP_FindHover(void)
{
	ui_object_t *ob;

	for(ob = ob_panel; ob->type; ob++)
	{
		if(ob->flags & UIF_HIDDEN || ob->type != UI_TEXT || ob->group < 2 ||
		   ob->relx < 280)
			continue;
		// Extend the detection area to the right edge of the screen.
		if(UI_MouseInsideBox(ob->x, ob->y, screenWidth, ob->h))
			return ob;
	}
	return NULL;
}

//===========================================================================
// CP_Ticker
//  Track the mouse and move the documentation window as needed.
//===========================================================================
void CP_Ticker(ui_page_t * page)
{
	int     off;
	ui_object_t *ob;
	void   *help;

	// Normal ticker actions first.
	UIPage_Ticker(page);

	// Check if the mouse is inside the options box.
	ob = UI_FindObject(page->objects, 0, CPID_FRAME);
	if(!UI_MouseInside(ob) || !panel_show_help)
	{
		panel_help_active = false;
	}
	else
	{
		// The mouse is inside the options box, so we may need to display
		// the options box or change its text. Detect which object the 
		// mouse is on.
		if((ob = CP_FindHover()))
		{
			// Change the text.
			if((help = DH_Find(ob->text)))
			{
				panel_help = help;
				panel_help_source = ob;
			}

			if(UI_MouseResting(page))
			{
				// The mouse has been paused on a text, activate help.
				panel_help_active = true;
			}

			if(!help)
				panel_help_active = false;
		}
	}

	// Should we move the help box?
	off = 0;
	if(panel_help_active)
	{
		if(panel_help_offset < HELP_OFFSET)
			off = (HELP_OFFSET - panel_help_offset) / 2;
		if(off < 4)
			off = 4;
	}
	else						// Help should be hidden.
	{
		if(panel_help_offset > 0)
			off = -panel_help_offset / 2;
		if(off > -4)
			off = -4;
	}
	panel_help_offset += off;
	if(panel_help_offset > HELP_OFFSET)
		panel_help_offset = HELP_OFFSET;
	if(panel_help_offset < 0)
		panel_help_offset = 0;
}

//===========================================================================
// CP_LabelText
//===========================================================================
int CP_LabelText(char *label, char *text, int x, int y, int w, int h,
				 float alpha)
{
	int     ind;

	UI_ColorA(UI_COL(UIC_TEXT), .5f * alpha);
	FR_TextOut(label, x, y);
	ind = FR_TextWidth(label);
	return UI_TextOutWrapEx(text, x + ind, y, w - ind, h, UI_COL(UIC_TEXT),
							alpha);
}

//===========================================================================
// CP_Drawer
//===========================================================================
void CP_Drawer(ui_page_t * page)
{
	float   alpha = panel_help_offset / (float) HELP_OFFSET;
	int     x, y, w, h, bor;
	char   *str;
	char   *homeURL = "http://sourceforge.net/projects/deng/";

	// First call the regular drawer.
	UIPage_Drawer(page);

	// Project home.
	UI_TextOutEx(homeURL, screenWidth - UI_BORDER - FR_TextWidth(homeURL), 
		UI_ScreenY(25), false, true, UI_COL(UIC_TEXT), 0.4f);

	// Is the help box visible?
	if(panel_help_offset <= 0 || !panel_help_source)
		return;

	// Help box placement.
	bor = 2 * UI_BORDER / 3;
	x = -bor;
	y = UI_ScreenY(0);
	w = HELP_OFFSET;
	h = UI_ScreenH(920);
	UI_GradientEx(x, y, w, h, bor, UI_COL(UIC_HELP), UI_COL(UIC_HELP), alpha,
				  alpha);
	UI_DrawRectEx(x, y, w, h, bor, false, UI_COL(UIC_BRD_HI), NULL, alpha, -1);
	x += 2 * bor;
	y += 2 * bor;
	w -= 4 * bor;
	h -= 4 * bor;

	// The title (with shadow).
	UI_TextOutWrapEx(panel_help_source->text, x + UI_SHADOW_OFFSET,
					 y + UI_SHADOW_OFFSET, w, h, UI_COL(UIC_SHADOW), alpha);
	y = UI_TextOutWrapEx(panel_help_source->text, x, y, w, h,
						 UI_COL(UIC_TITLE), alpha) + ui_fonthgt + 3;
	UI_Line(x, y, x + w, y, UI_COL(UIC_TEXT), 0, alpha * .5f, 0);
	y += 2;

	// Cvar?
	if((str = DH_GetString(panel_help, HST_CONSOLE_VARIABLE)))
		y = CP_LabelText("CVar: ", str, x, y, w, h, alpha) + ui_fonthgt;

	// Default?
	if((str = DH_GetString(panel_help, HST_DEFAULT_VALUE)))
		y = CP_LabelText("Default: ", str, x, y, w, h, alpha) + ui_fonthgt;

	// Information.
	if((str = DH_GetString(panel_help, HST_DESCRIPTION)))
	{
		y += ui_fonthgt / 2;
		UI_TextOutWrapEx(str, x, y, w, h, UI_COL(UIC_TEXT), alpha);
	}
}

/*
 * Initializes all slider objects.
 */
void CP_InitCvarSliders(ui_object_t *ob)
{
	for(; ob->type; ob++)
		if(ob->action == CP_CvarSlider)
		{
			uidata_slider_t *slid = ob->data;

			slid->value =
				slid->floatmode ? Con_GetFloat(slid->
											   data) : Con_GetInteger(slid->
																	  data);
		}
}

/*
 * Initialize and open the Control Panel.
 */
int CCmdOpenPanel(int argc, char **argv)
{
	int     i;
	ui_object_t *ob, *foc;
	uidata_list_t *list;
	cvarbutton_t *cvb;

	if(isDedicated)
		return false;

	// The help window is hidden.
	panel_help_active = false;
	panel_help_offset = 0;
	panel_help_source = NULL;

	UI_InitPage(&page_panel, ob_panel);
	strcpy(page_panel.title,
		   "Doomsday " DOOMSDAY_VERSION_TEXT " Control Panel");
	page_panel.ticker = CP_Ticker;
	page_panel.drawer = CP_Drawer;
	if(argc != 2)
	{
		// Choose the group that was last visible.
		for(i = 0; i < NUM_CP_BUTTONS; i++)
			if(panel_buttons[i])
				CP_ChooseGroup(foc = ob_panel + i);
	}
	else
	{
		// With an argument, choose the appropriate group.
		foc = NULL;
		for(i = 0; i < NUM_CP_BUTTONS; i++)
			if(!stricmp(ob_panel[i].text, argv[1]))
			{
				CP_ChooseGroup(foc = ob_panel + i);
				break;
			}
		if(!foc)
			CP_ChooseGroup(foc = ob_panel);
	}

	// Set default Yes/No strings.
	for(cvb = cvarbuttons; cvb->cvarname; cvb++)
	{
		if(!cvb->yes)
			cvb->yes = "Yes";
		if(!cvb->no)
			cvb->no = "No";
	}

	// Set cvarbutton data pointers.
	// This is only done the first time "panel" is issued.
	for(i = 0, ob = ob_panel; ob_panel[i].type; i++, ob++)
	{
		if(ob->action == CP_CvarButton)
		{
			if(ob->data)
			{
				// This button has already been initialized.
				cvb = ob->data;
				cvb->active = Con_GetByte(cvb->cvarname) != 0;
				strcpy(ob->text, cvb->active ? cvb->yes : cvb->no);
				continue;
			}
			// Find the cvarbutton representing this one.
			for(cvb = cvarbuttons; cvb->cvarname; cvb++)
				if(!strcmp(ob->text, cvb->cvarname))
				{
					cvb->active = Con_GetByte(cvb->cvarname) != 0;
					ob->data = cvb;
					strcpy(ob->text, cvb->active ? cvb->yes : cvb->no);
					break;
				}
		}
		if(ob->action == CP_CvarList)
		{
			list = ob->data;
			// Choose the correct list item based on the value of the cvar.
			list->selection = UI_ListFindItem(ob, Con_GetInteger(list->data));
		}
		if(ob->action == CP_CvarEdit)
		{
			uidata_edit_t *ed = ob->data;

			strncpy(ed->ptr, Con_GetString(ed->data), ed->maxlen);
		}
	}
	CP_InitCvarSliders(ob_panel);

	// Update width the current resolution.
	ob = UI_FindObject(ob_panel, CPG_VIDEO, CPID_RES_LIST);
	list = ob->data;
	list->selection = UI_ListFindItem(ob, RES(screenWidth, screenHeight));
	if(list->selection == -1)
		// Then use a reasonable default.
		list->selection = UI_ListFindItem(ob, RES(640, 480));
	CP_ResolutionList(ob);

	UI_Init();
	UI_SetPage(&page_panel);
	UI_Focus(foc);
	return true;
}
