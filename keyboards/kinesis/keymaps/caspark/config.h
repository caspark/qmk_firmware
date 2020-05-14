#pragma once

// configure time to complete tap dances and other tap actions
#define TAPPING_TERM 200

// register a tap combined with another keypress within the tapping term as a "hold"
#define PERMISSIVE_HOLD

// turn on a layer with only 2 taps instead of the default 5
#define TAPPING_TOGGLE 2

// 2 taps to make a one shot key stick in the activated position
#define ONESHOT_TAP_TOGGLE 2

// auto release one shot modifiers once this many seconds have passed
#define ONESHOT_TIMEOUT 5000

// mousekey settings - https://docs.qmk.fm/#/feature_mouse_keys
#define MOUSEKEY_WHEEL_INTERVAL 25
