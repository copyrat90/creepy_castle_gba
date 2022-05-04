#if !defined(NDEBUG) && !defined(RELEASE)

#include "tests.h"

#include "bn_core.h"
#include "bn_format.h"
#include "bn_keypad.h"
#include "bn_log.h"
#include "bn_vector.h"

#include "entity/Hud.h"
#include "entity/Player.h"
#include "event/EventArg.h"
#include "event/IObserve.h"

namespace crecat::tests
{

void testObserverPattern()
{
    BN_LOG("[TEST] tests::testObserverPattern()");

    struct MyEventArg
    {
        int x, y;
    };

    /**
     * @brief Test Observer.
     * This can be, for example, an Achievement System, where it observes game's state an unlock some
     achievements.
     *
     */
    class TestObserver final
        : public event::IObserver<event::EventArg>,
          public event::IObserver<MyEventArg> // Multiple inheritance of IObserver<EArg> is allowed.
    {
    public:
        // You should do this to overload 2 parents' observe().
        using event::IObserver<event::EventArg>::observe;
        using event::IObserver<MyEventArg>::observe;

    private:
        void onNotify(event::EventArg eventArg) final
        {
            BN_LOG(bn::format<28>("eventArg={} fired!", static_cast<int>(eventArg)));
        }
        void onNotify(MyEventArg myEventArg) final
        {
            BN_LOG(bn::format<28>("myEventArg=<{},{}>", myEventArg.x, myEventArg.y));
        }
    };

    /**
     * @brief Test Subject.
     * This can be, for example, a Player Character.
     *
     */
    class TestSubject1 final : public entity::IEntity, public event::IObservable<event::EventArg>
    {
    public:
        void update() final
        {
            using EventArg = event::EventArg;
            if (bn::keypad::a_pressed())
                notify(EventArg::TEST_A_PRESSED);
            if (bn::keypad::b_pressed())
                notify(EventArg::TEST_B_PRESSED);
            if (bn::keypad::start_pressed())
                notify(EventArg::TEST_START_PRESSED);
            if (bn::keypad::select_pressed())
                notify(EventArg::TEST_SELECT_PRESSED);
        }
    };

    class TestSubject2 final : public entity::IEntity, public event::IObservable<MyEventArg>
    {
    public:
        void update() final
        {
            if (bn::keypad::a_pressed())
                notify({0, 1});
            if (bn::keypad::b_pressed())
                notify({1, 0});
        }
    };

    TestObserver observer;
    TestSubject1 subject1;
    TestSubject2 subject2;
    observer.observe(subject1);
    observer.observe(subject2);

    while (true)
    {
        subject1.update();
        subject2.update();
        bn::core::update();
    }
}

void testHud()
{
    BN_LOG("[TEST] tests::testHud()");

    class TestSubject final : public entity::IEntity, public event::IObservable<event::EventArg>
    {
    public:
        void update() final
        {
            using EventArg = event::EventArg;
            if (bn::keypad::select_held())
            {
                if (bn::keypad::a_pressed())
                    notify(EventArg::PLAYER_DAMAGE_1);
                else if (bn::keypad::b_pressed())
                    notify(EventArg::PLAYER_DAMAGE_2);
                else if (bn::keypad::up_pressed())
                    notify(EventArg::PLAYER_HP_REGEN_1);
            }
        }
    };

    TestSubject subject;
    entity::Hud hud;
    hud.observe(subject);
    hud.allocateGraphics();

    while (true)
    {
        subject.update();
        bn::core::update();
    }
}

} // namespace crecat::tests

#endif
