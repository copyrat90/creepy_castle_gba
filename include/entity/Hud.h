#pragma once

#include "entity/IEntity.h"
#include "system/IObserver.h"

#include "bn_optional.h"
#include "bn_regular_bg_ptr.h"

#include "entity/PlayerHpBar.h"

namespace crecat::entity
{

class Hud final : public IEntity, public system::IObserver
{
public:
    Hud();

    void setPosition(const bn::fixed_point& position) final;
    void setPosition(bn::fixed x, bn::fixed y) final;
    void setX(bn::fixed x) final;
    void setY(bn::fixed y) final;

    void freeGraphics() final;
    void allocateGraphics() final;

private:
    void onNotify(system::EventArg e) final;

private:
    bn::optional<bn::regular_bg_ptr> _hudBg;
    PlayerHpBar _playerHpBar;
};

} // namespace crecat::entity
