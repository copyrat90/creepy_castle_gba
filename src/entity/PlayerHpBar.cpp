#include "entity/PlayerHpBar.h"

#include "bn_assert.h"
#include "bn_display.h"
#include "bn_fixed_point.h"
#include "bn_log.h"
#include "bn_sprite_tiles_ptr.h"

#include "bn_sprite_items_spr_player_hp.h"

namespace crecat::entity
{

namespace
{
constexpr bn::fixed_point OBJ_POS = {36 - bn::display::width() / 2, 79 - bn::display::height() / 2};
constexpr bn::fixed OFFSET_LOWER_HEART_Y = 44;
constexpr bn::fixed OFFSET_Y_INC = -10;
} // namespace

PlayerHpBar::PlayerHpBar() : IEntity(OBJ_POS), _hp(MAX_HP)
{
}

void PlayerHpBar::changeHp(int diff)
{
    const int prevHp = _hp;
    _hp += diff;
    _hp = _hp > MAX_HP ? MAX_HP : _hp;
    _hp = _hp < 0 ? 0 : _hp;

    if (graphicsAllocated())
    {
        if (diff < 0)
            for (int i = prevHp - 1; i > _hp - 1; --i)
                _hpSprites[i].set_tiles(bn::sprite_items::spr_player_hp.tiles_item().create_tiles(1));
        else
            for (int i = prevHp; i < _hp; ++i)
                _hpSprites[i].set_tiles(bn::sprite_items::spr_player_hp.tiles_item().create_tiles(0));
    }
}

void PlayerHpBar::setPosition(const bn::fixed_point& position)
{
    bn::fixed_point diff = position - this->position();
    IEntity::setPosition(position);

    for (auto& hp : _hpSprites)
        hp.set_position(hp.position() + diff);
}

void PlayerHpBar::setPosition(bn::fixed x, bn::fixed y)
{
    setPosition({x, y});
}

void PlayerHpBar::setX(bn::fixed x)
{
    setPosition(x, this->y());
}

void PlayerHpBar::setY(bn::fixed y)
{
    setPosition(this->x(), y);
}

void PlayerHpBar::freeGraphics()
{
    IEntity::freeGraphics();

    _hpSprites.clear();
}

void PlayerHpBar::allocateGraphics()
{
    IEntity::allocateGraphics();

    for (int i = 0; i < MAX_HP; ++i)
    {
        const bn::fixed_point pos = position() + bn::fixed_point{0, OFFSET_LOWER_HEART_Y + i * OFFSET_Y_INC};
        _hpSprites.push_back(bn::sprite_items::spr_player_hp.create_sprite(pos, !(i <= _hp - 1)));
    }
}

} // namespace crecat::entity
