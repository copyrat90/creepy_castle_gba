#pragma once

#include "entity/IEntity.h"

#include "bn_fixed_point.h"
#include "bn_sprite_item.h"
#include "bn_sprite_ptr.h"
#include "bn_vector.h"

namespace crecat::entity
{

/**
 * @brief 72x128 portrait `bn::sprite_ptr` manager.
 * Graphics are not allocated by default.
 *
 */
class Portrait final : public IEntity
{
public:
    enum class Kind
    {
        EMPTY = 0,
        BUTTERFLY = 1,
    };

    Portrait(Portrait::Kind kind, const bn::fixed_point& position);
    Portrait(Portrait::Kind kind, bn::fixed x, bn::fixed y);

    void setPosition(const bn::fixed_point& position) final;
    void setPosition(bn::fixed x, bn::fixed y) final;
    void setX(bn::fixed x) final;
    void setY(bn::fixed y) final;

    void freeGraphics() final;
    void allocateGraphics() final;

private:
    Portrait::Kind _kind;
    // top-left, bottom-left, top-right, bottom-right
    bn::vector<bn::sprite_ptr, 4> _sprites;
};

} // namespace crecat::entity
