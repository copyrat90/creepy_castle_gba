#pragma once

#include "bn_vector.h"

#include "event/IObservable.h"

namespace crecat::event
{

/**
 * @brief Observer class from https://gameprogrammingpatterns.com/observer.html.
 * This can be, for example, an Achievement System, where it observes game's state an unlock some
 achievements.
 *
 */
class IObserver
{
    friend class IObservable;

public:
    static constexpr int MAX_SUBJECTS = 3;

private:
    // We have to store observed subjects and their iterator.
    bn::vector<IObservable*, MAX_SUBJECTS> _subjects;
    bn::vector<IObservable::ObserverListType::const_iterator, MAX_SUBJECTS> _subjectsIters;

public:
    void observe(IObservable& subject);

    /**
     * @brief Destroy the Test Observer object
     * Let's stop observing all subjects here, using stored subjects and iterators.
     *
     */
    virtual ~IObserver();

private:
    virtual void onNotify(EventArg e) = 0;
};

} // namespace crecat::event
