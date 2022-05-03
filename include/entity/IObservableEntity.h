#pragma once

#include "entity/IEntity.h"
#include "system/IObservable.h"

namespace crecat::system
{
class IObserver;
}

namespace crecat::entity
{

/**
 * @brief IEntity + IObservable.
 * This can be, for example, a Player Character.
 *
 */
class IObservableEntity : public IEntity, public system::IObservable
{
public:
    virtual ~IObservableEntity() = 0;

    IObservableEntity() = default;
    IObservableEntity(const bn::fixed_point& position) : IEntity(position){};
    IObservableEntity(bn::fixed x, bn::fixed y) : IEntity(x, y){};
};

inline IObservableEntity::~IObservableEntity() = default;

} // namespace crecat::entity
