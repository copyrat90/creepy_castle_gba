#pragma once

#include "entity/IEntity.h"

#include "bn_list.h"

#include "system/EventArgs.h"

namespace crecat::system
{
class IObserver;
}

namespace crecat::entity
{

/**
 * @brief Subject class from https://gameprogrammingpatterns.com/observer.html.
 * This can be, for example, a Player Character.
 *
 * Name `IObservable~` and `EventArgs` are borrowed from C#.
 *
 */
class IObservableEntity : public IEntity
{
    friend class system::IObserver;

public:
    static constexpr int MAX_OBSERVERS = 3;
    using ObserverListType = bn::list<system::IObserver*, MAX_OBSERVERS>;

    virtual ~IObservableEntity() = 0;

    IObservableEntity() = default;
    IObservableEntity(const bn::fixed_point& position) : IEntity(position){};
    IObservableEntity(bn::fixed x, bn::fixed y) : IEntity(x, y){};

protected:
    void notify(system::EventArgs eventArgs);

private:
    [[nodiscard]] auto addObserver(system::IObserver* observer) -> ObserverListType::const_iterator;
    void removeObserver(ObserverListType::const_iterator it);

private:
    ObserverListType _observers;
};

} // namespace crecat::entity
