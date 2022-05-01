#pragma once

#include "scene/IScene.h"

#include "entity/Hud.h"
#include "entity/Player.h"

namespace crecat::scene
{

class Game final : public IScene
{
public:
    Game();

    [[nodiscard]] bn::optional<SceneType> update() final;

private:
    entity::Player _player;
    entity::Hud _hud;
};

} // namespace crecat::scene
