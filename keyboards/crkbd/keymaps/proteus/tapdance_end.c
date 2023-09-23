// this need to be at the bottom of the keymap.c or after the key


// Determine the current tap dance state. this will work for every one
// it seams to 
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        if(!state->pressed ) return TD_DOUBLE_TAP;
        else return TD_DOUBLE_HOLD;
    } else if (state->count >= 3 ) {
        if (!state->pressed) return TD_TRIPPLE_TAP;
        else return TD_UNKNOWN;
    }
        else return TD_UNKNOWN;
}

// Initialize tap structure associated with example tap dance key
static td_tap_t laynum_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void laynum_finished(tap_dance_state_t *state, void *user_data) {
    laynum_tap_state.state = cur_dance(state);
    switch (laynum_tap_state.state) {
        case TD_SINGLE_HOLD:
            layer_on(_NUM);
            break;
        case TD_DOUBLE_TAP:
            // Check to see if the layer is already set
            if (layer_state_is(_NUM)) {
                // If already set, then switch it "off"
                layer_off(_NUM);
            } else {
                // If not already set, then switch the layer on
                layer_on(_NUM);
            }
            break;
        default:
            break;
    }
}

void laynum_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (laynum_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(_NUM);
    }
    laynum_tap_state.state = TD_NONE;
}

// Initialize tap structure associated with example tap dance key
static td_tap_t laynav_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void laynav_finished(tap_dance_state_t *state, void *user_data) {
    laynav_tap_state.state = cur_dance(state);
    switch (laynav_tap_state.state) {
        case TD_SINGLE_HOLD:
            layer_on(_NAV);
            break;
        case TD_DOUBLE_TAP:
            // Check to see if the layer is already set
            if (layer_state_is(_NAV)) {
                // If already set, then switch it off
                layer_off(_NAV);
            } else {
                // If not already set, then switch the layer on
                layer_on(_NAV);
            }
            break;
        default:
            break;
    }
}

void laynav_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (laynav_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(_NAV);
    }
    laynav_tap_state.state = TD_NONE;
}

// Initialize tap structure associated with LNAV
static td_tap_t laylnav_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void laylnav_finished(tap_dance_state_t *state, void *user_data) {
    laylnav_tap_state.state = cur_dance(state);
    switch (laylnav_tap_state.state) {
        case TD_SINGLE_TAP:
            register_code(KC_LGUI);
            break;
        case TD_SINGLE_HOLD:
            register_code(KC_LGUI);
            break;
        case TD_DOUBLE_TAP:
            // Check to see if the layer is already set
            if (layer_state_is(_LNAV)) {
                // If already set, then switch it off
                layer_off(_LNAV);
            } else {
                // If not already set, then switch the layer on
                layer_on(_LNAV);
            }
            break;
        case TD_TRIPPLE_TAP:
            // Reset layer if it is not active
            if (!layer_state_is(_COLEMAKDH)) {
                // If not already set, then switch it off active layer
                layer_off(biton32(layer_state));
            } 
            break;
        default:
            break;
    }
}

void laylnav_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then release the key, but only single action.
    if (laylnav_tap_state.state == TD_SINGLE_HOLD || laylnav_tap_state.state == TD_SINGLE_TAP) {
        unregister_code(KC_LGUI);
    }
    laylnav_tap_state.state = TD_NONE;
}

// Initialize tap structure associated with holdModCA. one time or lock it with two tap. ESC to stop
static td_tap_t holdModCA_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void holdModCA_finished(tap_dance_state_t *state, void *user_data) {
    holdModCA_tap_state.state = cur_dance(state);
    switch (holdModCA_tap_state.state) {
        case TD_SINGLE_TAP:
            set_oneshot_mods(MOD_BIT(KC_LCTL)|MOD_BIT(KC_LALT));
            break;
        case TD_DOUBLE_TAP:
            set_mods(MOD_BIT(KC_LCTL)|MOD_BIT(KC_LALT));
            activMod = true;
            break;
        default:
            break;
    }
}

void holdModCA_reset(tap_dance_state_t *state, void *user_data) {
    // Nothing to do here.. 
    holdModCA_tap_state.state = TD_NONE;
}

// Initialize tap structure associated with holdModA. one time or lock it with two tap. ESC to stop
static td_tap_t holdModA_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void holdModA_finished(tap_dance_state_t *state, void *user_data) {
    holdModA_tap_state.state = cur_dance(state);
    switch (holdModA_tap_state.state) {
        case TD_SINGLE_TAP:
            set_oneshot_mods(MOD_BIT(KC_LALT));
            break;
        case TD_DOUBLE_TAP:
            set_mods(MOD_BIT(KC_LALT));
            activMod = true;
            break;
        default:
            break;
    }
}

void holdModA_reset(tap_dance_state_t *state, void *user_data) {
    // Notthing to do here.. 
    holdModA_tap_state.state = TD_NONE;
}

// Initialize tap structure associated with holdModCS. one time or lock it with two tap. ESC to stop
static td_tap_t holdModCS_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void holdModCS_finished(tap_dance_state_t *state, void *user_data) {
    holdModCS_tap_state.state = cur_dance(state);
    switch (holdModCS_tap_state.state) {
        case TD_SINGLE_TAP: 
            set_oneshot_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT));
            break;
        case TD_DOUBLE_TAP:
            set_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT));
            activMod = true;
            break;
        default:
            break;
    }
}

void holdModCS_reset(tap_dance_state_t *state, void *user_data) {
    // Notthing to do here.. 
    holdModCS_tap_state.state = TD_NONE;
}

// Initialize tap structure associated with holdModAS. one time or lock it with two tap. ESC to stop
static td_tap_t holdModAS_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void holdModAS_finished(tap_dance_state_t *state, void *user_data) {
    holdModAS_tap_state.state = cur_dance(state);
    switch (holdModAS_tap_state.state) {
        case TD_SINGLE_TAP: 
            set_oneshot_mods(MOD_BIT(KC_LALT) | MOD_BIT(KC_LSFT));
            break;
        case TD_DOUBLE_TAP:
            set_mods(MOD_BIT(KC_LALT) | MOD_BIT(KC_LSFT));
            activMod = true;
            break;
        default:
            break;
    }
}

void holdModAS_reset(tap_dance_state_t *state, void *user_data) {
    // Notthing to do here.. 
    holdModAS_tap_state.state = TD_NONE;
}

// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
tap_dance_action_t tap_dance_actions[] = {
    [holdModAS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, holdModAS_finished, holdModAS_reset),
    [holdModCS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, holdModCS_finished, holdModCS_reset),
    [holdModA] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, holdModA_finished, holdModA_reset),
    [holdModCA] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, holdModCA_finished, holdModCA_reset),
    [LAY_NAV] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, laynav_finished, laynav_reset),
    [LAY_NUM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, laynum_finished, laynum_reset),
    [LAY_LNAV] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, laylnav_finished, laylnav_reset),
    [CT_MINS_UNDS] = ACTION_TAP_DANCE_DOUBLE(NO_MINS, NO_UNDS),
    [CT_SLAH_BSLS] = ACTION_TAP_DANCE_DOUBLE(NO_SLSH, NO_BSLS),
    [CT_QUOTES] = ACTION_TAP_DANCE_DOUBLE(NO_DQUO, NO_QUOT),
    [CT_AA_ALT] = ACTION_TAP_DANCE_DOUBLE(NO_ARNG, KC_LALT)

};