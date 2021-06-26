#pragma once

#include "ICommand.hpp"


class ClearSceneCommand : public ICommand
{
public:
    virtual void execute(std::shared_ptr<Controller> controller) override;
};
