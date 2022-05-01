#pragma once

#include "bn_optional.h"

#include "scene/SceneType.h"

namespace crecat::scene
{

class IScene
{
public:
    virtual ~IScene() = default;

    /**
     * @brief Update the scene.
     *
     * @return next scene if present, `bn::nullopt` otherwise.
     */
    [[nodiscard]] virtual bn::optional<SceneType> update() = 0;
};

} // namespace crecat::scene
