#pragma once

#include "bn_camera_ptr.h"
#include "bn_fixed_point.h"
#include "bn_optional.h"

namespace crecat::entity
{

/**
 * @brief a.k.a. IGameObject.
 * Basically, everything meant to be drawn on screen
 * should inherit this class (directly or indirectly).
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

    bool graphicsAllocated() const;
    const bn::fixed_point& position() const;
    bn::fixed x() const;
    bn::fixed y() const;

    /**
     * @brief Set the position.
     * Don't forget to call parent `IEntity::setPosition()`, as this sets the `IEntity::_position` member!
     *
     * @param `position`
     */
    virtual void setPosition(const bn::fixed_point& position);

    /**
     * @brief Set the position.
     * Don't forget to call parent `IEntity::setPosition()`, as this sets the `IEntity::_position` member!
     *
     * @param `x`
     * @param `y`
     */
    virtual void setPosition(bn::fixed x, bn::fixed y);

    /**
     * @brief Set the x position.
     * Don't forget to call parent `IEntity::setX()`, as this sets the `IEntity::_position` member!
     *
     * @param `x`
     */
    virtual void setX(bn::fixed x);

    /**
     * @brief Set the y position.
     * Don't forget to call parent `IEntity::setY()`, as this sets the `IEntity::_position` member!
     *
     * @param `y`
     */
    virtual void setY(bn::fixed y);

    /**
     * @brief Free graphics.
     * Don't forget to call parent `IEntity::freeGrahpics()`, as this sets the `_graphicsAllocated` flag to `false` !
     *
     */
    virtual void freeGraphics();

    /**
     * @brief Allocate graphics.
     * Don't forget to call parent `IEntity::allocateGrahpics()`, as this sets the `_graphicsAllocated` flag to `true` !
     *
     */
    virtual void allocateGraphics();

    /**
     * @brief Set the camera.
     * Don't forget to call parent `IEntity::setCamera()`, as this sets the `IEntity::_camera` member!
     *
     */
    virtual void setCamera(const bn::camera_ptr& camera);

    /**
     * @brief Remove the camera.
     * Don't forget to call parent `IEntity::setCamera()`, as this sets the `IEntity::_camera` member!
     *
     */
    virtual void removeCamera();

    auto camera() -> const bn::optional<bn::camera_ptr>&;

private:
    bn::fixed_point _position;
    bool _graphicsAllocated = false;
    bn::optional<bn::camera_ptr> _camera;
};

} // namespace crecat::entity
