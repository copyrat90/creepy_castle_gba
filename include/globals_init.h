#pragma once

#include "globals.h"

#include "asset/font_variable_8x8_creepy_castle.h"

/**
 * @brief Define & Initialize global variables.
 * This macro is meant to be used on main().
 *
 */
#define GLOBALS_INIT \
    crecat::globals::GlobalData globalData = { \
        bn::sprite_text_generator(crecat::asset::font::variable_8x8_creepy_castle), \
    }; \
    crecat::globals::globalPtr = &globalData;
