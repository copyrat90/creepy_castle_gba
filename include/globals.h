#pragma once

#include "bn_sprite_text_generator.h"

namespace crecat::globals
{

struct GlobalData
{
    bn::sprite_text_generator textGenerator;
};

extern GlobalData* globalPtr;

} // namespace crecat::globals
