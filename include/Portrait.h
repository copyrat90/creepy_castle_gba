#pragma once

#include "bn_fixed_point.h"
#include "bn_sprite_item.h"
#include "bn_sprite_ptr.h"
#include "bn_vector.h"

namespace cr_ca
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

    const bn::fixed_point& Position() const;
    bn::fixed X() const;
    bn::fixed Y() const;

    void SetPosition(const bn::fixed_point& position);
    void SetPosition(bn::fixed x, bn::fixed y);
    void SetX(bn::fixed x);
    void SetY(bn::fixed y);

    void FreeGraphics();
    void AllocateGraphics();

private:
    Portrait::Kind kind_;
    bn::fixed_point position_;
    // top-left, bottom-left, top-right, bottom-right
    bn::vector<bn::sprite_ptr, 4> sprites_;
};

} // namespace cr_ca
