#include "Controller.hpp"
#include <algorithm>
#include "Engine/Utils/Logger.hpp"
#include <typeinfo>


Controller::Controller(std::shared_ptr<IManagerFactory> managerFactory)
{

    // sceneManager = managerFactory->createSceneManager();
    // objectManager = managerFactory->createObjectManager();
    // renderManager = managerFactory->createRenderManager();
    // transformManager = managerFactory->createTransformManager();
    // cameraManager = managerFactory->createCameraManager();
}

Controller::~Controller()
{
    for (auto& [type, manager] : managers)
        unregisterManager(manager);
}

void Controller::registerManager(std::shared_ptr<IManager> manager)
{
    const type_info& type = typeid(*manager);
    if (managers.count(type) != 0)
        throw std::runtime_error(std::string("Controller: duplicate of manager ") + type.name());
    managers[type] = manager;

    std::string msg = (std::string("Registered manager: ") + type.name());
    LOGGER_LOG(msg.c_str());
}

void Controller::unregisterManager(std::shared_ptr<IManager> manager)
{
    const type_info& type = typeid(*manager);
    if (managers.count(type) == 0)
        throw std::runtime_error(std::string("Controller: tried to unregister not registered manager ") + type.name());
    managers[type] = nullptr;

    std::string msg = (std::string("Unregistered manager: ") + type.name());
    LOGGER_LOG(msg.c_str());
}
