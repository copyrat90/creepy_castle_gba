#pragma once

#include "scene/IScene.h"

namespace crecat::scene
{

class Game final : public IScene
{
public:
    Game();

    [[nodiscard]] bn::optional<SceneType> update() final;
};

} // namespace crecat::scene
