#pragma once

#include "bn_fixed_point.h"

namespace crecat::entity
{

/**
 * @brief a.k.a. IGameObject.
 * Holds `bn::fixed_point` position, and abstract graphic alloc & free functions.
 *
 */
class IEntity
{
public:
    virtual ~IEntity() = 0;

    IEntity() = default;
    IEntity(const bn::fixed_point& position);
    IEntity(bn::fixed x, bn::fixed y);

    virtual void update(){};

    const bn::fixed_point& position() const;
    bn::fixed x() const;
    bn::fixed y() const;

    virtual void setPosition(const bn::fixed_point& position);
    virtual void setPosition(bn::fixed x, bn::fixed y);
    virtual void setX(bn::fixed x);
    virtual void setY(bn::fixed y);

    virtual void freeGraphics(){};
    virtual void allocateGraphics(){};

private:
    bn::fixed_point _position;
};

} // namespace crecat::entity
