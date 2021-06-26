#include "SceneManager.hpp"
#include "API/Scene/Directors/EmptySceneDirector.hpp"
#include "Engine/Utils/Logger.hpp"


SceneManager::SceneManager()
{
    createEmptyScene();
}

void SceneManager::createEmptyScene()
{
    LOG_FUNC;

    auto builder = std::make_shared<SceneBuilder>();
    EmptySceneDirector director(builder);

    scene = director.makeScene();
}

void SceneManager::loadScene(const char* filename)
{
    LOG_FUNC;

    //QString filename = QFileDialog::getOpenFileName(nullptr, "загрузить сцену",
    //    "Scene files (*.scn)");

    //if (!filename.isEmpty())
    {
        //QByteArray ba = filename.toLocal8Bit();
        //getController()->loadScene(ba.data());
    }
}

Scene& SceneManager::getScene()
{
    return *scene;
}

const Scene& SceneManager::getScene() const
{
    return *scene;
}
