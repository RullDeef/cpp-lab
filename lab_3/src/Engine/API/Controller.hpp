#pragma once

#include "API/Managers/IManagerFactory.hpp"
#include <map>


class Controller
{
public:
    explicit Controller(std::shared_ptr<IManagerFactory> managerFactory);
    ~Controller();

    std::shared_ptr<SceneManager> getSceneManager();
    std::shared_ptr<ObjectManager> getObjectManager();
    std::shared_ptr<RenderManager> getRenderManager();
    std::shared_ptr<TransformManager> getTransformManager();
    std::shared_ptr<CameraManager> getCameraManager();

    //IManager* getManagerPtr(type_info managerType);

    template<typename _Manager>
    _Manager& getManager();

protected:
    // bool hasManager(type_info managerType) const;
    void registerManager(std::shared_ptr<IManager> manager);
    void unregisterManager(std::shared_ptr<IManager> manager);

private:
    // std::shared_ptr<SceneManager> sceneManager;
    // std::shared_ptr<ObjectManager> objectManager;
    // std::shared_ptr<RenderManager> renderManager;
    // std::shared_ptr<TransformManager> transformManager;
    // std::shared_ptr<CameraManager> cameraManager;

    std::map<type_info, std::shared_ptr<IManager>> managers;
};

#include "ControllerImpl.hpp"
