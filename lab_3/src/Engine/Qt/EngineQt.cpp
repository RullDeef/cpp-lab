#include "EngineQt.hpp"
#include "../Tools/Logger.hpp"
#include "Renderer/QtRenderer.hpp"
#include <QTimer>

#include "Scene/SceneObjectGroup.hpp"
#include "Scene/Objects/Builders/TransformBuilder.hpp"
#include "Scene/Objects/Builders/DefaultHullCubeBuilder.hpp"


EngineQt::EngineQt(QApplication& qtApp)
    : qtApp(&qtApp)
{
}

EngineQt::~EngineQt()
{
    delete mainWindow;
}

static std::shared_ptr<ISceneObject> object;
static Vector axis = { 1.0, 0.0, 0.0 };

void EngineQt::processCommandsQt()
{
    if (isRunning())
    {
        processCommands();

        axis = axis * Matrix::rotation({ 0.0, 1.0, 0.0 }, 0.1);
        object->getTransform().rotate(axis, 0.01);
        renderScene();

        int i = 1;
        for (auto& child : *(SceneObjectGroup*)&*object)
        {
            child->getTransform().rotate({double(i % 2), double(i % 3), double(i)}, 0.01);
            i++;
        }

        QTimer::singleShot(0, this, &EngineQt::processCommandsQt);
    }
}

void EngineQt::prepareWorkspace(int argc, char* argv[])
{
    LOG_FUNC;

    mainWindow = new MainWindow();

    QGraphicsView* graphics = mainWindow->getGraphisView();
    setRenderer(std::shared_ptr<IRenderer>(new QtRenderer(graphics)));

    // add sample qube
    object = std::shared_ptr<ISceneObject>(new SceneObjectGroup());

    for (double dx = -1.5; dx <= 1.5; dx += 1.5)
    {
        ((SceneObjectGroup*)&*object)->addObject(DefaultHullCubeBuilder()
            .setWidth(1.0)
            .build(
                TransformBuilder()
                .translate({ dx, 0.0, 0.0 })
                .build())
        );
    }
    getController().addSceneObject(object);

    QTimer::singleShot(0, this, &EngineQt::processCommandsQt);

    renderScene();

    mainWindow->show();
}

int EngineQt::runMainLoop()
{
    LOG_FUNC;

    int res = qtApp->exec();
    shutdown();
    return res;
}
