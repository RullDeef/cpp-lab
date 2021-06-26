#pragma once

#include "ICommand.hpp"


class AddHullModelCommand : public ICommand
{
public:
    explicit AddHullModelCommand(std::shared_ptr<ISceneObject> object);
    virtual void execute(std::shared_ptr<Controller> controller) override;

private:
    std::shared_ptr<ISceneObject> object;
};
