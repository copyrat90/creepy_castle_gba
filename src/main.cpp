#include "bn_core.h"

#include "globals.h"
#include "globals_init.h"

#include "debug_view.h"
#include "tests.h"

int main()
{
    bn::core::init();
    bn::core::set_skip_frames(1);
    GLOBALS_INIT;

    crecat::tests::testHud();

    DEBUG_VIEW_INIT;
    while (true)
    {
        DEBUG_VIEW_UPDATE;
        bn::core::update();
    }
}
