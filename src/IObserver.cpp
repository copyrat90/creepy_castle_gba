#include "IObserver.h"

namespace crecat
{

void IObserver::observeEntity(IObservableEntity& entity)
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

} // namespace crecat
