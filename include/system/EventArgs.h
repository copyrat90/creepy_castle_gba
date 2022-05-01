#pragma once

namespace crecat::system
{

enum class EventArgs
{
    TEST_A_PRESSED = 0,
    TEST_B_PRESSED,
    TEST_START_PRESSED,
    TEST_SELECT_PRESSED,

    // Player events.
    PLAYER_LEVEL_UP = 100,
    PLAYER_KILLED,
    PLAYER_BATTLE_DAMAGE_1,
    PLAYER_BATTLE_DAMAGE_2,
};

} // namespace crecat::system
