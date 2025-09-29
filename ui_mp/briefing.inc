#include "ui_mp/dx_colors.inc"
#include "ui_mp/dr_menu_frame.inc"

#ifndef BRIEFING_INC
#define BRIEFING_INC

#define BRIEFING_WIDTH 220
#define BRIEFING_HEIGHT 180
#define BRIEFING_X (MENUFRAME_ANCHOR_X_CENTER - BRIEFING_WIDTH / 2)
#define BRIEFING_Y (MENUFRAME_Y + 16)
#define BRIEFING_BORDER_SIZE 1

itemDef 
{
	rect			BRIEFING_X BRIEFING_Y BRIEFING_WIDTH BRIEFING_HEIGHT
	style			WINDOW_STYLE_SHADER
	exp				material( "$levelBriefing" )
  border    0
	forecolor		1 1 1 1
	visible			1
	decoration
}

// Borders

// Bottom border
itemDef
{
  rect    (BRIEFING_X - BRIEFING_BORDER_SIZE) (BRIEFING_Y + BRIEFING_HEIGHT) (BRIEFING_WIDTH + (BRIEFING_BORDER_SIZE * 2)) BRIEFING_BORDER_SIZE
  style   WINDOW_STYLE_FILLED
  backcolor  DX_THEME 1
  visible     1
  border      0
  decoration
}

// Top border
itemDef
{
  rect    (BRIEFING_X - BRIEFING_BORDER_SIZE) (BRIEFING_Y - BRIEFING_BORDER_SIZE) (BRIEFING_WIDTH + (BRIEFING_BORDER_SIZE * 2)) BRIEFING_BORDER_SIZE
  style   WINDOW_STYLE_FILLED
  border  0
  backcolor  DX_THEME 1
  visible     1
  border      0
  decoration
}

// Left border
itemDef
{
  rect    (BRIEFING_X - BRIEFING_BORDER_SIZE) BRIEFING_Y BRIEFING_BORDER_SIZE BRIEFING_HEIGHT
  style   WINDOW_STYLE_FILLED
  backcolor  DX_THEME 1
  visible     1
  border 0
  decoration
}

// Right border
itemDef
{
  rect    (BRIEFING_X + BRIEFING_WIDTH) BRIEFING_Y BRIEFING_BORDER_SIZE BRIEFING_HEIGHT
  style   WINDOW_STYLE_FILLED
  backcolor  DX_THEME 1
  visible     1
  border 0
  decoration
}

itemDef
		{
			name			"separator_left"
			visible			1
			rect (MENUFRAME_X + 1) (BRIEFING_Y + (BRIEFING_HEIGHT / 2)) (BRIEFING_X - (MENUFRAME_X + 1)) 1
			backcolor DX_THEME 1
			style			WINDOW_STYLE_FILLED
			decoration
		}
		itemDef
		{
			name        "separator_right"
			visible     1
			rect (BRIEFING_X + BRIEFING_WIDTH) (BRIEFING_Y + (BRIEFING_HEIGHT / 2)) ((MENUFRAME_X + MENUFRAME_W - 1) - (BRIEFING_X + BRIEFING_WIDTH) + 1) 1
			backcolor   DX_THEME 1
			style       WINDOW_STYLE_FILLED
			decoration
		}

#endif // BRIEFING_INC
