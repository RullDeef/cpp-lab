#pragma once

#include <memory>
#include <string>
#include "IManager.hpp"

class IObject;
class Scene;


class LoadManager : public IManager
{
public:
    std::shared_ptr<Scene> loadEmptyScene();
    std::shared_ptr<Scene> loadScene(const std::string& filename);

    void loadWireframe(Scene& scene, const std::string& filename);
    void loadCamera(Scene& scene, const std::string& filename);
};
