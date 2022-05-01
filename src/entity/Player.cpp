#include "entity/Player.h"

namespace crecat::entity
{

Player::Player(int hp, int level, int exp) : _hp(hp), _level(level), _exp(exp)
{
}

void Player::freeGraphics()
{
}

void Player::allocateGraphics()
{
}

void Player::expUp()
{
    if (++_exp == _level)
    {
        ++_level;
        _exp = 0;
        notify(system::EventArgs::PLAYER_LEVEL_UP);
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
