#include "entity/PlayerExpBar.h"

#include "bn_assert.h"
#include "bn_display.h"
#include "bn_fixed_point.h"
#include "bn_log.h"
#include "bn_span.h"
#include "bn_string.h"

#include "bn_sprite_items_spr_exp_bar.h"
#include "constants.h"
#include "globals.h"

namespace crecat::entity
{

namespace
{
constexpr bn::fixed_point OBJ_POS = {22 - bn::display::width() / 2, 8 - bn::display::height() / 2};
constexpr bn::fixed_point LEVEL_NUM_POS = {36 - bn::display::width() / 2, 23 - bn::display::height() / 2};
} // namespace

PlayerExpBar::PlayerExpBar(int level, int exp) : IEntity(OBJ_POS), _level(level), _exp(exp)
{
}

void PlayerExpBar::update()
{
    if (graphicsAllocated() && _expBarAction)
    {
        if (!_expBarAction->done())
            _expBarAction->update();
        else
            _expBarAction.reset();
    }
}

static int calculateGraphicsIndex(int level, int exp)
{
    const int ret = (exp == 0) ? (level == 1 ? 0 : PlayerExpBar::EXP_BAR_LEN)
                               : ((bn::fixed(exp) / level * PlayerExpBar::EXP_BAR_LEN).round_integer());
    BN_LOG(ret);
    return ret;
}

void PlayerExpBar::changeExp(int diff)
{
    const int prevLevel = _level;
    const int prevExp = _exp;

    // update level & exp values
    _exp += diff;
    while (_exp >= _level)
    {
        _exp -= _level;
        ++_level;
    }

    if (graphicsAllocated())
    {
        const int prevGraphicsIndex = calculateGraphicsIndex(prevLevel, prevExp);
        const int nextGraphicsIndex = calculateGraphicsIndex(_level, _exp);

        if (prevLevel != _level)
            updateLevelSprite();
        if (prevGraphicsIndex != nextGraphicsIndex)
            startExpBarAction(prevGraphicsIndex, nextGraphicsIndex);
    }
}

void PlayerExpBar::setLevelAndExp(int level, int exp)
{
    const int prevLevel = _level;
    const int prevExp = _exp;

    _level = level;
    _exp = exp;

    if (graphicsAllocated())
    {
        const int prevGraphicsIndex = calculateGraphicsIndex(prevLevel, prevExp);
        const int nextGraphicsIndex = calculateGraphicsIndex(level, exp);

        if (prevLevel != _level)
            updateLevelSprite();

        // update exp bar sprite
        if (prevGraphicsIndex != nextGraphicsIndex)
            _expBarSprite->set_tiles(bn::sprite_items::spr_exp_bar.tiles_item().create_tiles(nextGraphicsIndex));
    }
}

void PlayerExpBar::setPosition(const bn::fixed_point& position)
{
    setPosition(position.x(), position.y());
}

void PlayerExpBar::setPosition(bn::fixed x, bn::fixed y)
{
    IEntity::setPosition(x, y);

    if (graphicsAllocated())
        _expBarSprite->set_position(position());
}

void PlayerExpBar::setX(bn::fixed x)
{
    setPosition(x, this->y());
}

void PlayerExpBar::setY(bn::fixed y)
{
    setPosition(this->x(), y);
}

void PlayerExpBar::freeGraphics()
{
    IEntity::freeGraphics();

    _expBarAction.reset();
    _expBarSprite.reset();
    _levelSprite.clear();
}

void PlayerExpBar::allocateGraphics()
{
    IEntity::allocateGraphics();

    _expBarSprite = bn::sprite_items::spr_exp_bar.create_sprite(position(), calculateGraphicsIndex(_level, _exp));
    updateLevelSprite();
}

void PlayerExpBar::updateLevelSprite()
{
    BN_ASSERT(graphicsAllocated(), "updateLevelSprite() called when graphics not allocated");

    auto& textGen = globals::globalPtr->textGenerator;
    auto prevAlignment = textGen.alignment();
    textGen.set_alignment(bn::sprite_text_generator::alignment_type::LEFT);

    // update level sprite
    _levelSprite.clear();
    textGen.generate(LEVEL_NUM_POS, bn::to_string<2>(_level), _levelSprite);

    textGen.set_alignment(prevAlignment);
}

void PlayerExpBar::startExpBarAction(int prevGraphicsIndex, int nextGraphicsIndex)
{
    BN_ASSERT(graphicsAllocated(), "startExpBarAction() called when graphics not allocated");
    if (prevGraphicsIndex == nextGraphicsIndex)
        return;
    // if bar is full, start animating from empty bar.
    if (prevGraphicsIndex == EXP_BAR_LEN)
        prevGraphicsIndex = 0;

    // create graphics indices span
    bn::vector<uint16_t, EXP_BAR_LEN + 1> graphicsIndices;
    if (prevGraphicsIndex < nextGraphicsIndex)
        for (uint16_t i = prevGraphicsIndex; i <= nextGraphicsIndex; ++i)
            graphicsIndices.push_back(i);
    else if (prevGraphicsIndex > nextGraphicsIndex)
        for (uint16_t i = prevGraphicsIndex; i >= nextGraphicsIndex; --i)
            graphicsIndices.push_back(i);
    bn::span<const uint16_t> graphicsIndicesSpan(graphicsIndices.begin(), graphicsIndices.end());

    const int waitUpdates = (bn::fixed(constants::EXP_INCREASE_FRAMES) / graphicsIndices.size()).floor_integer();

    // actually start exp bar animate action
    _expBarAction = bn::sprite_animate_action<EXP_BAR_LEN + 1>::once(
        *_expBarSprite, waitUpdates, bn::sprite_items::spr_exp_bar.tiles_item(), graphicsIndicesSpan);
}

} // namespace crecat::entity
