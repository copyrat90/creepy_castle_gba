#include "entity/IEntity.h"

#include "bn_assert.h"

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

bool IEntity::graphicsAllocated() const
{
    return _graphicsAllocated;
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

void IEntity::freeGraphics()
{
    BN_ASSERT(_graphicsAllocated, "Tried to free graphics that isn't allocated");
    _graphicsAllocated = false;
}

void IEntity::allocateGraphics()
{
    BN_ASSERT(!_graphicsAllocated, "Tried to allocate graphics when it is already allocated");
    _graphicsAllocated = true;
}

void IEntity::setCamera(const bn::camera_ptr& camera)
{
    _camera = camera;
}

void IEntity::removeCamera()
{
    _camera.reset();
}

auto IEntity::camera() -> const bn::optional<bn::camera_ptr>&
{
    return _camera;
}

} // namespace crecat::entity
