#include QMK_KEYBOARD_H

enum kinesis_layers {
  LAYER_COLEMAK,   // Colemak (default layer)
  LAYER_SYMBOLS,   // Symbols, numbers, and function keys
  LAYER_TEMPLATE,  // template layer for easy copy pasting to make new layers (not a real layer)
};

enum custom_keycodes {
  ALT_TAB = SAFE_RANGE
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
#define CTLESC   CTL_T(KC_ESC)
#define COLONS   TD(TD_COLON)
#define LBRACKS  TD(TD_LBRACK)
#define RBRACKS  TD(TD_RBRACK)
#define TAB_SYM  LT(LAYER_SYMBOLS, KC_TAB)

// alt tab mode: hit the ALT_TAB key to switch once, also allows cycling through options (see code)
bool alt_tab_activated;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[LAYER_COLEMAK] = LAYOUT_pretty( // default base layer
//______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ /**/,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______
 KC_ESC  ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_F6   ,KC_F7   ,KC_F8   /**/,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,KC_PSCR ,KC_SLCK ,KC_PAUS ,KC_INS  ,RESET
,KC_EQL  ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5                               /**/                           ,KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_MINS
,KC_TAB  ,KC_Q    ,KC_W    ,KC_F    ,KC_P    ,KC_G                               /**/                           ,KC_J    ,KC_L    ,KC_U    ,KC_Y    ,KC_SCLN ,KC_BSLS
,ALT_TAB ,KC_A    ,KC_R    ,KC_S    ,KC_T    ,KC_D                               /**/                           ,KC_H    ,KC_N    ,KC_E    ,KC_I    ,KC_O    ,KC_QUOT
,KC_LSPO ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B                               /**/                           ,KC_K    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_RSPC
         ,KC_GRV  ,KC_LGUI ,LBRACKS ,RBRACKS                                     /**/                                    ,KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT
                                                               ,KC_CAPS ,KC_LALT /**/,COLONS  ,TAB_SYM
                                                                        ,KC_LALT /**/,KC_PGUP
                                                      ,KC_SPC  ,CTLESC  ,KC_DEL  /**/,KC_PGDN ,KC_ENTER,KC_BSPC
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

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ALT_TAB:
      alt_tab_activated = record->event.pressed;
      if (alt_tab_activated) {
        register_code(KC_LALT);
        tap_code(KC_TAB);
      } else {
        unregister_code(KC_LALT);
      }
      break;
    case CTLESC:
      if (alt_tab_activated) {
        if (record->event.pressed) {
          tap_code(KC_TAB);
        }
        return false;
      }
    case KC_SPC:
      if (alt_tab_activated) {
        if (record->event.pressed) {
          register_code(KC_LSFT);
          tap_code(KC_TAB);
          unregister_code(KC_LSFT);
        }
        return false;
      }
      break;
  }
  return true;
};

void led_set_user(uint8_t usb_led) {

}
