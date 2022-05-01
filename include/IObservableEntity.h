#pragma once

#include "IEntity.h"

#include "bn_list.h"

#include "EventArgs.h"

namespace crecat
{

class IObserver;

/**
 * @brief Subject class from https://gameprogrammingpatterns.com/observer.html.
 * This can be, for example, a Player Character.
 *
 * Name `IObservable~` and `EventArgs` are borrowed from C#.
 *
 */
class IObservableEntity : public IEntity
{
    friend class IObserver;

public:
    static constexpr int MAX_OBSERVERS = 3;
    using ObserverListType = bn::list<IObserver*, MAX_OBSERVERS>;

    virtual ~IObservableEntity() = 0;

    IObservableEntity() = default;
    IObservableEntity(const bn::fixed_point& position) : IEntity(position){};
    IObservableEntity(bn::fixed x, bn::fixed y) : IEntity(x, y){};

protected:
    void notify(EventArgs eventArgs);

private:
    [[nodiscard]] auto addObserver(IObserver* observer) -> ObserverListType::const_iterator;
    void removeObserver(ObserverListType::const_iterator it);

private:
    ObserverListType _observers;
};

} // namespace crecat
