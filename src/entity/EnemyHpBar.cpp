#include "entity/EnemyHpBar.h"

#include "bn_assert.h"
#include "bn_display.h"
#include "bn_fixed_point.h"

#include "globals.h"

namespace crecat::entity
{

namespace
{
constexpr bn::fixed_point OBJ_POS = {214 - bn::display::width() / 2, 63 - bn::display::height() / 2};
constexpr bn::fixed_point UPPER_TEXT_POS = {198 - bn::display::width() / 2, 5 - bn::display::height() / 2};
constexpr bn::fixed_point LOWER_HEART_OFFSET = {-4, 59};
} // namespace

EnemyHpBar::EnemyHpBar() : IEntity(OBJ_POS), _maxHp(0), _hp(0)
{
}

void EnemyHpBar::changeHp(int diff)
{
    setHp(_hp + diff);
}

void EnemyHpBar::setHp(int hp)
{
    _hp = hp;
    _hp = _hp > _maxHp ? _maxHp : _hp;
    _hp = _hp < 0 ? 0 : _hp;

    if (graphicsAllocated())
    {
        // TODO: Allocate enemy HP heart sprites
    }
}

void EnemyHpBar::setMaxAndCurrentHp(int maxHp, int currentHp)
{
    _maxHp = maxHp;
    setHp(currentHp);
}

bn::string_view EnemyHpBar::name() const
{
    return _name;
}

void EnemyHpBar::setName(bn::string_view name)
{
    if (name == _name)
        return;

    BN_ASSERT(name.size() <= _name.max_size(), "Enemy name is longer than max name length");

    _name = name;

    if (graphicsAllocated())
    {
        _nameSprites.clear();
        globals::globalPtr->textGenerator.generate(UPPER_TEXT_POS, _name, _nameSprites);
    }
}

void EnemyHpBar::setPosition(const bn::fixed_point& position)
{
    setPosition(position.x(), position.y());
}

void EnemyHpBar::setPosition(bn::fixed x, bn::fixed y)
{
    IEntity::setPosition(x, y);

    // name sprite position is fixed;

    // TODO: Set enemy HP heart sprites position
}

void EnemyHpBar::setX(bn::fixed x)
{
    setPosition(x, this->y());
}

void EnemyHpBar::setY(bn::fixed y)
{
    setPosition(this->x(), y);
}

void EnemyHpBar::freeGraphics()
{
    IEntity::freeGraphics();

    _hpSprites.clear();
    _nameSprites.clear();
}

void EnemyHpBar::allocateGraphics()
{
    IEntity::allocateGraphics();

    globals::globalPtr->textGenerator.generate(UPPER_TEXT_POS, _name, _nameSprites);
    // TODO: Allocate enemy HP heart sprites
}

} // namespace crecat::entity
