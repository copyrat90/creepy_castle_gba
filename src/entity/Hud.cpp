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
    if (graphicsAllocated())
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
    IEntity::freeGraphics();

    _hudBg.reset();
    _playerHpBar.freeGraphics();
    _enemyHpBar.freeGraphics();
}

void Hud::allocateGraphics()
{
    IEntity::allocateGraphics();

    _hudBg = bn::regular_bg_items::bg_hud.create_bg(position());
    _playerHpBar.allocateGraphics();
    _enemyHpBar.allocateGraphics();
}

void Hud::onNotify(event::arg::PlayerEArg e)
{
    using EventArg = event::arg::PlayerEArg;

    switch (e.type)
    {
    case EventArg::Type::LEVEL_UP:
        BN_ERROR("TODO");
        break;
    case EventArg::Type::DAMAGE:
        _playerHpBar.changeHp(-e.amount);
        break;
    case EventArg::Type::HP_REGEN:
        _playerHpBar.changeHp(e.amount);
        break;
    default:
        break;
    }
}

void Hud::onNotify(event::arg::EnemyEArg e)
{
    using EventArg = event::arg::EnemyEArg;

    switch (e.type)
    {
    case EventArg::Type::DAMAGE:
        _enemyHpBar.changeHp(-e.amount);
        _enemyHpBar.setName(e.name);
        break;
    default:
        break;
    }
}

} // namespace crecat::entity
