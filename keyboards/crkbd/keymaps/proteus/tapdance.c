// this need to be on the top in keymap.c

// Tap Dance keycodes, used on in the key map
enum td_keycodes {
    LAY_NUM, 
    LAY_NAV,
    CT_MINS_UNDS,
    CT_SLAH_BSLS,
    CT_QUOTES,
    CT_AA_ALT,
    LAY_LNAV,
    holdModCA,
    holdModA,
    holdModCS,
    holdModAS
};

// Define a type containing as many tapdance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP,
    TD_TRIPPLE_TAP
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// Declare the functions to be used with with tap dance key(s)

// Function associated with all tap dances
td_state_t cur_dance(tap_dance_state_t *state);

// Functions associated with individual tap dances
void ql_finished(tap_dance_state_t *state, void *user_data);
void ql_reset(tap_dance_state_t *state, void *user_data);