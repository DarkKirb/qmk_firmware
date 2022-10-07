#pragma once

#include "quantum/action.h"
#include <stdint.h>

void track_neo2_modifier_state(uint16_t keycode, keyrecord_t *record);
uint32_t keystroke_to_unicode(uint16_t keycode);
