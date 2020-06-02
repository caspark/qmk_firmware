#include QMK_KEYBOARD_H

enum kinesis_layers {
  LAYER_COLEMAK,   // Colemak (default layer)
  LAYER_QWERTY,    // Qwerty layer (alternate default layer)
  LAYER_GAMING,    // Gaming layer, with WASD mapped to qwerty's ESDF (alternate default layer)
  LAYER_SYMBOLS,   // Symbols, numbers, and function keys
  LAYER_EDITING,   // Shortcuts for editing text (arrow keys and more)
  LAYER_GUI,       // Shortcuts for navigating GUIs (mouse keys and more)
  LAYER_ADJUST,    // Mechanism for configuring the keyboard and swapping the base layers
  LAYER_TEMPLATE,  // template layer for easy copy pasting to make new layers (not a real layer)
};

enum custom_keycodes {
  TRU_ESC = SAFE_RANGE, // send escape but also reset to default layer
  CLN_EDT,
  MNYUP, // hit up at a high key repeat rate
  MNYDOWN, // hit down at a high key repeat rate
  MNYLEFT, // hit left at a high key repeat rate
  MNYRGHT, // hit right at a high key repeat rate
  RM_LINE, // remove the current line of text
};

// Tap dancing setup - https://docs.qmk.fm/#/feature_tap_dance
enum {
  TD_COLON = 0,
};
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_COLON] = ACTION_TAP_DANCE_DOUBLE(KC_COLN, KC_SCLN),
};

// Aliases for longer keycodes
//     "12345678" is a visual guide to help ensure aliases are 8 characters or less so they fit
// basic keys
#define WRDLFT   LCTL(KC_LEFT)
#define WRDRGT   LCTL(KC_RGHT)
#define SEL_LFT  LSFT(KC_LEFT)
#define SEL_RGT  LSFT(KC_RGHT)
#define SEL_UP   LSFT(KC_UP)
#define SEL_DWN  LSFT(KC_DOWN)
#define SWRDLFT  LCTL(LSFT(KC_LEFT))
#define SWRDRGT  LCTL(LSFT(KC_RGHT))
#define SEL_HOM  LSFT(KC_HOME)
#define SEL_END  LSFT(KC_END)
#define ALT_UP   LALT(KC_UP)
#define ALT_DWN  LALT(KC_DOWN)
#define DOCHOME  LCTL(KC_HOME)
#define DOCEND   LCTL(KC_END)
#define WRDBSPC  LCTL(KC_BSPACE)
#define WRDDEL   LCTL(KC_DEL)
#define UNDO     LCTL(KC_Z)
#define CUT      LCTL(KC_X)
#define COPY     LCTL(KC_C)
#define PASTE    LCTL(KC_V)
#define REDO     LCTL(KC_Y)
#define CLS_TAB  LCTL(KC_F4)
#define CLS_WIN  LALT(KC_F4)
// mod taps - https://docs.qmk.fm/#/mod_tap
#define CTL_ESC   MT(MOD_LCTL, KC_ESC)
// one shot modifiers - https://docs.qmk.fm/#/one_shot_keys
#define ONE_ALT  OSM(MOD_LALT)
// tap tances - https://docs.qmk.fm/#/feature_tap_dance
#define COLONS   TD(TD_COLON)
// layers - https://docs.qmk.fm/#/feature_layers
#define LAY_ADJ  MO(LAYER_ADJUST) // momentary layer
#define LAY_COL  DF(LAYER_COLEMAK) // set default layer
#define LAY_QWE  DF(LAYER_QWERTY) // set default layer
#define LAY_GAM  DF(LAYER_GAMING) // set default layer
#define ENT_SYM  LT(LAYER_SYMBOLS, KC_ENTER) // layer or enter
#define LAY_EDT  CLN_EDT // layer or tab
#define OSL_GUI  OSL(LAYER_GUI) // one shot layer - hold to use layer, tap once to use once, or tap twice to toggle layer
#define MO_GUI   MO(LAYER_GUI) // momentary layer
#define TAB_GUI  LT(LAYER_GUI, KC_TAB) // layer or tab

// special alt tab replacement: hold CTL_ESC and hit OSL_GUI one or more times to trigger alt tab
bool ctlesc_down;
bool alt_tab_activated;

// colon "layer tap", which we can't do using the LT macro because colon is not a standard keycode
// (and using tap dance means that interuptions before the "hold" point will send the colon)
bool lt_colon_held;
bool lt_colon_other_key_pressed;

// "many press" is a way to override operating system's key repeat logic to get keys to repeat
// faster or with less delay before the repeating starts.
#define MANY_PRESS_REPEAT_DELAY_MS 5
#define MANY_PRESS_REPEAT_DELAY_INITIAL_MS 100
#define MANY_PRESS_INIT(name, keycode)  \
uint16_t many_press_##name##_timer; \
bool many_press_##name##_held; \
bool many_press_##name##_repeating; \
uint16_t many_press_##name##_underlying = keycode;
#define MANY_PRESS_PROCESS_RECORD(name)  if (record->event.pressed) { \
  tap_code(many_press_##name##_underlying); \
  many_press_##name##_held = true; \
  many_press_##name##_timer = timer_read(); \
} else { \
  many_press_##name##_held = false; \
  many_press_##name##_repeating = false; \
}
#define MANY_PRESS_IF_MANY_KEY_HELD_THEN_REPEAT(name) if (many_press_##name##_held && \
    ( \
      (many_press_##name##_repeating && timer_elapsed(many_press_##name##_timer) > MANY_PRESS_REPEAT_DELAY_MS) \
    || \
      (!many_press_##name##_repeating && timer_elapsed(many_press_##name##_timer) > MANY_PRESS_REPEAT_DELAY_INITIAL_MS) \
    )) { \
  many_press_##name##_repeating = true; \
  tap_code(many_press_##name##_underlying); \
  many_press_##name##_timer = timer_read(); \
}

MANY_PRESS_INIT(up, KC_UP)
MANY_PRESS_INIT(down, KC_DOWN)
MANY_PRESS_INIT(left, KC_LEFT)
MANY_PRESS_INIT(right, KC_RGHT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[LAYER_COLEMAK] = LAYOUT_pretty( // default base layer
//______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ /**/,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
 TRU_ESC ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_F6   ,KC_F7   ,KC_F8   /**/,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,KC_PSCR ,KC_SLCK ,KC_PAUS ,KC_INS  ,LAY_ADJ
,KC_EQL  ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5                               /**/                           ,KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_MINS
,KC_TAB  ,KC_Q    ,KC_W    ,KC_F    ,KC_P    ,KC_B                               /**/                           ,KC_J    ,KC_L    ,KC_U    ,KC_Y    ,KC_SCLN ,KC_BSLS
,OSL_GUI ,KC_A    ,KC_R    ,KC_S    ,KC_T    ,KC_G                               /**/                           ,KC_M    ,KC_N    ,KC_E    ,KC_I    ,KC_O    ,KC_QUOT
,KC_LSFT ,KC_Z    ,KC_X    ,KC_C    ,KC_D    ,KC_V                               /**/                           ,KC_K    ,KC_H    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_DEL
         ,KC_GRV  ,KC_LGUI ,KC_LBRC ,KC_RBRC                                     /**/                                    ,KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT
                                                               ,LAY_EDT ,KC_CAPS /**/,XXXXXXX ,TAB_GUI
                                                                        ,ONE_ALT /**/,KC_PGUP
                                                      ,KC_SPC  ,CTL_ESC ,COLONS  /**/,KC_PGDN ,ENT_SYM ,KC_BSPC
)

,[LAYER_QWERTY] = LAYOUT_pretty( // qwerty layout, where every key does what it says on the keyboard (except maybe one or two of the function keys)
//______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ /**/,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
 TRU_ESC ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_F6   ,KC_F7   ,KC_F8   /**/,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,KC_PSCR ,KC_SLCK ,KC_PAUS ,KC_INS  ,LAY_ADJ
,KC_EQL  ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5                               /**/                           ,KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_MINS
,KC_TAB  ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T                               /**/                           ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_BSLS
,KC_CAPS ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G                               /**/                           ,KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_QUOT
,KC_LSFT ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B                               /**/                           ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_RSFT
         ,KC_GRV  ,KC_PIPE ,KC_LEFT ,KC_RGHT                                     /**/                                    ,KC_UP   ,KC_DOWN ,KC_LBRC ,KC_RBRC
                                                               ,KC_LCTL ,KC_LALT /**/,KC_RGUI ,KC_RCTL
                                                                        ,KC_HOME /**/,KC_PGUP
                                                      ,KC_BSPC ,KC_DEL  ,KC_END  /**/,KC_PGDN ,KC_ENT  ,KC_SPC
)

,[LAYER_GAMING] = LAYOUT_pretty( // gaming layer - WASD is moved one row to the right, with TGB moving to where QAZ is normally (and stuff like GRV becomes LCTL)
//______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ /**/,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
 _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ /**/,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
,_______ ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5                               /**/                           ,KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,_______
,_______ ,KC_T    ,KC_Q    ,KC_W    ,KC_E    ,KC_R                               /**/                           ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,_______
,MO_GUI  ,KC_G    ,KC_A    ,KC_S    ,KC_D    ,KC_F                               /**/                           ,KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,_______
,_______ ,KC_B    ,KC_Z    ,KC_X    ,KC_C    ,KC_V                               /**/                           ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,_______
         ,KC_LCTL ,KC_LALT ,KC_LEFT ,KC_RGHT                                     /**/                                    ,KC_UP   ,KC_DOWN ,KC_LBRC ,KC_RBRC
                                                               ,KC_G    ,_______ /**/,_______ ,_______
                                                                        ,KC_LALT /**/,_______
                                                      ,_______ ,_______ ,_______ /**/,_______ ,_______ ,_______
)

// Character Frequencies Reference from http://xahlee.info/comp/computer_language_char_distribution.html
// KC_DOT (6.6), KC_COMM (5.8), KC_QUOT (4.4), KC_SLSH (4.0), KC_SCLN (3.8) are accessible enough on the keyboard already, so we start with:
// KC_UNDS (11.4) and KC_LPRN + KC_RPRN (both 7.4) are most common by far, with remainder starting at 4.4:
// KC_EQL, KC_MINS, KC_DQUOT, KC_ASTR, KC_COLN, KC_LABK, KC_DLR, KC_0, KC_HASH are greater than 2%
// KC_LCBR, KC_RCBR, KC_1, KC_LABK, KC_AMPR, KC_BSLS, KC_2 are greater than 1%
// KC_LBRC, KC_LBRC, KC_AT, KC_PIPE, KC_PLUS are greater than 0.5%
// KC_3, KC_EXLM, KC_4, KC_PERC, KC_5, KC_8, KC_6, KC_QUES, KC_9, KC_7, KC_GRV, KC_TILD, KC_CIRC make up the remainder
,[LAYER_SYMBOLS] = LAYOUT_pretty( // function keys on number row, numbers and symbols on home row
//______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ /**/,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
 _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ /**/,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
,KC_EQL  ,KC_EXLM ,KC_AT   ,KC_HASH ,KC_DLR  ,KC_PERC                            /**/                           ,KC_CIRC ,KC_AMPR ,KC_ASTR ,KC_LPRN ,KC_RPRN ,KC_UNDS
,_______ ,_______ ,_______ ,_______ ,KC_LBRC ,KC_RBRC                            /**/                           ,_______ ,KC_1    ,KC_0    ,KC_BSLS ,KC_SCLN ,KC_PIPE
,_______ ,KC_QUES ,KC_PLUS ,KC_EQL  ,KC_LPRN ,KC_RPRN                            /**/                           ,_______ ,KC_UNDS ,KC_COLN ,KC_MINS ,KC_PIPE ,KC_DQUO
,_______ ,KC_GRV  ,KC_TILD ,KC_SLSH ,KC_LCBR ,KC_RCBR                            /**/                           ,_______ ,KC_ASTR ,_______ ,_______ ,_______, _______
         ,_______ ,_______ ,_______ ,_______                                     /**/                                    ,_______ ,_______ ,_______ ,_______
                                                               ,_______ ,_______ /**/,_______ ,_______
                                                                        ,_______ /**/,_______
                                                      ,_______ ,_______ ,_______ /**/,_______ ,_______ ,_______
)

,[LAYER_EDITING] = LAYOUT_pretty( // arrow keys and other editing aids
//______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ /**/,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
 _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ /**/,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
,_______ ,_______ ,_______ ,_______ ,_______ ,_______                            /**/                           ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
,_______ ,_______ ,SEL_HOM ,SEL_UP  ,SEL_END ,RM_LINE                            /**/                           ,ALT_UP  ,KC_HOME ,MNYUP   ,KC_END  ,XXXXXXX ,_______
,_______ ,SWRDLFT ,SEL_LFT ,SEL_DWN ,SEL_RGT ,SWRDRGT                            /**/                           ,XXXXXXX ,MNYLEFT ,MNYDOWN ,MNYRGHT ,XXXXXXX ,XXXXXXX
,_______ ,UNDO    ,CUT     ,COPY    ,PASTE   ,REDO                               /**/                           ,ALT_DWN ,WRDLFT  ,XXXXXXX ,WRDRGT  ,XXXXXXX ,WRDDEL
         ,_______ ,_______ ,_______ ,_______                                     /**/                                    ,KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT
                                                               ,_______ ,_______ /**/,_______ ,_______
                                                                        ,_______ /**/,DOCHOME
                                                      ,_______ ,_______ ,_______ /**/,DOCEND  ,_______ ,WRDBSPC
)

,[LAYER_GUI] = LAYOUT_pretty( // mouse keys and other utilities
//______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ /**/,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
 _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ /**/,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
,KC_F12  ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5                              /**/                           ,KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11
,_______ ,XXXXXXX ,KC_WH_L ,KC_MS_U ,KC_WH_R ,KC_WH_U                            /**/                           ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
,_______ ,XXXXXXX ,KC_MS_L ,KC_MS_D ,KC_MS_R ,KC_WH_D                            /**/                           ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
,_______ ,_______ ,_______ ,CLS_TAB ,_______ ,_______                            /**/                           ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
         ,_______ ,_______ ,_______ ,CLS_WIN                                     /**/                                    ,_______ ,_______ ,_______ ,_______
                                                               ,KC_ACL0 ,KC_BTN3 /**/,_______ ,_______
                                                                        ,_______ /**/,_______
                                                      ,KC_BTN1 ,_______ ,KC_BTN2 /**/,_______ ,_______ ,_______
)

,[LAYER_ADJUST] = LAYOUT_pretty( // configure the keyboard
//______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ /**/,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
 XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX /**/,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,RESET   ,_______
,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX                            /**/                           ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,RESET   ,RESET
,XXXXXXX ,LAY_QWE ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX                            /**/                           ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,LAY_GAM                            /**/                           ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
,XXXXXXX ,XXXXXXX ,XXXXXXX ,LAY_COL ,XXXXXXX ,XXXXXXX                            /**/                           ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
         ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX                                     /**/                                    ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
                                                               ,XXXXXXX ,XXXXXXX /**/,XXXXXXX ,XXXXXXX
                                                                        ,XXXXXXX /**/,XXXXXXX
                                                      ,XXXXXXX ,XXXXXXX ,XXXXXXX /**/,XXXXXXX ,XXXXXXX ,XXXXXXX
)

,[LAYER_TEMPLATE] = LAYOUT_pretty( // template layer, for easy copy pasting to make a new layer
//______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ /**/,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
 _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ /**/,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
,_______ ,_______ ,_______ ,_______ ,_______ ,_______                            /**/                           ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
,_______ ,_______ ,_______ ,_______ ,_______ ,_______                            /**/                           ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
,_______ ,_______ ,_______ ,_______ ,_______ ,_______                            /**/                           ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
,_______ ,_______ ,_______ ,_______ ,_______ ,_______                            /**/                           ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
         ,_______ ,_______ ,_______ ,_______                                     /**/                                    ,_______ ,_______ ,_______ ,_______
                                                               ,_______ ,_______ /**/,_______ ,_______
                                                                        ,_______ /**/,_______
                                                      ,_______ ,_______ ,_______ /**/,_______ ,_______ ,_______
)

};


void matrix_init_user(void) {

}

void matrix_scan_user(void) {
  MANY_PRESS_IF_MANY_KEY_HELD_THEN_REPEAT(up)
  else MANY_PRESS_IF_MANY_KEY_HELD_THEN_REPEAT(down)
  else MANY_PRESS_IF_MANY_KEY_HELD_THEN_REPEAT(left)
  else MANY_PRESS_IF_MANY_KEY_HELD_THEN_REPEAT(right)
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (keycode == CLN_EDT) {
    if (record->event.pressed) {
      lt_colon_held = true;
      layer_on(LAYER_EDITING);
      lt_colon_other_key_pressed = false;
    } else {
      lt_colon_held = false;
      layer_off(LAYER_EDITING);
      if (!lt_colon_other_key_pressed) {
        register_code(KC_LSFT);
        tap_code(KC_SCLN);
        unregister_code(KC_LSFT);
      }
    }
    return false;
  } else {
    lt_colon_other_key_pressed = true;
  }

  switch (keycode) {
    case TRU_ESC:
      if (record->event.pressed) {
        layer_clear();
        register_code(KC_ESC);
      } else {
        unregister_code(KC_ESC);
      }
    break;
    case MNYUP:
      MANY_PRESS_PROCESS_RECORD(up);
      break;
    case MNYDOWN:
      MANY_PRESS_PROCESS_RECORD(down);
      break;
    case MNYLEFT:
      MANY_PRESS_PROCESS_RECORD(left);
      break;
    case MNYRGHT:
      MANY_PRESS_PROCESS_RECORD(right);
      break;
    case RM_LINE:
      if (record->event.pressed) {
        // this looks like an unnecessarily complicated way to delete a line, but it's necessary to cover:
        // - not changing/messing with indentation of line above/below
        // - "smart home" features in some editors
        // - working correctly when the line is the first/last line
        SEND_STRING(SS_TAP(X_HOME)SS_TAP(X_HOME)SS_DOWN(X_LSFT)SS_TAP(X_END)SS_TAP(X_RGHT)SS_UP(X_LSFT)SS_TAP(X_DEL));
      }
      break;
    case OSL_GUI:
      if (ctlesc_down) {
        if (record->event.pressed) {
          if (!alt_tab_activated) {
            alt_tab_activated = true;
            unregister_code(KC_LCTL);
            register_code(KC_LALT);
          }
          register_code(KC_TAB);
        } else {
          unregister_code(KC_TAB);
        }
        return false;
      }
      break;
    case CTL_ESC:
      if (record->event.pressed) {
        ctlesc_down = true;
      } else {
        if (alt_tab_activated) {
          unregister_code(KC_LALT);
          alt_tab_activated = false;
          ctlesc_down = false;
          return false;
        }
        ctlesc_down = false;
      }
      break;
  }
  return true;
};

void led_set_user(uint8_t usb_led) {

}
