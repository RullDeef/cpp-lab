#pragma once

#include <memory>
#include "API/Managers/IStateManager.hpp"
#include "API/Managers/IRenderManager.hpp"
#include "API/Renderer/IRenderer.hpp"


class QtRenderManager : public IRenderManager
{
public:
    QtRenderManager(std::shared_ptr<IStateManager> stateManager, std::shared_ptr<IRenderer> renderer);
    virtual ~QtRenderManager() = default;

    virtual void renderScene() override;

private:
    std::shared_ptr<IStateManager> stateManager;
    std::shared_ptr<IRenderer> renderer;
};
