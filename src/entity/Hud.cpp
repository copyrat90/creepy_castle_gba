#include "entity/Hud.h"

#include "bn_assert.h"

#include "bn_regular_bg_items_bg_hud.h"

namespace crecat::entity
{

Hud::Hud()
{
}

void Hud::setPosition(const bn::fixed_point& position)
{
    setPosition(position.x(), position.y());
}

void Hud::setPosition(bn::fixed x, bn::fixed y)
{
    IEntity::setPosition(x, y);
    if (_hudBg)
        _hudBg->set_position(position());
}

void Hud::setX(bn::fixed x)
{
    setPosition(x, this->y());
}

void Hud::setY(bn::fixed y)
{
    setPosition(this->x(), y);
}

void Hud::freeGraphics()
{
    _hudBg.reset();
    _playerHpBar.freeGraphics();
}

void Hud::allocateGraphics()
{
    if (_hudBg)
        return;
    _hudBg = bn::regular_bg_items::bg_hud.create_bg(position());
    _playerHpBar.allocateGraphics();
}

void Hud::onNotify(system::EventArg e)
{
    using EventArg = system::EventArg;

    switch (e)
    {
    case EventArg::PLAYER_LEVEL_UP:
        BN_ERROR("TODO");
        break;
    case EventArg::PLAYER_DAMAGE_1:
        _playerHpBar.changeHp(-1);
        break;
    case EventArg::PLAYER_DAMAGE_2:
        _playerHpBar.changeHp(-2);
        break;
    default:
        break;
    }

    if ((int)EventArg::PLAYER_HP_REGEN_1 <= (int)e && (int)e <= (int)EventArg::PLAYER_HP_REGEN_9)
    {
        const int amount = (int)e - (int)EventArg::PLAYER_HP_REGEN_1 + 1;
        _playerHpBar.changeHp(amount);
    }
}

} // namespace crecat::entity
