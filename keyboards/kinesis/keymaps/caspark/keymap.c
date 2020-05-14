#include QMK_KEYBOARD_H

enum kinesis_layers {
  LAYER_COLEMAK,   // Colemak (default layer)
  LAYER_SYMBOLS,   // Symbols, numbers, and function keys
  LAYER_EDITING,   // Shortcuts for editing text (arrow keys and more)
  LAYER_GUI,       // Shortcuts for navigating GUIs (mouse keys and more)
  LAYER_TEMPLATE,  // template layer for easy copy pasting to make new layers (not a real layer)
};

enum custom_keycodes {
  MNYUP = SAFE_RANGE, // hit up a bunch of times
  MNYDOWN, // hit down a bunch of times
};

// Tap dancing setup - https://docs.qmk.fm/#/feature_tap_dance
enum {
  TD_COLON = 0,
  TD_LBRACK,
  TD_RBRACK,
};
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_COLON] = ACTION_TAP_DANCE_DOUBLE(KC_COLN, KC_SCLN),
  [TD_LBRACK] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_LPRN),
  [TD_RBRACK] = ACTION_TAP_DANCE_DOUBLE(KC_RBRC, KC_RPRN),
};

// Aliases for longer keycodes
//     "12345678" is a visual guide to help ensure aliases are 8 characters or less so they fit
// basic keys
#define WRDLEFT  LCTL(KC_LEFT)
#define WRDRGHT  LCTL(KC_RGHT)
#define DOCHOME  LCTL(KC_HOME)
#define DOCEND   LCTL(KC_END)
#define WRDBSPC  LCTL(KC_BSPACE)
#define WRDDEL   LCTL(KC_DEL)
#define UNDO     LCTL(KC_Z)
#define CUT      LCTL(KC_X)
#define COPY     LCTL(KC_C)
#define PASTE    LCTL(KC_V)
#define REDO     LCTL(KC_Y)
// mod taps - https://docs.qmk.fm/#/mod_tap
#define CTLESC   MT(MOD_LCTL, KC_ESC)
// one shot modifiers - https://docs.qmk.fm/#/one_shot_keys
#define ONE_ALT  OSM(MOD_LALT)
#define ONE_SFT  OSM(MOD_LSFT)
// tap tances - https://docs.qmk.fm/#/feature_tap_dance
#define COLONS   TD(TD_COLON)
#define LBRACKS  TD(TD_LBRACK)
#define RBRACKS  TD(TD_RBRACK)
// layers - https://docs.qmk.fm/#/feature_layers
#define ENT_SYM  LT(LAYER_SYMBOLS, KC_ENTER) // layer or tab
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
 KC_ESC  ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_F6   ,KC_F7   ,KC_F8   /**/,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,KC_PSCR ,KC_SLCK ,KC_PAUS ,KC_INS  ,RESET
,KC_EQL  ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5                               /**/                           ,KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_MINS
,KC_TAB  ,KC_Q    ,KC_W    ,KC_F    ,KC_P    ,KC_G                               /**/                           ,KC_J    ,KC_L    ,KC_U    ,KC_Y    ,KC_SCLN ,KC_BSLS
,LAY_GUI ,KC_A    ,KC_R    ,KC_S    ,KC_T    ,KC_D                               /**/                           ,KC_H    ,KC_N    ,KC_E    ,KC_I    ,KC_O    ,KC_QUOT
,ONE_SFT ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B                               /**/                           ,KC_K    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_TAB
         ,XXXXXXX ,KC_LGUI ,LBRACKS ,RBRACKS                                     /**/                                    ,KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT
                                                               ,LAY_EDT ,KC_CAPS /**/,XXXXXXX ,KC_DEL
                                                                        ,ONE_ALT /**/,KC_PGUP
                                                      ,KC_SPC  ,CTLESC  ,COLONS  /**/,KC_PGDN ,ENT_SYM  ,KC_BSPC
)

,[LAYER_SYMBOLS] = LAYOUT_pretty( // function keys on number row, numbers and symbols on home row
//______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ /**/,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
 _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ /**/,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
,KC_F12  ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5                              /**/                           ,KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11
,_______ ,KC_EXLM ,KC_AT   ,KC_HASH ,KC_DLR  ,_______                            /**/                           ,_______ ,KC_AMPR ,KC_ASTR ,KC_BSLS ,KC_PIPE ,_______
,_______ ,KC_TILD ,KC_GRV  ,KC_EQL  ,KC_0    ,KC_PERC                            /**/                           ,KC_CIRC ,KC_1    ,KC_MINS ,KC_PLUS ,KC_UNDS ,KC_DQUO
,_______ ,KC_6    ,KC_7    ,KC_8    ,KC_9    ,_______                            /**/                           ,_______ ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,_______
         ,_______ ,_______ ,_______ ,_______                                     /**/                                    ,_______ ,_______ ,_______ ,_______
                                                               ,_______ ,_______ /**/,_______ ,_______
                                                                        ,_______ /**/,_______
                                                      ,_______ ,_______ ,_______ /**/,_______ ,_______ ,_______
)

,[LAYER_EDITING] = LAYOUT_pretty( // arrow keys and other editing aids
//______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ /**/,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
 _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ /**/,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
,_______ ,_______ ,_______ ,_______ ,_______ ,_______                            /**/                           ,_______ ,_______ ,DOCHOME ,DOCEND  ,_______ ,_______
,_______ ,_______ ,_______ ,_______ ,_______ ,_______                            /**/                           ,_______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______
,_______ ,_______ ,_______ ,_______ ,_______ ,_______                            /**/                           ,KC_HOME ,KC_LEFT ,KC_DOWN, KC_UP   ,KC_RGHT ,KC_END
,_______ ,UNDO    ,CUT     ,COPY    ,PASTE   ,REDO                               /**/                           ,_______ ,WRDLEFT ,MNYDOWN ,MNYUP   ,WRDRGHT ,_______
         ,_______ ,_______ ,_______ ,_______                                     /**/                                    ,_______ ,_______ ,_______ ,_______
                                                               ,_______ ,_______ /**/,_______ ,WRDDEL
                                                                        ,_______ /**/,_______
                                                      ,_______ ,_______ ,_______ /**/,_______ ,_______ ,WRDBSPC
)

,[LAYER_GUI] = LAYOUT_pretty( // mouse keys
//______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ /**/,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
 _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ /**/,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
,_______ ,_______ ,_______ ,_______ ,_______ ,_______                            /**/                           ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
,_______ ,XXXXXXX ,KC_WH_L ,KC_MS_U ,KC_WH_R ,KC_WH_U                            /**/                           ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
,_______ ,XXXXXXX ,KC_MS_L ,KC_MS_D ,KC_MS_R ,KC_WH_D                            /**/                           ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
,_______ ,_______ ,_______ ,_______ ,_______ ,_______                            /**/                           ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
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
