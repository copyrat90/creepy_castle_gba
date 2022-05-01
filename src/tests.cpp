#if !defined(NDEBUG) && !defined(RELEASE)

#include "tests.h"

#include "bn_core.h"
#include "bn_format.h"
#include "bn_keypad.h"
#include "bn_log.h"
#include "bn_vector.h"

#include "entity/Hud.h"
#include "entity/IObservableEntity.h"
#include "entity/Player.h"
#include "system/EventArg.h"
#include "system/IObserver.h"

namespace crecat::tests
{

void testObserverPattern()
{
    BN_LOG("[TEST] tests::testObserverPattern()");

    /**
     * @brief Test Observer.
     * This can be, for example, an Achievement System, where it observes game's state an unlock some
     achievements.
     *
     */
    class TestObserver final : public system::IObserver
    {
    private:
        void onNotify(system::EventArg eventArgs) final
        {
            BN_LOG(bn::format<28>("eventArgs={} fired!", static_cast<int>(eventArgs)));
        }
    };

    /**
     * @brief Test Subject.
     * This can be, for example, a Player Character.
     *
     */
    class TestSubject final : public entity::IObservableEntity
    {
    public:
        void update() final
        {
            IObservableEntity::update();

            if (bn::keypad::a_pressed())
                notify(system::EventArg::TEST_A_PRESSED);
            if (bn::keypad::b_pressed())
                notify(system::EventArg::TEST_B_PRESSED);
            if (bn::keypad::start_pressed())
                notify(system::EventArg::TEST_START_PRESSED);
            if (bn::keypad::select_pressed())
                notify(system::EventArg::TEST_SELECT_PRESSED);
        }
    };

    TestObserver observer;
    TestSubject subject;
    observer.observeEntity(subject);

    while (true)
    {
        subject.update();
        bn::core::update();
    }
}

void testHud()
{
    BN_LOG("[TEST] tests::testHud()");

    class TestSubject final : public entity::IObservableEntity
    {
    public:
        void update() final
        {
            using EventArg = system::EventArg;
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
    hud.observeEntity(subject);
    hud.allocateGraphics();

    while (true)
    {
        subject.update();
        bn::core::update();
    }
}

} // namespace crecat::tests

#endif
