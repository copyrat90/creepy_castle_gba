#include "entity/IEntity.h"

namespace crecat::entity
{

IEntity::~IEntity() = default;

IEntity::IEntity(const bn::fixed_point& position)
{
    setPosition(position);
}

IEntity::IEntity(bn::fixed x, bn::fixed y)
{
    setPosition(x, y);
}

const bn::fixed_point& IEntity::position() const
{
    return _position;
}

bn::fixed IEntity::x() const
{
    return _position.x();
}

bn::fixed IEntity::y() const
{
    return _position.y();
}

void IEntity::setPosition(const bn::fixed_point& position)
{
    _position = position;
}

void IEntity::setPosition(bn::fixed x, bn::fixed y)
{
    _position = {x, y};
}

void IEntity::setX(bn::fixed x)
{
    _position.set_x(x);
}

void IEntity::setY(bn::fixed y)
{
    _position.set_y(y);
}

} // namespace crecat::entity
