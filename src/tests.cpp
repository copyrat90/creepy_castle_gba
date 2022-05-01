#include "tests.h"

#include "bn_core.h"
#include "bn_format.h"
#include "bn_keypad.h"
#include "bn_log.h"
#include "bn_vector.h"

#include "EventArgs.h"
#include "IObservableEntity.h"
#include "IObserver.h"

namespace crecat::tests
{

void testObserverPattern()
{
    if constexpr (!ndebug)
    {
        BN_LOG("start tests::testObserverPattern()");

        /**
         * @brief Test Observer.
         * This can be, for example, an Achievement System, where it observes game's state an unlock some
         achievements.
         *
         */
        class TestObserver final : public IObserver
        {
        private:
            void onNotify(EventArgs eventArgs) final
            {
                BN_LOG(bn::format<28>("eventArgs={} fired!", static_cast<int>(eventArgs)));
            }
        };

        /**
         * @brief Test Subject.
         * This can be, for example, a Player Character.
         *
         */
        class TestSubject final : public IObservableEntity
        {
        public:
            void update() final
            {
                IObservableEntity::update();

                if (bn::keypad::a_pressed())
                    notify(EventArgs::TEST_A_PRESSED);
                if (bn::keypad::b_pressed())
                    notify(EventArgs::TEST_B_PRESSED);
                if (bn::keypad::start_pressed())
                    notify(EventArgs::TEST_START_PRESSED);
                if (bn::keypad::select_pressed())
                    notify(EventArgs::TEST_SELECT_PRESSED);
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
}

} // namespace crecat::tests
