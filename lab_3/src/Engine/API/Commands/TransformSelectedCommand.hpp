#pragma once

#include "ICommand.hpp"
#include "Core/Math/Transform.hpp"


class TransformSelectedCommand : public ICommand
{
public:
    explicit TransformSelectedCommand(const Transform& t);
    virtual void execute(std::shared_ptr<Controller> controller) override;

private:
    Transform transform;
};
