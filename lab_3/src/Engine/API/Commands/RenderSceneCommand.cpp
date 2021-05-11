#include "RenderSceneCommand.hpp"

RenderSceneCommand::RenderSceneCommand(std::shared_ptr<Controller> controller, std::shared_ptr<IRenderer> renderer)
    : ICommand(controller), renderer(renderer)
{
}

void RenderSceneCommand::execute()
{
    getController()->renderScene(renderer);
}
