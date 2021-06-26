#include "TransformSelectedCommand.hpp"
#include "API/Controller.hpp"


TransformSelectedCommand::TransformSelectedCommand(const Transform& t)
    : transform(t)
{
}

void TransformSelectedCommand::execute(std::shared_ptr<Controller> controller)
{
    controller->getTransformManager()->transformSelected(transform);
}
