#pragma once

#include <string>
#include "IManager.hpp"

class IObject;
class Scene;


class LoadManager : public IManager
{
public:
    Scene* loadEmptyScene();
    // Scene* loadScene(const std::string& filename);

    void loadWireframe(Scene& scene, const std::string& filename);
    void loadCamera(Scene& scene, const std::string& filename);
};
