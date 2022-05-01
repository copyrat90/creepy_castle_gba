#pragma once

#include "bn_vector.h"

#include "entity/IObservableEntity.h"

namespace crecat::system
{

/**
 * @brief Observer class from https://gameprogrammingpatterns.com/observer.html.
 * This can be, for example, an Achievement System, where it observes game's state an unlock some
 achievements.
 *
 */
class IObserver
{
    friend class entity::IObservableEntity;

public:
    static constexpr int MAX_OBSERVED_ENTITIES = 3;

private:
    // We have to store observed entities and its iterator.
    bn::vector<entity::IObservableEntity*, MAX_OBSERVED_ENTITIES> _observedEntities;
    bn::vector<entity::IObservableEntity::ObserverListType::const_iterator, MAX_OBSERVED_ENTITIES>
        _observedEntitiesIters;

public:
    void observeEntity(entity::IObservableEntity& entity);

    /**
     * @brief Destroy the Test Observer object
     * Let's stop observing all entities here, using stored entites and iterators.
     *
     */
    virtual ~IObserver();

private:
    virtual void onNotify(EventArg e) = 0;
};

} // namespace crecat::system