#undef  MENUFRAME_INCLUDE_SUBMENU_TOP
#undef  MENUFRAME_INCLUDE_MAIN_PANEL
#undef  MENUFRAME_INCLUDE_SUBMENU_BOTTOM
#define MENUFRAME_INCLUDE_SUBMENU_TOP     0
#define MENUFRAME_INCLUDE_MAIN_PANEL      0
#define MENUFRAME_INCLUDE_SUBMENU_BOTTOM  1
#include "ui_mp/dr_menu_frame.inc"

#undef  _NAV_ORIG_W
#define _NAV_ORIG_W   DX_BTN_WIDTH
#undef  DX_BTN_WIDTH
#define DX_BTN_WIDTH  32
#undef  _NAV_GAP
#define _NAV_GAP      16

// // Prev / Next (narrow arrows)
DR_BUTTON("previous", (SUBMENU_CENTER_X - (DX_BTN_WIDTH + _NAV_GAP) - _NAV_ORIG_W), SUBMENU_CENTER_Y, "<<", scriptMenuResponse "previous";, 1)

DR_BUTTON("next", (SUBMENU_CENTER_X + (DX_BTN_WIDTH + _NAV_GAP) + _NAV_ORIG_W), SUBMENU_CENTER_Y, ">>", scriptMenuResponse "next";, 1)

// ---- restore original width for main buttons ----
#include "ui_mp/mutables.inc"

#ifndef SUBMENU_LEFT_X
#define SUBMENU_LEFT_X (MENUFRAME_SUBMENU_X + 8)
#endif


// Select (center) + Back (left)
DR_BUTTON("select_btn", SUBMENU_CENTER_X, SUBMENU_CENTER_Y, "Select", scriptMenuResponse "select";, 1)
DR_BUTTON("back",   SUBMENU_LEFT_X,   SUBMENU_CENTER_Y, "Back",  close self; open "character_stuff";, 1)

#define TEXT_CONTAINER_WIDTH 220
#define TEXT_CONTAINER_HEIGHT (MENUFRAME_SUBMENU_H - 20)
#define TEXT_CONTAINER_X (SUBMENU_CENTER_X - TEXT_CONTAINER_WIDTH / 4)
#define TEXT_CONTAINER_Y (SUBMENU_CENTER_Y - TEXT_CONTAINER_HEIGHT - 20)

/* Item Text Container */
itemDef { 
  rect TEXT_CONTAINER_X TEXT_CONTAINER_Y TEXT_CONTAINER_WIDTH TEXT_CONTAINER_HEIGHT DX_BTN_ALIGN 
  style WINDOW_STYLE_SHADER
  background "menu_bg_small"
  forecolor 1 1 1 1
  border    1
  bordercolor DX_THEME 1
  visible   1
  decoration 
}

ITEM_TEXT("characters")

