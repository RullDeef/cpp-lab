#pragma once

#include "ICommand.hpp"

class IRenderManager;

class RenderSceneCommand : public ICommand
{
public:
    RenderSceneCommand(std::shared_ptr<IRenderManager> manager);

    void execute() override;

private:
    std::shared_ptr<IRenderManager> manager;
};
