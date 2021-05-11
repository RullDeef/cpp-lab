#pragma once

#include "ICommand.hpp"


class RenderSceneCommand : public ICommand
{
public:
    RenderSceneCommand(std::shared_ptr<Controller> controller, std::shared_ptr<IRenderer> renderer);

    void execute() override;

private:
    std::shared_ptr<IRenderer> renderer;
};
