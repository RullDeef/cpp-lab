#pragma once

#include "ICommand.hpp"


class CreateEmptySceneCommand : public ICommand
{
public:
    virtual void execute(std::shared_ptr<Controller> controller) override;
};
