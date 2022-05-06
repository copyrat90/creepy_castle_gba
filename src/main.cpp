#include "bn_core.h"

#include "globals.h"
#include "globals_init.h"

#include "tests.h"

int main()
{
    bn::core::init();
    GLOBALS_INIT;

    crecat::tests::testHud();

    while (true)
    {
        bn::core::update();
    }
}
