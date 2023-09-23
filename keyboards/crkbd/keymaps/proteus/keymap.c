/* Copyright 2020 Dane Evans
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 2 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */

// CRKBD

#include QMK_KEYBOARD_H
// this will give me NO_ that I can use to get the norwagian keymaps 
#include "keymap_norwegian.h"
#include "tapdance.c"

// this define if a mod is locked
bool activMod = false;



char layer_state_str[24];

  enum userspace_layers {
	_COLEMAKDH,
    _NUM,
    _SYM,
    _NAV,
    _COM,
    _LNAV
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	// colemak DH
	[_COLEMAKDH] = LAYOUT(
	//,-----------------------------------------------------.                    ,-----------------------------------------------------.
	    KC_ESC, 	KC_Q, 	 KC_W, 	  KC_F,    KC_P,    KC_B, 					    KC_J,    KC_L,    KC_U,    KC_Y, NO_OSTR, KC_BSPC,
	//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
	    KC_LCTL,    KC_A,    KC_R,    KC_S,    KC_T,    KC_G, 						KC_M,    KC_N,    KC_E,    KC_I,   KC_O,    NO_AE,
	//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
		 OSM(MOD_LSFT),KC_Z, KC_X,    KC_C,    KC_D,    KC_V, 			            KC_K,    KC_H,   KC_COMM,  KC_DOT, TD(CT_MINS_UNDS), TD(CT_AA_ALT),
	//|--------+--------+--------+--------+--------+--------+--------|     |--------+--------+--------+--------+--------+--------+--------|
									TD(LAY_LNAV),TD(LAY_NUM),  KC_SPC, 	    KC_ENT, MO(_SYM), TD(LAY_NAV)
										//`--------------------------'     `--------------------------'
	),

	// numbers  - Left thumb
	[_NUM] = LAYOUT(
	//,-----------------------------------------------------.                    ,-----------------------------------------------------.
	     KC_NO,  KC_NO,   KC_NO,   KC_NO,   NO_ASTR, KC_NO, 		               KC_NO,     KC_7,    KC_8,    KC_9,   KC_DEL, KC_BSPC,
	//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
	    KC_LCTL, NO_SLSH, NO_MINS, NO_EQL,  NO_PLUS, KC_NO, 			           KC_NO,     KC_4,   KC_5,     KC_6,   KC_0,    KC_NO,
	//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
		KC_LSFT, KC_NO,   KC_LALT,LALT(KC_TAB),KC_TAB,KC_CAPS,		        	   KC_NO,     KC_1,   KC_2,     KC_3,   NO_COMM, KC_DOT,
	//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
											KC_TRNS, KC_TRNS,  KC_SPC,    KC_ENT, TG(_COM), KC_RALT
										//`--------------------------'   `--------------------------'
	),

	// symbols  - Right thumb
	[_SYM] = LAYOUT(
	//,-----------------------------------------------------.                    ,-----------------------------------------------------.
	    NO_CIRC,  NO_GRV,TD(CT_QUOTES), KC_HASH,NO_DLR,KC_PERC, 				NO_AMPR, TD(CT_SLAH_BSLS), NO_LPRN, NO_RPRN, KC_DEL, KC_BSPC,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
	    KC_LCTL,KC_PSCR, NO_EXLM, NO_SCLN, NO_AT,   NO_EQL, 				       NO_PLUS,  NO_MINS, NO_LBRC, NO_RBRC, TD(holdModCA), TD(holdModA),
	//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
		KC_LSFT,NO_TILD, NO_SECT, NO_LABK, NO_RABK, NO_PIPE, 			          NO_QUES, NO_COLN, NO_LCBR, NO_RCBR, TD(holdModCS), TD(holdModAS)	,
	//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
											KC_TRNS, MO(_COM),KC_SPC,    KC_ENT, KC_TRNS, KC_RALT
										//`--------------------------'  `--------------------------'
	),

	// navigate - Right thumbs
	[_NAV] = LAYOUT(
	//,-----------------------------------------------------.                    ,-----------------------------------------------------.
	      KC_NO, KC_NO,   KC_HOME, KC_UP,   KC_END, KC_PGUP,                       KC_NO,   LCTL(KC_C),LCTL(KC_V),KC_NO,LCTL(KC_DEL), LCTL(KC_BSPC),
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
	    KC_NO,   KC_NO,   KC_LEFT, KC_DOWN, KC_RGHT,KC_PGDN,					   KC_NO,   KC_LSFT, KC_LCTL, KC_LALT, KC_NO,  KC_NO,
	//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
		KC_NO,   KC_NO,   KC_NO,   LALT(KC_TAB),KC_TAB,KC_NO,                      LWIN(KC_L),   C(LWIN(KC_LEFT)),   C(LWIN(KC_RIGHT)),   KC_NO,   KC_NO,  KC_NO,
	//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
							        KC_TRNS, TO(_COLEMAKDH),  KC_SPC,    KC_ENT, TO(_COLEMAKDH), TO(_COLEMAKDH)
										//`--------------------------'  `--------------------------'
	),

	// commands - both thumbs
	[_COM] = LAYOUT(
	//,-----------------------------------------------------.                    ,-----------------------------------------------------.
	    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_DEL, KC_BSPC,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
	    KC_F7,   KC_F8,   KC_F9,   KC_F10, KC_F11,   KC_F12,					   KC_NO,   KC_LSFT, KC_LCTL, KC_LALT, KC_NO,  KC_NO,
	//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
		KC_NO,   KC_NO,   KC_NO, LALT(KC_TAB),KC_TAB, KC_NO,                       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,
	//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
										 KC_TRNS, KC_TRNS,  KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS
										//`--------------------------'  `--------------------------'
	),

	// layer nav - both thumbs
	[_LNAV] = LAYOUT(
	//,-----------------------------------------------------.                    ,-----------------------------------------------------.
	    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
	    KC_NO,   TO(_NAV),TO(_SYM),KC_NO,   KC_NO,   KC_NO,					       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,
	//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
		KC_NO,   KC_NO,   KC_NO,   KC_NO   ,KC_TAB,  KC_NO,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,
	//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
										KC_TRNS, KC_TRNS,  KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS
										//`--------------------------'  `--------------------------'
	),

};


// Diagram of underglow LEDs on the left, from above:
    //    2   1   0
    //    3   4   5
    //
    // LED on keys on the left side when viewed from above:
    //   24  23  18  17  10   9
    //   25  22  19  16  11   8
    //   26  21  20  15  12   7
    //                   14  13   6
    //
    // Diagram of underglow LEDs on the RH side when viewed from above:
    //   27  28  29
    //   32  31  30
    //
    // LED on keys on the right side when viewed from above:
    //   36  37  44  45  50  51
    //   35  38  43  46  49  52
    //   34  39  42  47  48  53
    //                   33  40  41


// _COLEMAKDH,
// no need for light when I'm typing
const rgblight_segment_t PROGMEM layer_colemakdh_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 57, HSV_OFF}
);

// _NUM, 0-9 + hold key on left side
const rgblight_segment_t PROGMEM layer_num_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    {37, 3, HSV_RED},
    {42, 6, HSV_RED},
    {49, 1, HSV_RED},
    {22, 1, HSV_RED},
    {19, 1, HSV_RED},
    {16, 1, HSV_RED},
    {11, 1, HSV_RED}
);
// _SYMBOL, everything yellow. 
const rgblight_segment_t PROGMEM layer_symbol_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    {6, 21, HSV_GOLD},
    {33, 21, HSV_GOLD}
);
// _NAV, arrow key on left side
const rgblight_segment_t PROGMEM layer_navigation_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    {19, 1, HSV_CORAL},
    {11, 1, HSV_CORAL},
    {16, 2, HSV_CORAL}
);
// _COM, F1-F12
const rgblight_segment_t PROGMEM layer_command_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    {24, 2, HSV_PURPLE},
    {22, 2, HSV_PURPLE},
    {18, 2, HSV_PURPLE},
    {16, 2, HSV_PURPLE},
    {10, 2, HSV_PURPLE},
    {8, 2, HSV_PURPLE}
);

//
// _LNAV 
const rgblight_segment_t PROGMEM layer_lnavigation_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    {11, 1, HSV_GREEN},
    {16, 1, HSV_GREEN},
    {19, 1, HSV_GREEN},
    {22, 1, HSV_GREEN}
);

// used when caps-lock is active, everything is white
const rgblight_segment_t PROGMEM layer_caps_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    {7, 20, HSV_WHITE},
    {34, 20, HSV_WHITE}
);
// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
	layer_colemakdh_lights,
	layer_num_lights,
	layer_symbol_lights,
    layer_navigation_lights,
    layer_command_lights,
    layer_lnavigation_lights,
    layer_caps_lights
);

// need this to set the default layer
void matrix_scan_user(void) {
	rgblight_set_layer_state(0, layer_state_cmp(default_layer_state, _COLEMAKDH));
}

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;

}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _COLEMAKDH));
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
	rgblight_set_layer_state(1, layer_state_cmp(state, _NUM));
	rgblight_set_layer_state(2, layer_state_cmp(state, _SYM));
	rgblight_set_layer_state(3, layer_state_cmp(state, _NAV));
	rgblight_set_layer_state(4, layer_state_cmp(state, _COM));
	rgblight_set_layer_state(5, layer_state_cmp(state, _LNAV));
    switch (get_highest_layer(state)) {
        case _COLEMAKDH:
            if (host_keyboard_led_state().caps_lock) {
                // When caps lock is on, make it REALLY obvious.
                rgblight_set_layer_state(6, true);
            } else {
                rgblight_set_layer_state(0, true);
            }
            break;
        default: //  for any other layers
            // remove caps lock light if active
            if(rgblight_get_layer_state(6)){
                rgblight_set_layer_state(6, false);
            }
            break;
    }
    return state;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}

#ifdef OLED_ENABLE


oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master() || true) {
        return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
    }
  return rotation;
}

void oled_render_layer_state(void) {
  char string [24];
  switch (get_highest_layer(default_layer_state|layer_state))
  {
      case _COLEMAKDH:
        oled_write_ln_P(PSTR("Layer: COLEMAKDH"),false);
        break;
      case _NUM:
        oled_write_ln_P(PSTR("Layer: Numbers"),false);
        break;
      case _SYM:
        oled_write_ln_P(PSTR("Layer: Symbols"),false);
        break;
      case _COM:
        oled_write_ln_P(PSTR("Layer: Command"),false);
        break;
      case _NAV:
        oled_write_ln_P(PSTR("Layer: Navgation"),false);
        break;
      case _LNAV:
        oled_write_ln_P(PSTR("Layer: Lay Navgation"),false);
        break;
      default:
        // snprintf(string, sizeof(string), "%ld",layer_state);
        oled_write_P(PSTR("Layer: Undef-"),false);
        oled_write_ln(string, false);
    }

  

 }

char keylog_str[24] = {};
const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void oled_render_logo_screen(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo_screen();
    }
    return false;
}

#endif 
// OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    #ifdef OLED_ENABLE
    if (record->event.pressed) {
        set_keylog(keycode, record);
    }
    #endif 

    switch (keycode) {
        case KC_ESC:
            // Detect if any 
            if( get_mods() || get_oneshot_mods() ){
                clear_mods();
                clear_oneshot_mods();
                activMod = false;
                return false;
            }
            if (activMod == true) {
                clear_mods();
                clear_oneshot_mods();
                activMod = false;
                return false;
            }
            return true;
            break;
    }

    return true;
}


#include "tapdance_end.c"
