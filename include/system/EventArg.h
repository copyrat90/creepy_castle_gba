#pragma once

namespace crecat::system
{

enum class EventArg
{
    TEST_A_PRESSED = 0,
    TEST_B_PRESSED,
    TEST_START_PRESSED,
    TEST_SELECT_PRESSED,

    // Player events.
    PLAYER_LEVEL_UP = 100,
    PLAYER_EXP_UP,
    PLAYER_KILLED,
    PLAYER_DAMAGE_1,
    PLAYER_DAMAGE_2,
    PLAYER_HP_REGEN_1, // DO NOT CHANGE ORDER!
    PLAYER_HP_REGEN_2, //
    PLAYER_HP_REGEN_3, // The order is used for
    PLAYER_HP_REGEN_4, // calculating the amount
    PLAYER_HP_REGEN_5, // of HP regeneration.
    PLAYER_HP_REGEN_6, //
    PLAYER_HP_REGEN_7, //
    PLAYER_HP_REGEN_8, //
    PLAYER_HP_REGEN_9, // DO NOT CHANGE ORDER!
};

} // namespace crecat::system
