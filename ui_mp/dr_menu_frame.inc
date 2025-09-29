#include "ui_mp/dx_colors.inc"
#include "ui_mp/mutables.inc"

#ifndef DR_MENU_FRAME_INC
#define DR_MENU_FRAME_INC 1

// ======= Tunables =======
#define CENTER_TO_SCREEN_X(w) (SCREEN_WIDTH / 2 - w / 2)
#define CENTER_TO_SCREEN_Y(h) (SCREEN_HEIGHT / 2 - h / 2)

#define MENUFRAME_X        32
#define MENUFRAME_Y        30
#define MENUFRAME_W        576
#define MENUFRAME_H        372
#define MENUFRAME_ANCHOR_X_CENTER (MENUFRAME_X + MENUFRAME_W / 2)
#define MENUFRAME_ANCHOR_Y_CENTER (MENUFRAME_Y + MENUFRAME_H / 2)

// Panel look
#define MENUFRAME_BACKGROUND    "menu_bg_large"
#define MENUFRAME_BORDER   			DX_THEME 1
#define MENUFRAME_BORDERSZ 			1
#define MENUFRAME_ACCENT_DIM   	DX_THEME_DARK 1

// Submenu (Common)
#define MENUFRAME_GAP 								16
#define MENUFRAME_SUBMENU_X        		MENUFRAME_X
#define MENUFRAME_SUBMENU_W 					MENUFRAME_W
#define MENUFRAME_SUBMENU_H 					40
#define MENUFRAME_SUBMENU_BACKGROUND	"menu_bg_small"
#define MENUFRAME_SUBMENU_BORDERSZ 		1
#define MENUFRAME_SUBMENU_BORDERCOLOR MENUFRAME_ACCENT_DIM
#define MENUFRAME_SUBMENU_PADDING_X   10

// Submenu (Bottom)
#define MENUFRAME_SUBMENU_BOTTOM_Y     (MENUFRAME_Y + MENUFRAME_H + MENUFRAME_GAP)

#endif // DR_MENU_FRAME_INC
// ======= Frame =======

// Base panel
itemDef
{
  rect        MENUFRAME_X MENUFRAME_Y MENUFRAME_W MENUFRAME_H
  style       WINDOW_STYLE_SHADER
  border      MENUFRAME_BORDERSZ
  bordercolor MENUFRAME_BORDER
  background  MENUFRAME_BACKGROUND
  visible     MENUFRAME_INCLUDE_MAIN_PANEL
  decoration
}

// Submenu (Bottom)
itemDef
{
  rect        MENUFRAME_SUBMENU_X MENUFRAME_SUBMENU_BOTTOM_Y MENUFRAME_SUBMENU_W MENUFRAME_SUBMENU_H
  style       WINDOW_STYLE_SHADER
  border      MENUFRAME_SUBMENU_BORDERSZ
  bordercolor MENUFRAME_SUBMENU_BORDERCOLOR
  background  MENUFRAME_SUBMENU_BACKGROUND
  visible     MENUFRAME_INCLUDE_SUBMENU_BOTTOM
  decoration
}