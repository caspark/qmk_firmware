#include QMK_KEYBOARD_H

enum kinesis_layers {
  _COLEMAK,   // Colemak (default layer)
};

//Aliases for longer keycodes
#define CTLESC  CTL_T(KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_COLEMAK] = LAYOUT_pretty( // default base layer
//_____ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,/**/ _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______,
KC_ESC  ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_F6   ,KC_F7   ,KC_F8   ,/**/ KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,KC_PSCR ,KC_SLCK ,KC_PAUS ,KC_INS  ,RESET  ,
KC_EQL  ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5                                /**/                           ,KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_MINS,
KC_TAB  ,KC_Q    ,KC_W    ,KC_F    ,KC_P    ,KC_G                                /**/                           ,KC_J    ,KC_L    ,KC_U    ,KC_Y    ,KC_SCLN ,KC_BSLS,
CTLESC  ,KC_A    ,KC_R    ,KC_S    ,KC_T    ,KC_D                                /**/                           ,KC_H    ,KC_N    ,KC_E    ,KC_I    ,KC_O    ,KC_QUOT,
KC_LSPO ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B                                /**/                           ,KC_K    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_RSPC,
         KC_GRV , KC_LGUI ,KC_LBRC ,KC_RBRC                                      /**/                                    ,KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT ,
                                                               KC_CAPS ,KC_LALT ,/**/ KC_RGUI ,KC_RCTL ,
                                                                        KC_LALT ,/**/ KC_PGUP ,
                                                       KC_SPC ,KC_LCTRL,KC_DEL  ,/**/ KC_PGDN ,KC_ENTER,KC_BSPC
)
};

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void led_set_user(uint8_t usb_led) {

}
