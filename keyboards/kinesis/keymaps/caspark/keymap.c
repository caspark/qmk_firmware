#include QMK_KEYBOARD_H

enum kinesis_layers {
  LAYER_COLEMAK,   // Colemak (default layer)
  LAYER_SYMBOLS,   // Symbols, numbers, and function keys
  LAYER_EDITING,   // Shortcuts for editing text (arrow keys and more)
  LAYER_GUI,       // Shortcuts for navigating GUIs (mouse keys and more)
  LAYER_TEMPLATE,  // template layer for easy copy pasting to make new layers (not a real layer)
};

enum custom_keycodes {
  TRU_ESC = SAFE_RANGE, // send escape but also reset to default layer
  MNYUP, // hit up a bunch of times
  MNYDOWN, // hit down a bunch of times
  RM_LINE, // remove the current line of text
};

// Tap dancing setup - https://docs.qmk.fm/#/feature_tap_dance
enum {
  TD_COLON = 0,
  TD_LBRACK,
  TD_RBRACK,
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
#define CTLESC   MT(MOD_LCTL, KC_ESC)
// one shot modifiers - https://docs.qmk.fm/#/one_shot_keys
#define ONE_ALT  OSM(MOD_LALT)
#define ONE_SFT  OSM(MOD_LSFT)
// tap tances - https://docs.qmk.fm/#/feature_tap_dance
#define COLONS   TD(TD_COLON)
// layers - https://docs.qmk.fm/#/feature_layers
#define ENT_SYM  LT(LAYER_SYMBOLS, KC_ENTER) // layer or enter
#define LAY_EDT  MO(LAYER_EDITING) // momentary layer
#define LAY_GUI  OSL(LAYER_GUI) // one shot layer - hold to use layer, tap once to use once, or tap twice to toggle layer

// special alt tab replacement: hold CTLESC and hit LAY_GUI one or more times to trigger alt tab
bool ctlesc_down;
bool alt_tab_activated;

#define MANY_WORD_REPEAT_DELAY_MS 5
uint16_t many_word_up_timer;
bool many_word_up_held;
uint16_t many_word_down_timer;
bool many_word_down_held;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[LAYER_COLEMAK] = LAYOUT_pretty( // default base layer
//______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ /**/,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
 TRU_ESC ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_F6   ,KC_F7   ,KC_F8   /**/,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,KC_PSCR ,KC_SLCK ,KC_PAUS ,KC_INS  ,RESET
,KC_TILD ,KC_EXLM ,KC_AT   ,KC_HASH ,KC_DLR  ,KC_PERC                            /**/                           ,KC_CIRC ,KC_AMPR ,KC_ASTR ,KC_LPRN ,KC_RPRN ,KC_UNDS
,KC_TAB  ,KC_Q    ,KC_W    ,KC_F    ,KC_P    ,KC_G                               /**/                           ,KC_J    ,KC_L    ,KC_U    ,KC_Y    ,KC_SCLN ,KC_BSLS
,LAY_GUI ,KC_A    ,KC_R    ,KC_S    ,KC_T    ,KC_D                               /**/                           ,KC_H    ,KC_N    ,KC_E    ,KC_I    ,KC_O    ,KC_QUOT
,ONE_SFT ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B                               /**/                           ,KC_K    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_DEL
         ,XXXXXXX ,KC_LGUI ,KC_LABK ,KC_RABK                                     /**/                                    ,KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT
                                                               ,LAY_EDT ,KC_CAPS /**/,XXXXXXX ,KC_TAB
                                                                        ,ONE_ALT /**/,KC_PGUP
                                                      ,KC_SPC  ,CTLESC  ,COLONS  /**/,KC_PGDN ,ENT_SYM  ,KC_BSPC
)
,[LAYER_SYMBOLS] = LAYOUT_pretty( // function keys on number row, numbers and symbols on home row
//______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ /**/,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
 _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ /**/,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
,KC_F12  ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5                              /**/                           ,KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11
,_______ ,_______ ,_______ ,_______ ,_______ ,KC_LBRC                            /**/                           ,KC_RBRC ,_______ ,_______ ,_______ ,_______ ,_______
,_______ ,KC_GRV  ,KC_PLUS ,KC_0    ,KC_EQL  ,KC_LPRN                            /**/                           ,KC_RPRN ,KC_UNDS, KC_1    ,KC_MINS ,KC_PIPE ,KC_DQUO
,_______ ,KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_LCBR                            /**/                           ,KC_RCBR ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,_______
         ,_______ ,_______ ,_______ ,_______                                     /**/                                    ,_______ ,_______ ,_______ ,_______
                                                               ,_______ ,_______ /**/,_______ ,_______
                                                                        ,_______ /**/,_______
                                                      ,_______ ,_______ ,_______ /**/,_______ ,_______ ,_______
)

,[LAYER_EDITING] = LAYOUT_pretty( // arrow keys and other editing aids
//______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ /**/,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
 _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ /**/,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
,_______ ,_______ ,_______ ,_______ ,_______ ,_______                            /**/                           ,_______ ,DOCHOME ,MNYUP   ,DOCEND  ,_______ ,_______
,_______ ,_______ ,SEL_HOM ,SEL_UP  ,SEL_END ,RM_LINE                            /**/                           ,ALT_UP  ,KC_HOME ,KC_UP   ,KC_END  ,XXXXXXX ,_______
,_______ ,SWRDLFT ,SEL_LFT ,SEL_DWN ,SEL_RGT ,SWRDRGT                            /**/                           ,WRDLFT  ,KC_LEFT ,KC_DOWN ,KC_RGHT ,WRDRGT  ,XXXXXXX
,_______ ,UNDO    ,CUT     ,COPY    ,PASTE   ,REDO                               /**/                           ,ALT_DWN ,XXXXXXX ,MNYDOWN ,XXXXXXX ,XXXXXXX ,WRDDEL
         ,_______ ,_______ ,_______ ,_______                                     /**/                                    ,_______ ,_______ ,_______, _______
                                                               ,_______ ,_______ /**/,_______ ,_______
                                                                        ,_______ /**/,_______
                                                      ,_______ ,_______ ,_______ /**/,_______ ,_______ ,WRDBSPC
)

,[LAYER_GUI] = LAYOUT_pretty( // mouse keys and other utilities
//______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ /**/,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
 _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ /**/,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
,_______ ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5                               /**/                           ,KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,_______
,_______ ,XXXXXXX ,KC_WH_L ,KC_MS_U ,KC_WH_R ,KC_WH_U                            /**/                           ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
,_______ ,XXXXXXX ,KC_MS_L ,KC_MS_D ,KC_MS_R ,KC_WH_D                            /**/                           ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
,_______ ,_______ ,_______ ,CLS_TAB ,_______ ,CLS_WIN                            /**/                           ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
         ,_______ ,_______ ,_______ ,_______                                     /**/                                    ,_______ ,_______ ,_______ ,_______
                                                               ,KC_ACL0 ,_______ /**/,_______ ,_______
                                                                        ,_______ /**/,_______
                                                      ,KC_BTN1 ,KC_BTN2 ,KC_BTN3 /**/,_______ ,_______ ,_______
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
  if (many_word_up_held && timer_elapsed(many_word_up_timer) > MANY_WORD_REPEAT_DELAY_MS) {
    tap_code(KC_UP);
    many_word_up_timer = timer_read();
  } else if (many_word_down_held && timer_elapsed(many_word_down_timer) > MANY_WORD_REPEAT_DELAY_MS) {
    tap_code(KC_DOWN);
    many_word_down_timer = timer_read();
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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
      if (record->event.pressed) {
        tap_code(KC_UP);
        many_word_up_held = true;
        many_word_up_timer = timer_read();
      } else {
        many_word_up_held = false;
      }
      break;
    case MNYDOWN:
      if (record->event.pressed) {
        tap_code(KC_DOWN);
        many_word_down_held = true;
        many_word_down_timer = timer_read();
      } else {
        many_word_down_held = false;
      }
      break;
    case RM_LINE:
      if (record->event.pressed) {
        // this looks like an unnecessarily complicated way to delete a line, but it's necessary to cover:
        // - not changing/messing with indentation of line above/below
        // - "smart home" features in some editors
        // - working correctly when the line is the first/last line
        SEND_STRING(SS_TAP(X_HOME)SS_TAP(X_HOME)SS_DOWN(X_LSFT)SS_TAP(X_END)SS_TAP(X_RGHT)SS_UP(X_LSFT)SS_TAP(X_DEL));
      }
    case LAY_GUI:
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
    case CTLESC:
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
