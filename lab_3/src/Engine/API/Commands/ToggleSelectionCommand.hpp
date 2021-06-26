#pragma once

#include "ICommand.hpp"
#include "API/Objects/ISceneObject.hpp"


class ToggleSelectionCommand : public ICommand
{
public:
    explicit ToggleSelectionCommand(std::shared_ptr<ISceneObject> object);
    virtual void execute(std::shared_ptr<Controller> controller) override;

private:
    std::weak_ptr<ISceneObject> object;
};
