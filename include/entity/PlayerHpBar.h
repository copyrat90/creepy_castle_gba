#pragma once

#include "entity/IEntity.h"

#include "bn_sprite_ptr.h"
#include "bn_vector.h"

namespace crecat::entity
{

class PlayerHpBar final : public IEntity
{
public:
    static constexpr int MAX_HP = 10;

public:
    PlayerHpBar();

    void changeHp(int diff);

    void setPosition(const bn::fixed_point& position) final;
    void setPosition(bn::fixed x, bn::fixed y) final;
    void setX(bn::fixed x) final;
    void setY(bn::fixed y) final;

    void freeGraphics() final;
    void allocateGraphics() final;

private:
    bn::vector<bn::sprite_ptr, MAX_HP> _hpSprites;
    int _hp;
};

} // namespace crecat::entity
