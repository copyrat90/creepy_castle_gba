#pragma once

#include "entity/IEntity.h"

#include "bn_sprite_ptr.h"
#include "bn_string.h"
#include "bn_string_view.h"
#include "bn_vector.h"

#include "constants.h"

namespace crecat::entity
{

class EnemyHpBar final : public IEntity
{
public:
    EnemyHpBar();

    void changeHp(int diff);
    void setHp(int hp);
    void setMaxAndCurrentHp(int maxHp, int currentHp);

    bn::string_view name() const;
    void setName(bn::string_view name);

    void setPosition(const bn::fixed_point& position) final;
    void setPosition(bn::fixed x, bn::fixed y) final;
    void setX(bn::fixed x) final;
    void setY(bn::fixed y) final;

    void freeGraphics() final;
    void allocateGraphics() final;

private:
    bn::vector<bn::sprite_ptr, 7> _hpSprites;
    bn::vector<bn::sprite_ptr, 7> _nameSprites;
    int _maxHp;
    int _hp;
    bn::string<constants::MAX_ENEMY_NAME_LEN> _name;
};

} // namespace crecat::entity
