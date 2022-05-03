#pragma once

#include "bn_list.h"

#include "event/EventArg.h"

namespace crecat::event
{

class IObserver;

/**
 * @brief Subject class from https://gameprogrammingpatterns.com/observer.html.
 *
 * Name `IObservable` and `EventArg` are borrowed from C#.
 *
 */
class IObservable
{
    friend class IObserver;

public:
    static constexpr int MAX_OBSERVERS = 3;
    using ObserverListType = bn::list<IObserver*, MAX_OBSERVERS>;

    virtual ~IObservable() = 0;

    IObservable() = default;

protected:
    void notify(EventArg e);

private:
    [[nodiscard]] auto addObserver(IObserver* observer) -> ObserverListType::const_iterator;
    void removeObserver(ObserverListType::const_iterator it);

private:
    ObserverListType _observers;
};

} // namespace crecat::event
