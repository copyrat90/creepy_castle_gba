#pragma once

#include "entity/IEntity.h"
#include "event/IObserve.h"

#include "bn_optional.h"
#include "bn_sprite_ptr.h"
#include "bn_vector.h"

#include "event/arg/PlayerEArg.h"

namespace crecat::entity
{

class Player final : public IEntity, public event::IObservable<event::arg::PlayerEArg>
{
public:
    static constexpr int MAX_HP = 10;

public:
    Player(int hp = MAX_HP, int level = 1, int exp = 0);

    void freeGraphics() final;
    void allocateGraphics() final;

    void expUp();

    int hp() const;
    int level() const;
    int exp() const;

private:
    int _hp;
    int _level;
    int _exp;
    bn::optional<bn::sprite_ptr> _sprite;
};

} // namespace crecat::entity
