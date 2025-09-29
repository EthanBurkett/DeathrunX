#include "ui_mp/dx_colors.inc"
#include "ui_mp/mutables.inc"

// ---------- Tables & helpers ----------
#ifndef DR_TABLES_INC
#define DR_TABLES_INC 1

#define ITEM_TABLE        "mp/itemTable.csv"
#define CHARACTER_TABLE   "mp/characterTable.csv"

// Player rank as seen by UI (adjust if your rank stat differs)
// stock CoD4 MP rank is stat 252 (0-based), so +1 to make it 1..55
#define rank       ( stat(2350) + 1 )
#define prestige   ( stat(2326) )
#define CHARACTER_IDX     (dvarInt("drui_character") + 1)
#define WEAPON_IDX        (dvarInt("drui_weapon") + 1)
#define CURRENT_TABLE     dvarString("customize_table")

// Center helpers you already defined elsewhere
// SUBMENU_CENTER_X / SUBMENU_CENTER_Y should be defined by your frame include
#endif

#ifndef DX_COMMON_INC
#define DX_COMMON_INC 1

// Simple text helper (static props only)
#define DX_TEXT(px, py, pw, ph, ptext, palign, r, g, b, a) \
  itemDef \
  { \
    rect        px py pw ph \
    type        ITEM_TYPE_TEXT \
    textfont    UI_FONT_NORMAL \
    textscale   0.36 \
    textstyle   ITEM_TEXTSTYLE_SHADOWED \
    exp         text( ptext ) \
    textalign   palign \
    forecolor   r g b a \
    visible     1 \
    decoration \
  }

// itemDef { \
//   rect (SUBMENU_CENTER_X) (SUBMENU_CENTER_Y - MENUFRAME_SUBMENU_H / 2) 220 MENUFRAME_SUBMENU_H DR_BUTTON_ALIGN \
//   textScale 0.33 \
//   textFont UI_FONT_NORMAL \
//   textalign ITEM_ALIGN_CENTER \
//   textalignx 0 \
//   textaligny 0 \
//   forecolor 1 1 1 1 \
//   exp			text( "^7"+tableLookup(ITEM_TABLE, 0, dvarInt("drui_weapon"), 5) ) \
//   visible		 when( rank >= tableLookup(ITEM_TABLE, 0, dvarInt("drui_weapon"), 2) && dvarString("customize_table") == "weapons" ) \
//   decoration \
// } \

// access to TEXT_CONTAINER_(WIDTH, HEIGHT, Y, X) should be assumed

#ifndef TEXT_CONTAINER_WIDTH
#define TEXT_CONTAINER_WIDTH 220
#endif

#ifndef TEXT_CONTAINER_HEIGHT
#define TEXT_CONTAINER_HEIGHT (MENUFRAME_SUBMENU_H - 20)
#endif

#ifndef TEXT_CONTAINER_X
#define TEXT_CONTAINER_X (SUBMENU_CENTER_X - TEXT_CONTAINER_WIDTH / 4)
#endif

#ifndef TEXT_CONTAINER_Y
#define TEXT_CONTAINER_Y (SUBMENU_CENTER_Y - TEXT_CONTAINER_HEIGHT - 20)
#endif

#define ITEM_TEXT_WIDTH TEXT_CONTAINER_WIDTH
#define ITEM_TEXT_HEIGHT (TEXT_CONTAINER_HEIGHT - 20)
#define ITEM_TEXT_X TEXT_CONTAINER_X
#define ITEM_TEXT_Y (TEXT_CONTAINER_Y + 19)

#define ITEM_TEXT(id) \
/** START CHARACTER TEXT */ \
itemDef { \
  rect ITEM_TEXT_X ITEM_TEXT_Y ITEM_TEXT_WIDTH ITEM_TEXT_HEIGHT DX_BTN_ALIGN \
  textScale 0.3 \
  textFont UI_FONT_NORMAL \
  textalign ITEM_ALIGN_CENTER \
  forecolor 1 1 1 1 \
  exp			text( "^7"+tableLookup(CHARACTER_TABLE, 0, CHARACTER_IDX, 4)+" ^1(Unlocked at prestige "+tableLookup(CHARACTER_TABLE, 0, CHARACTER_IDX, 5)+")" ) \
  visible		when( CURRENT_TABLE == "characters" && (prestige < tableLookup(CHARACTER_TABLE, 0, CHARACTER_IDX, 5)) ) \
  decoration \
} \
itemDef { \
  rect ITEM_TEXT_X ITEM_TEXT_Y ITEM_TEXT_WIDTH ITEM_TEXT_HEIGHT DX_BTN_ALIGN \
  textScale 0.3 \
  textFont UI_FONT_NORMAL \
  textalign ITEM_ALIGN_CENTER \
  forecolor 1 1 1 1 \
  exp			text( "^7"+tableLookup(CHARACTER_TABLE, 0, CHARACTER_IDX, 4)+" ^1(Unlocked at rank "+tableLookup(CHARACTER_TABLE, 0, CHARACTER_IDX, 2)+")" ) \
  visible		when( CURRENT_TABLE == "characters" && (prestige >= tableLookup(CHARACTER_TABLE, 0, CHARACTER_IDX, 5) && rank < tableLookup(CHARACTER_TABLE, 0, CHARACTER_IDX, 2)) ) \
  decoration \
} \
itemDef { \
  rect ITEM_TEXT_X ITEM_TEXT_Y ITEM_TEXT_WIDTH ITEM_TEXT_HEIGHT DX_BTN_ALIGN \
  textScale 0.33 \
  textFont UI_FONT_NORMAL \
  textalign ITEM_ALIGN_CENTER \
  textalignx 0 \
  textaligny 0 \
  forecolor 1 1 1 1 \
  exp			text( "^7"+tableLookup(CHARACTER_TABLE, 0, CHARACTER_IDX, 4) ) \
  visible		when( CURRENT_TABLE == "characters" && (prestige >= tableLookup(CHARACTER_TABLE, 0, CHARACTER_IDX, 5) && rank >= tableLookup(CHARACTER_TABLE, 0, CHARACTER_IDX, 2)) ) \
  decoration \
} \
/* END CHARACTER TEXT */ \
/* START WEAPON TEXT */ \
itemDef { \
  rect ITEM_TEXT_X ITEM_TEXT_Y ITEM_TEXT_WIDTH ITEM_TEXT_HEIGHT DX_BTN_ALIGN \
  textScale 0.33 \
  textFont UI_FONT_NORMAL \
  textalign ITEM_ALIGN_CENTER \
  textalignx 0 \
  textaligny 0 \
  forecolor 1 1 1 1 \
  exp			text( "^7"+tableLookup(ITEM_TABLE, 0, WEAPON_IDX, 5)+" ^1(Unlocked at prestige "+tableLookup(ITEM_TABLE, 0, WEAPON_IDX, 6)+")" ) \
  visible		when( CURRENT_TABLE == "weapons" && (prestige < tableLookup(ITEM_TABLE, 0, WEAPON_IDX, 6) ) ) \
  decoration \
} \
itemDef { \
  rect ITEM_TEXT_X ITEM_TEXT_Y ITEM_TEXT_WIDTH ITEM_TEXT_HEIGHT DX_BTN_ALIGN \
  textScale 0.33 \
  textFont UI_FONT_NORMAL \
  textalign ITEM_ALIGN_CENTER \
  textalignx 0 \
  textaligny 0 \
  forecolor 1 1 1 1 \
  exp			text( "^7"+tableLookup(ITEM_TABLE, 0, WEAPON_IDX, 5)+" ^1(Unlocked at rank "+tableLookup(ITEM_TABLE, 0, WEAPON_IDX, 2)+")" ) \
  visible		when( CURRENT_TABLE == "weapons" && (prestige >= tableLookup(ITEM_TABLE, 0, WEAPON_IDX, 6) && rank < tableLookup(ITEM_TABLE, 0, WEAPON_IDX, 2)) ) \
  decoration \
} \
itemDef { \
  rect ITEM_TEXT_X ITEM_TEXT_Y ITEM_TEXT_WIDTH ITEM_TEXT_HEIGHT DX_BTN_ALIGN \
  textScale 0.33 \
  textFont UI_FONT_NORMAL \
  textalign ITEM_ALIGN_CENTER \
  textalignx 0 \
  textaligny 0 \
  forecolor 1 1 1 1 \
  exp			text( "^7"+tableLookup(ITEM_TABLE, 0, WEAPON_IDX, 5) ) \
  visible		when( CURRENT_TABLE == "weapons" && (prestige >= tableLookup(ITEM_TABLE, 0, WEAPON_IDX, 6) && rank >= tableLookup(ITEM_TABLE, 0, WEAPON_IDX, 2)) ) \
  decoration \
} \
/* END WEAPON TEXT */
// itemDef { \
//   rect (SUBMENU_CENTER_X + 90) (SUBMENU_CENTER_Y - MENUFRAME_SUBMENU_H / 2) 220 MENUFRAME_SUBMENU_H DX_BTN_ALIGN \
//   textScale 0.33 \
//   textFont UI_FONT_NORMAL \
//   textalign ITEM_ALIGN_CENTER \
//   textalignx 0 \
//   textaligny 0 \
//   forecolor 1 1 1 1 \
//   exp			text( "^7"+tableLookup(CHARACTER_TABLE, 0, dvarInt("drui_character"), 1)+" ^1(Unlocked at "+tableLookup(CHARACTER_TABLE, 0, dvarInt("drui_character"), 2)+")" ) \
//   visible		when( rank < tableLookup(CHARACTER_TABLE, 0, dvarInt("drui_character"), 2) && dvarString("customize_table") == "characters" ) \
//   decoration \
// }

#endif // DX_COMMON_INC


#ifndef DX_BUTTON_INC
#define DX_BUTTON_INC 1

// ================= Tunables =================
#define DX_BTN_BACKGROUND                 "button_bg"
#define DX_BTN_FORECOLOR                  1 1 1 1
#define DX_BTN_BORDERCOLOR                0.50 0.50 0.50 0.15
#define DX_BTN_TEXTSIZE                   0.28
#define DX_BTN_ALIGN                      0 0 /*HORIZONTAL_ALIGN_FULLSCREEN VERTICAL_ALIGN_FULLSCREEN*/

// Phases (0..1)
#define DX_PHASE ((milliseconds()%1600)/1600)
#define DX_PHASE_R (1 - DX_PHASE)

// ================ DX_BUTTON (dual scanner) ================
// idStr, fxStr must be strings. Example:
//   DX_BUTTON("btnPlay","btnPlay_fx", 100,110, 180,20, "@DRM_PLAY", scriptMenuResponse "autoassign";, 1)
#define DX_BUTTON(idStr, fxStr, x, y, itemName, itemAction, visArg) \
  /* soft focus glow */ \
  itemDef { \
    name        fxStr \
    style       WINDOW_STYLE_SHADER \
    background  "gradient_center" \
    forecolor   DX_THEME 0.16 \
    visible     0 \
    decoration \
    exp rect X( x - 1 ) \
    exp rect Y( y - 1 ) \
    exp rect W( DX_BTN_WIDTH + 4 ) \
    exp rect H( DX_BTN_HEIGHT + 4 ) \
  } \
  /* top scanner: left -> right */ \
  itemDef { \
    name        fxStr "_lr" \
    style       WINDOW_STYLE_SHADER \
    background  "white" \
    forecolor   DX_THEME 1 \
    visible     0 \
    decoration \
    exp rect X( x + (DX_BTN_WIDTH - (DX_BTN_WIDTH / 4)) * DX_PHASE ) \
    exp rect Y( y ) \
    exp rect W( DX_BTN_WIDTH / 4 ) \
    exp rect H( 3 ) \
  } \
  /* bottom scanner: right -> left */ \
  itemDef { \
    name        fxStr "_rl" \
    style       WINDOW_STYLE_SHADER \
    background  "white" \
    forecolor   DX_THEME_DARK 1 \
    visible     0 \
    decoration \
    exp rect X( x + (DX_BTN_WIDTH - (DX_BTN_WIDTH / 4)) * DX_PHASE_R ) \
    exp rect Y( y + DX_BTN_HEIGHT - 1 ) \
    exp rect W( DX_BTN_WIDTH / 4 ) \
    exp rect H( 3 ) \
  } \
  /* main clickable button */ \
  itemDef { \
    name        idStr \
    visible     visArg \
    rect        x y DX_BTN_WIDTH DX_BTN_HEIGHT DX_BTN_ALIGN \
    style       WINDOW_STYLE_SHADER \
    background  DX_BTN_BACKGROUND \
    border      1 \
    bordercolor DX_BTN_BORDERCOLOR \
    type        ITEM_TYPE_BUTTON \
    textfont    UI_FONT_NORMAL \
    textstyle   ITEM_TEXTSTYLE_NORMAL \
    textalign   ITEM_ALIGN_CENTER \
    textscale   DX_BTN_TEXTSIZE \
    textalignx  0 \
    textaligny  (DX_BTN_HEIGHT - 5) \
    forecolor   DX_BTN_FORECOLOR \
    exp         text( itemName ) \
    mouseEnter  { \
      play "mouse_over"; \
      show fxStr; \
      show fxStr "_lr"; \
      show fxStr "_rl"; \
    } \
    mouseExit   { \
      hide fxStr; \
      hide fxStr "_lr"; \
      hide fxStr "_rl"; \
    } \
    action      { play "mouse_click"; itemAction } \
  }

#define DR_BUTTON(idStr, x, y, itemName, itemAction, visArg) \
  DX_BUTTON(idStr, idStr"_fx", x, y, itemName, itemAction, visArg)

// Button tints (normal / hover)
#define DX_BTN_TINT_NORMAL    1 1 1 1
#define DX_BTN_TINT_HOVER     1 1 1 1

// ================ DX_BUTTON_SIMPLE =================
// Usage:
//   DX_BUTTON_SIMPLE("btnPlay", 100, 110, "@DRM_PLAY", { scriptMenuResponse "autoassign"; }, 1)
#define DX_BUTTON_SIMPLE(idStr, x, y, itemName, itemActionBlock, visArg) \
  itemDef { \
    name        idStr \
    visible     visArg \
    rect        x y DX_BTN_WIDTH DX_BTN_HEIGHT DX_BTN_ALIGN \
    style       WINDOW_STYLE_SHADER \
    background  DX_BTN_BACKGROUND \
    forecolor   DX_BTN_TINT_NORMAL \
    border      1 \
    bordercolor DX_BTN_BORDERCOLOR \
    type        ITEM_TYPE_BUTTON \
    textfont    UI_FONT_NORMAL \
    textstyle   ITEM_TEXTSTYLE_NORMAL \
    textalign   ITEM_ALIGN_CENTER \
    textscale   DX_BTN_TEXTSIZE \
    textalignx  0 \
    textaligny  (DX_BTN_HEIGHT - 5) \
    exp         text( itemName ) \
    mouseEnter  { play "mouse_over"; setitemcolor self bordercolor DX_BTN_TINT_HOVER; } \
    mouseExit   { setitemcolor self bordercolor DX_BTN_BORDERCOLOR; } \
    action      { play "mouse_click"; itemActionBlock } \
  }