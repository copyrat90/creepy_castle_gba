#include "Portrait.h"

#include "bn_assert.h"

#include "bn_sprite_items_spr_portrait_butterfly_left.h"
#include "bn_sprite_items_spr_portrait_butterfly_right.h"

namespace cr_ca
{

namespace
{

constexpr bn::fixed OFFSET_TOP = -32;
constexpr bn::fixed OFFSET_BOTTOM = +32;
constexpr bn::fixed OFFSET_LEFT = -4;
constexpr bn::fixed OFFSET_RIGHT = +44;

} // namespace

Portrait::Portrait(Portrait::Kind kind, const bn::fixed_point& position) : kind_(kind), position_(position)
{
}

Portrait::Portrait(Portrait::Kind kind, bn::fixed x, bn::fixed y) : kind_(kind), position_(x, y)
{
}

const bn::fixed_point& Portrait::Position() const
{
    return position_;
}

bn::fixed Portrait::X() const
{
    return position_.x();
}

bn::fixed Portrait::Y() const
{
    return position_.y();
}

void Portrait::SetPosition(const bn::fixed_point& position)
{
    SetPosition(position.x(), position.y());
}

void Portrait::SetPosition(bn::fixed x, bn::fixed y)
{
    position_ = {x, y};
    if (!sprites_.empty())
    {
        sprites_[0].set_position({x + OFFSET_LEFT, y + OFFSET_TOP});
        sprites_[1].set_position({x + OFFSET_LEFT, y + OFFSET_BOTTOM});
        sprites_[2].set_position({x + OFFSET_RIGHT, y + OFFSET_TOP});
        sprites_[3].set_position({x + OFFSET_RIGHT, y + OFFSET_BOTTOM});
    }
}

void Portrait::SetX(bn::fixed x)
{
    SetPosition(x, position_.y());
}

void Portrait::SetY(bn::fixed y)
{
    SetPosition(position_.x(), y);
}

void Portrait::FreeGraphics()
{
    sprites_.clear();
}

void Portrait::AllocateGraphics()
{
    if (!sprites_.empty())
        return;

    const bn::fixed top = position_.y() + OFFSET_TOP;
    const bn::fixed bottom = position_.y() + OFFSET_BOTTOM;
    const bn::fixed left = position_.x() + OFFSET_LEFT;
    const bn::fixed right = position_.x() + OFFSET_RIGHT;

    auto pushSprites = [&](const bn::sprite_item& leftPortrait, const bn::sprite_item& rightPortrait) {
        sprites_.push_back(leftPortrait.create_sprite(left, top, 0));
        sprites_.push_back(leftPortrait.create_sprite(left, bottom, 1));
        sprites_.push_back(rightPortrait.create_sprite(right, top, 0));
        sprites_.push_back(rightPortrait.create_sprite(right, bottom, 1));
    };

    switch (kind_)
    {
        using namespace bn::sprite_items;
    case Portrait::Kind::EMPTY:
        break;
    case Portrait::Kind::BUTTERFLY:
        pushSprites(spr_portrait_butterfly_left, spr_portrait_butterfly_right);
        break;
    default:
        BN_ERROR("Invalid Portrait::Kind: ", static_cast<int>(kind_));
    }
}

} // namespace cr_ca
