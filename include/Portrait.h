#pragma once

#include "bn_fixed_point.h"
#include "bn_sprite_item.h"
#include "bn_sprite_ptr.h"
#include "bn_vector.h"

namespace crecat
{

/**
 * @brief 72x128 portrait `bn::sprite_ptr` manager.
 * Graphics are not allocated by default.
 *
 */
class Portrait
{
public:
    enum class Kind
    {
        EMPTY = 0,
        BUTTERFLY = 1,
    };

    Portrait(Portrait::Kind kind, const bn::fixed_point& position);
    Portrait(Portrait::Kind kind, bn::fixed x, bn::fixed y);

    const bn::fixed_point& position() const;
    bn::fixed x() const;
    bn::fixed y() const;

    void setPosition(const bn::fixed_point& position);
    void setPosition(bn::fixed x, bn::fixed y);
    void setX(bn::fixed x);
    void setY(bn::fixed y);

    void freeGraphics();
    void allocateGraphics();

private:
    Portrait::Kind _kind;
    bn::fixed_point _position;
    // top-left, bottom-left, top-right, bottom-right
    bn::vector<bn::sprite_ptr, 4> _sprites;
};

} // namespace crecat
