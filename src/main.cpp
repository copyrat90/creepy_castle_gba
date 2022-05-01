#include "bn_core.h"

#include "tests.h"

using namespace crecat;

int main()
{
    bn::core::init();

    while (true)
    {
        tests::testObserverPattern();
        bn::core::update();
    }
}
