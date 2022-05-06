#pragma once

#include "bn_string_view.h"

namespace crecat::event::arg
{

struct EnemyEArg
{
    enum class Type
    {
        KILLED,
        DAMAGE,
    };

    Type type;
    int amount;
    bn::string_view name;
};

} // namespace crecat::event::arg
