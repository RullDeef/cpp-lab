#include <QFileDialog>
#include <stdexcept>
#include "LoadSceneCommand.hpp"
#include "Engine/Utils/Logger.hpp"
#include "API/Managers/ISceneManager.hpp"


LoadSceneCommand::LoadSceneCommand(std::shared_ptr<ISceneManager> manager)
    : manager(manager)
{
}

void LoadSceneCommand::execute()
{
    LOG_FUNC;

    if (manager.expired())
        throw std::runtime_error("expired pointer to scene manager");

    manager.lock()->loadScene();
}
