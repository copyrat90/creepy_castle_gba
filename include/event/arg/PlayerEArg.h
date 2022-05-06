#pragma once

namespace crecat::event::arg
{

struct PlayerEArg
{
    enum class Type
    {
        LEVEL_UP,
        EXP_UP,
        KILLED,
        DAMAGE,
        HP_REGEN,
    };

    Type type;
    int amount;
};

} // namespace crecat::event::arg
