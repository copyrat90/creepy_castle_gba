#include "entity/Player.h"

namespace crecat::entity
{

Player::Player(int hp, int level, int exp) : _hp(hp), _level(level), _exp(exp)
{
}

void Player::freeGraphics()
{
    IEntity::freeGraphics();
}

void Player::allocateGraphics()
{
    IEntity::allocateGraphics();
}

void Player::expUp()
{
    using EventArg = event::arg::PlayerEArg;
    if (++_exp == _level)
    {
        ++_level;
        _exp = 0;
        notify({EventArg::Type::LEVEL_UP, 1});
    }
    else
    {
        notify({EventArg::Type::EXP_UP, 1});
    }
}

int Player::hp() const
{
    return _hp;
}

int Player::level() const
{
    return _level;
}

int Player::exp() const
{
    return _exp;
}

} // namespace crecat::entity
