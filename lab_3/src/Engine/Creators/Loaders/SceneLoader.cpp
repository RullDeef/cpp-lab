#include "SceneLoader.hpp"
#include "Scene/Scene.hpp"
#include "Creators/Loaders/OBJLoader/OBJLoader.hpp"


Scene* SceneLoader::loadScene(const std::string& filename)
{
    OBJLoader objLoader(filename);

    for (const auto& face : objLoader.getFaces())
    {
        const auto& positions = face.getPositions();

        for (auto i : positions)
        {
            objLoader.getPositions();
        }
    }

    return nullptr;
}
