#include "debug_view.h"

#if !defined(NDEBUG) && !defined(RELEASE)

#include "bn_bgs.h"
#include "bn_core.h"
#include "bn_display.h"
#include "bn_fixed_point.h"
#include "bn_format.h"
#include "bn_keypad.h"
#include "bn_memory.h"
#include "bn_sprites.h"

#include "constants.h"

namespace crecat::debugs
{

namespace
{
constexpr bn::fixed_point OBJ_POS = {0 - bn::display::width() / 2, 32 - bn::display::height() / 2};
constexpr bn::fixed_point LINE_OFFSET = {0, 7};
constexpr bn::fixed_point BLOCK_OFFSET = {0, 10};
} // namespace

int availableIwram()
{
    return IWRAM_BYTES - bn::memory::used_stack_iwram() - bn::memory::used_static_iwram();
}

int availableIwramPercent()
{
    return (bn::fixed(crecat::debugs::availableIwram()) / IWRAM_BYTES * 100).round_integer();
}

int availableEwramPercent()
{
    return (bn::fixed(bn::memory::available_alloc_ewram()) / EWRAM_BYTES * 100).round_integer();
}

DebugView::DebugView() : entity::IEntity(OBJ_POS)
{
    allocateGraphics();
}

void DebugView::update()
{
    ++_updateCounter;
    if (bn::keypad::select_pressed())
    {
        if (graphicsAllocated())
            freeGraphics();
        else
            allocateGraphics();
    }

    // text updates on every 0.5 second.
    if (graphicsAllocated() && (_updateCounter >= constants::REDRAW_FRAMES_DEBUG_VIEW || bn::keypad::select_pressed()))
    {
        _updateCounter = 0;
        auto& textGen = crecat::globals::globalPtr->textGenerator;
        auto prevAlignment = textGen.alignment();
        textGen.set_alignment(bn::sprite_text_generator::alignment_type::LEFT);
        _dynamicTexts.clear();
        textGen.generate(position() + LINE_OFFSET * 1,
                         bn::format<4>("{}%", (bn::core::last_cpu_usage() * 100).round_integer()), _dynamicTexts);
        textGen.generate(position() + BLOCK_OFFSET * 1 + LINE_OFFSET * 2,
                         bn::format<4>("{}%", crecat::debugs::availableEwramPercent()), _dynamicTexts);
        textGen.generate(position() + BLOCK_OFFSET * 1 + LINE_OFFSET * 3,
                         bn::format<6>("{}", bn::memory::available_alloc_ewram()), _dynamicTexts);
        textGen.generate(position() + BLOCK_OFFSET * 2 + LINE_OFFSET * 4,
                         bn::format<4>("{}%", crecat::debugs::availableIwramPercent()), _dynamicTexts);
        textGen.generate(position() + BLOCK_OFFSET * 2 + LINE_OFFSET * 5,
                         bn::format<5>("{}", crecat::debugs::availableIwram()), _dynamicTexts);
        textGen.generate(position() + BLOCK_OFFSET * 3 + LINE_OFFSET * 6,
                         bn::to_string<10>(bn::bgs::available_items_count()), _dynamicTexts);
        textGen.generate(position() + BLOCK_OFFSET * 4 + LINE_OFFSET * 7,
                         bn::to_string<10>(bn::sprites::available_items_count()), _dynamicTexts);
        for (auto& text : _dynamicTexts)
            text.set_bg_priority(constants::BG_PRIORITY_DEBUG_VIEW);
        textGen.set_alignment(prevAlignment);
    }
}

void DebugView::freeGraphics()
{
    entity::IEntity::freeGraphics();
    _dynamicTexts.clear();
    _staticTexts.clear();
}

void DebugView::allocateGraphics()
{
    entity::IEntity::allocateGraphics();

    auto& textGen = crecat::globals::globalPtr->textGenerator;
    auto prevAlignment = textGen.alignment();
    textGen.set_alignment(bn::sprite_text_generator::alignment_type::LEFT);
    textGen.generate(position(), "cpu use", _staticTexts);
    textGen.generate(position() + BLOCK_OFFSET * 1 + LINE_OFFSET * 1, "free ew", _staticTexts);
    textGen.generate(position() + BLOCK_OFFSET * 2 + LINE_OFFSET * 3, "free iw", _staticTexts);
    textGen.generate(position() + BLOCK_OFFSET * 3 + LINE_OFFSET * 5, "free bg", _staticTexts);
    textGen.generate(position() + BLOCK_OFFSET * 4 + LINE_OFFSET * 6, "free spr", _staticTexts);
    for (auto& text : _staticTexts)
        text.set_bg_priority(constants::BG_PRIORITY_DEBUG_VIEW);
    textGen.set_alignment(prevAlignment);
}

} // namespace crecat::debugs

#endif
