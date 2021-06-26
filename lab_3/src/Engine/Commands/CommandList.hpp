#pragma once

#include "ICommand.hpp"
#include "API/Managers/RenderManager.hpp"


class RenderSceneCommand : public ICommand
{
public:
    RenderSceneCommand(RenderManager& manager, const Scene& scene, const Camera& camera)
        : manager(manager), scene(scene), camera(camera) {}

    void execute() override
    {
        manager.renderScene(scene, camera);
    }

private:
    RenderManager& manager;
    const Scene& scene;
    const Camera& camera;
};
