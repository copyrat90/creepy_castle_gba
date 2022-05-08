#pragma once

#include "entity/IEntity.h"

#include "bn_optional.h"
#include "bn_sprite_animate_actions.h"
#include "bn_sprite_ptr.h"
#include "bn_vector.h"

namespace crecat::entity
{

class PlayerExpBar final : public IEntity
{
public:
    static constexpr int EXP_BAR_LEN = 11;

public:
    PlayerExpBar(int level = 1, int exp = 0);

    void update() final;

    /**
     * @brief Increase exp, and also animate it.
     *
     * @param `diff` how many exp to increase
     */
    void changeExp(int diff);

    /**
     * @brief Set the Level And Exp object.
     * Note that this doesn't animate exp change.
     *
     * @param `level`
     * @param `exp`
     */
    void setLevelAndExp(int level, int exp);

    void setPosition(const bn::fixed_point& position) final;
    void setPosition(bn::fixed x, bn::fixed y) final;
    void setX(bn::fixed x) final;
    void setY(bn::fixed y) final;

    void freeGraphics() final;
    void allocateGraphics() final;

private:
    void updateLevelSprite();
    void startExpBarAction(int prevGraphicsIndex, int nextGraphicsIndex);

private:
    bn::optional<bn::sprite_ptr> _expBarSprite;
    bn::vector<bn::sprite_ptr, 1> _levelSprite;
    bn::optional<bn::sprite_animate_action<EXP_BAR_LEN + 1>> _expBarAction;
    int _level, _exp;
};

} // namespace crecat::entity
