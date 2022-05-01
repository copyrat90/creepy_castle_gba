#include "bn_core.h"

#include "tests.h"

int main()
{
    bn::core::init();

    crecat::tests::testHud();

    while (true)
    {
        bn::core::update();
    }
}
