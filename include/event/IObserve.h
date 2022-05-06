#pragma once

#include "bn_assert.h"
#include "bn_list.h"
#include "bn_vector.h"

namespace crecat::event
{

template <typename EArg>
class IObservable;

/**
 * @brief Observer class from https://gameprogrammingpatterns.com/observer.html.
 * This can be, for example, an Achievement System, where it observes game's state an unlock some
 achievements.
 *
 * @tparam `EArg` Event Argument. Provides event information.
 */
template <typename EArg>
class IObserver
{
    friend class IObservable<EArg>;

public:
    static constexpr int MAX_SUBJECTS = 3;

private:
    // We have to store observed subjects and their iterator.
    bn::vector<IObservable<EArg>*, MAX_SUBJECTS> _subjects;
    bn::vector<typename IObservable<EArg>::ObserverListType::const_iterator, MAX_SUBJECTS> _subjectsIters;

public:
    void observe(IObservable<EArg>& subject)
    {
        auto it = subject.addObserver(this);
        _subjects.push_back(&subject);
        _subjectsIters.push_back(it);
    }

    /**
     * @brief Destroy the IObserver.
     * Let's stop observing all subjects here, using stored subjects and iterators.
     *
     */
    virtual ~IObserver()
    {
        for (int i = 0; i < _subjects.size(); ++i)
            _subjects[i]->removeObserver(_subjectsIters[i]);
    }

private:
    /**
     * @brief Remove subject from the observed list.
     * This takes O(_subjects.size()) time, should be improved later.
     *
     * Unfortunately, storing each other's iterators and removing both on O(1) turns out to be a tricky task.
     *
     * @param `subject` subject to be deleted
     */
    void removeSubject(IObservable<EArg>* subject)
    {
        int removedIdx = 0;
        for (; removedIdx < _subjects.size(); ++removedIdx)
            if (_subjects[removedIdx] == subject)
                break;
        BN_ASSERT(removedIdx < _subjects.size());

        _subjects.erase(_subjects.cbegin() + removedIdx);
        _subjectsIters.erase(_subjectsIters.cbegin() + removedIdx);
    }

private:
    virtual void onNotify(EArg e) = 0;
};

/**
 * @brief Subject class from https://gameprogrammingpatterns.com/observer.html.
 *
 * Name `IObservable` and `EventArg` are borrowed from C#.
 *
 * @tparam `EArg` Event Argument. Provides event information.
 */
template <typename EArg>
class IObservable
{
    friend class IObserver<EArg>;

public:
    static constexpr int MAX_OBSERVERS = 3;
    using ObserverListType = bn::list<IObserver<EArg>*, MAX_OBSERVERS>;

    virtual ~IObservable()
    {
        for (auto& observer : _observers)
            observer->removeSubject(this);
    }

    IObservable() = default;

protected:
    void notify(EArg e)
    {
        for (auto& observer : _observers)
            observer->onNotify(e);
    }

private:
    [[nodiscard]] auto addObserver(IObserver<EArg>* observer) -> typename ObserverListType::const_iterator
    {
        if (!observer)
            BN_ERROR("Storing nullptr observer inside IObservable");
        _observers.push_front(observer);
        return _observers.cbegin();
    }

    /**
     * @brief Removes observer.
     * This takes O(1) time, as it uses iterator.
     *
     * @param `it` Iterator pointing observer to be deleted.
     */
    void removeObserver(typename ObserverListType::const_iterator it)
    {
        _observers.erase(it);
    }

private:
    ObserverListType _observers;
};

} // namespace crecat::event
