#include "RenderSceneCommand.hpp"
#include "Engine/API/Controller.hpp"
#include "Engine/API/Event/SceneRenderEvent.hpp"
#include "Engine/API/Managers/ISceneManager.hpp"


RenderSceneCommand::RenderSceneCommand(std::shared_ptr<IRenderManager> manager)
    : manager(manager)
{
}

void RenderSceneCommand::execute()
{
    /*
    if (auto sceneMng = getController()->request<SceneManager>())
    {
        auto scene = sceneMng->getScene();
        getController()->postEvent(new SceneRenderEvent(scene));
    }
    */
}
