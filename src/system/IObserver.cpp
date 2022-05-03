#include "system/IObserver.h"

namespace crecat::system
{

void IObserver::observe(IObservable& subject)
{
    auto it = subject.addObserver(this);
    _subjects.push_back(&subject);
    _subjectsIters.push_back(it);
}

IObserver::~IObserver()
{
    for (int i = 0; i < _subjects.size(); ++i)
        _subjects[i]->removeObserver(_subjectsIters[i]);
}

} // namespace crecat::system
