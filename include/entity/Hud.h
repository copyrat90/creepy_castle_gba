#pragma once

#include "entity/IEntity.h"
#include "event/IObserve.h"

#include "bn_optional.h"
#include "bn_regular_bg_ptr.h"

#include "entity/PlayerHpBar.h"
#include "event/EventArg.h"

namespace crecat::entity
{

class Hud final : public IEntity, public event::IObserver<event::EventArg>
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
    void onNotify(event::EventArg e) final;

private:
    bn::optional<bn::regular_bg_ptr> _hudBg;
    PlayerHpBar _playerHpBar;
};

} // namespace crecat::entity
