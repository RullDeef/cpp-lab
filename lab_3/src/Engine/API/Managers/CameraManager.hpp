#pragma once

#include "IManager.hpp"

class Camera;
class Scene;


class CameraManager : public IManager
{
public:
    Camera& getActiveCamera();
    const Camera& getActiveCamera() const;

    void setScene(Scene& newScene);

    void switchNextCamera();
    void switchPrevCamera();

private:
    Scene* scene = nullptr;
    Camera* activeCamera = nullptr;
};
