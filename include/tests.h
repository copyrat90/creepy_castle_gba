#pragma once

#ifdef NDEBUG
inline constexpr bool ndebug = true;
#else
inline constexpr bool ndebug = false;
#endif

namespace crecat::tests
{

void testObserverPattern();

}
