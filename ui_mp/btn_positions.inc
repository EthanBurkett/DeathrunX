
#ifndef BTN_POSITIONS_INC
#define BTN_POSITIONS_INC 1

// --- layout knobs ---
#define BTN_W             DX_BTN_WIDTH
#define BTN_H             DX_BTN_HEIGHT
#define BTN_GAP_SIDE      10          // gap between briefing edge and side columns
#define BTN_ROW_SPACING   30          // vertical distance between rows

// Half the vertical space between the bottom of the briefing and the bottom of the frame
#define BTN_TOP_MARGIN    ( ( (MENUFRAME_Y + MENUFRAME_H) - (BRIEFING_Y + BRIEFING_HEIGHT) ) / 4 )

// --- column left-edges (aligned to the briefing width) ---
#define COL_LEFT_X    (MENUFRAME_ANCHOR_X_CENTER - (BRIEFING_WIDTH/2) - BTN_GAP_SIDE - BTN_W)
#define COL_CENTER_X  (MENUFRAME_ANCHOR_X_CENTER - (BTN_W/2))
#define COL_RIGHT_X   (MENUFRAME_ANCHOR_X_CENTER + (BRIEFING_WIDTH/2) + BTN_GAP_SIDE)

// centers for midpoint math
#define COL_LEFT_C    (COL_LEFT_X + BTN_W/2)
#define COL_CENTER_C  (MENUFRAME_ANCHOR_X_CENTER)
#define COL_RIGHT_C   (COL_RIGHT_X + BTN_W/2)

// --- row Y positions (all rows under the map image) ---
#define ROW_BASE_Y    (BRIEFING_Y + BRIEFING_HEIGHT + BTN_TOP_MARGIN)
#define ROW_TOP_Y     (ROW_BASE_Y)
#define ROW_MID_Y     (ROW_BASE_Y + BTN_ROW_SPACING)
#define ROW_BOT_Y     (ROW_BASE_Y + (BTN_ROW_SPACING*2))
#define ROW_EXTRA_Y   (ROW_BASE_Y + (BTN_ROW_SPACING*3))  // optional (e.g., VIP)

// --- staggered X positions for top/bottom rows (midpoints between mid-row columns) ---
#define STAGGER_LR_X  ( ((COL_LEFT_C + COL_CENTER_C)/2) - (BTN_W/2) )   // between left & center
#define STAGGER_CR_X  ( ((COL_CENTER_C + COL_RIGHT_C)/2) - (BTN_W/2) )  // between center & right

// --- submenu center alignment ---
#define SUBMENU_CENTER_X (MENUFRAME_SUBMENU_X + (MENUFRAME_SUBMENU_W/2) - (DX_BTN_WIDTH/2))
#define SUBMENU_CENTER_Y (MENUFRAME_SUBMENU_BOTTOM_Y + (MENUFRAME_SUBMENU_H/2) - (DX_BTN_HEIGHT/2))
// with padding
#define SUBMENU_LEFT_X (MENUFRAME_SUBMENU_X + MENUFRAME_SUBMENU_PADDING_X)
#define SUBMENU_RIGHT_X(w) (MENUFRAME_SUBMENU_X + MENUFRAME_SUBMENU_W - w - MENUFRAME_SUBMENU_PADDING_X)

#endif
