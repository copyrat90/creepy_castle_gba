#include "bn_core.h"

#include "Portrait.h"

using namespace cr_ca;

int main()
{
    bn::core::init();

    Portrait butterfly(Portrait::Kind::BUTTERFLY, 0, 0);
    butterfly.AllocateGraphics();

    while (true)
    {
        bn::core::update();
    }
}
