#include "ISceneManager.hpp"
#include "Engine/Utils/Logger.hpp"

/*
std::shared_ptr<Scene> ISceneManager::getScene()
{
    return scene;
}

void ISceneManager::createEmptyScene()
{
    LOG_FUNC;

    scene = std::make_shared<Scene>();
}

void ISceneManager::loadScene(const char* filename)
{
    LOG_FUNC;

    QString filename = QFileDialog::getOpenFileName(nullptr, "загрузить сцену",
        "Scene files (*.scn)");

    if (!filename.isEmpty())
    {
        QByteArray ba = filename.toLocal8Bit();
        getController()->loadScene(ba.data());
    }
}

bool ISceneManager::addSceneObject(std::shared_ptr<ISceneObject> object)
{
    LOG_FUNC;

    scene->addObject(object);
    return true;
}

void ISceneManager::renderScene(std::shared_ptr<IRenderer> renderer, std::shared_ptr<ICamera> camera)
{
    renderer->beginFrame(camera);

    for (auto& object : *scene)
        object->draw(renderer);

    renderer->endFrame();
}
*/

