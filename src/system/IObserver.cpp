#include "system/IObserver.h"

namespace crecat::system
{

void IObserver::observeEntity(entity::IObservableEntity& entity)
{
    auto it = entity.addObserver(this);
    _observedEntities.push_back(&entity);
    _observedEntitiesIters.push_back(it);
}

IObserver::~IObserver()
{
    for (int i = 0; i < _observedEntities.size(); ++i)
        _observedEntities[i]->removeObserver(_observedEntitiesIters[i]);
}

} // namespace crecat::system
