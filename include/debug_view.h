#pragma once

#if !defined(NDEBUG) && !defined(RELEASE)

#include "entity/IEntity.h"

#include "bn_sprite_ptr.h"
#include "bn_vector.h"

#include "globals.h"

namespace crecat::debugs
{
inline constexpr int IWRAM_BYTES = 32'768;
inline constexpr int EWRAM_BYTES = 262'144;

int availableIwram();
int availableIwramPercent();
int availableEwramPercent();

class DebugView final : entity::IEntity
{
public:
    DebugView();
    void update() final;

    void freeGraphics() final;
    void allocateGraphics() final;

private:
    bn::vector<bn::sprite_ptr, 6> _staticTexts;
    bn::vector<bn::sprite_ptr, 8> _dynamicTexts;
    int _updateCounter;
};

#define DEBUG_VIEW_INIT crecat::debugs::DebugView debugView;

#define DEBUG_VIEW_UPDATE debugView.update();

} // namespace crecat::debugs

#else

#define DEBUG_VIEW_INIT ((void)0);

#define DEBUG_VIEW_UPDATE ((void)0);

#endif
