#include "entity/IObservableEntity.h"

#include "bn_log.h"

#include "system/IObserver.h"

namespace crecat::entity
{

IObservableEntity::~IObservableEntity() = default;

auto IObservableEntity::addObserver(system::IObserver* observer) -> ObserverListType::const_iterator
{
    if (!observer)
        BN_ERROR("Storing nullptr observer inside IObservableEntity");
    _observers.push_front(observer);
    return _observers.cbegin();
}

void IObservableEntity::removeObserver(ObserverListType::const_iterator it)
{
    _observers.erase(it);
}

void IObservableEntity::notify(system::EventArgs eventArgs)
{
    for (auto& observer : _observers)
        observer->onNotify(eventArgs);
}

} // namespace crecat::entity
