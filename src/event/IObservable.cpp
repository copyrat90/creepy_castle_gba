#include "event/IObservable.h"

#include "event/IObserver.h"

namespace crecat::event
{

IObservable::~IObservable() = default;

auto IObservable::addObserver(IObserver* observer) -> ObserverListType::const_iterator
{
    if (!observer)
        BN_ERROR("Storing nullptr observer inside IObservable");
    _observers.push_front(observer);
    return _observers.cbegin();
}

void IObservable::removeObserver(ObserverListType::const_iterator it)
{
    _observers.erase(it);
}

void IObservable::notify(EventArg e)
{
    for (auto& observer : _observers)
        observer->onNotify(e);
}

} // namespace crecat::event
