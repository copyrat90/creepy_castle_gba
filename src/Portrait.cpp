#include "Portrait.h"

#include "bn_assert.h"

#include "bn_sprite_items_spr_portrait_butterfly_left.h"
#include "bn_sprite_items_spr_portrait_butterfly_right.h"

namespace crecat
{

namespace
{

constexpr bn::fixed OFFSET_TOP = -32;
constexpr bn::fixed OFFSET_BOTTOM = +32;
constexpr bn::fixed OFFSET_LEFT = -4;
constexpr bn::fixed OFFSET_RIGHT = +44;

} // namespace

Portrait::Portrait(Portrait::Kind kind, const bn::fixed_point& position) : IEntity(position), _kind(kind)
{
}

Portrait::Portrait(Portrait::Kind kind, bn::fixed x, bn::fixed y) : IEntity(x, y), _kind(kind)
{
}

void Portrait::setPosition(const bn::fixed_point& position)
{
    setPosition(position.x(), position.y());
}

void Portrait::setPosition(bn::fixed x, bn::fixed y)
{
    IEntity::setPosition(x, y);
    if (!_sprites.empty())
    {
        _sprites[0].set_position({x + OFFSET_LEFT, y + OFFSET_TOP});
        _sprites[1].set_position({x + OFFSET_LEFT, y + OFFSET_BOTTOM});
        _sprites[2].set_position({x + OFFSET_RIGHT, y + OFFSET_TOP});
        _sprites[3].set_position({x + OFFSET_RIGHT, y + OFFSET_BOTTOM});
    }
}

void Portrait::setX(bn::fixed x)
{
    setPosition(x, _position.y());
}

void Portrait::setY(bn::fixed y)
{
    setPosition(_position.x(), y);
}

void Portrait::freeGraphics()
{
    _sprites.clear();
}

void Portrait::allocateGraphics()
{
    if (!_sprites.empty())
        return;

    const bn::fixed top = _position.y() + OFFSET_TOP;
    const bn::fixed bottom = _position.y() + OFFSET_BOTTOM;
    const bn::fixed left = _position.x() + OFFSET_LEFT;
    const bn::fixed right = _position.x() + OFFSET_RIGHT;

    auto pushSprites = [&](const bn::sprite_item& leftPortrait, const bn::sprite_item& rightPortrait) {
        _sprites.push_back(leftPortrait.create_sprite(left, top, 0));
        _sprites.push_back(leftPortrait.create_sprite(left, bottom, 1));
        _sprites.push_back(rightPortrait.create_sprite(right, top, 0));
        _sprites.push_back(rightPortrait.create_sprite(right, bottom, 1));
    };

    switch (_kind)
    {
        using namespace bn::sprite_items;
    case Portrait::Kind::EMPTY:
        break;
    case Portrait::Kind::BUTTERFLY:
        pushSprites(spr_portrait_butterfly_left, spr_portrait_butterfly_right);
        break;
    default:
        BN_ERROR("Invalid Portrait::Kind: ", static_cast<int>(_kind));
    }
}

} // namespace crecat
