#include "system/IObservable.h"

#include "system/IObserver.h"

namespace crecat::system
{

IObservable::~IObservable() = default;

auto IObservable::addObserver(system::IObserver* observer) -> ObserverListType::const_iterator
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

void IObservable::notify(system::EventArg e)
{
    for (auto& observer : _observers)
        observer->onNotify(e);
}

} // namespace crecat::system