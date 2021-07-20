#include <QTimer>
#include <QMouseEvent>
#include <QFileDialog>
#include "MainWindow.h"
#include "API/Facade/Facade.hpp"
#include "Qt/QtManagerFactory.hpp"
#include "Commands/CommandList.hpp"

#include "Scene/Scene.hpp"
#include "Objects/Camera/Camera.hpp"
#include "Qt/Renderer/QtRenderViewport.hpp"
#include "Creators/Directors/WireframeCubeDirector.hpp"


static QTimer timer;

MainWindow::MainWindow()
{
    ui.setupUi(this);

    RenderViewport* viewport = new QtRenderViewport();
    ui.mainViewport->parentWidget()->layout()->replaceWidget(ui.mainViewport, (QtRenderViewport *)viewport);
    ui.mainViewport = (QtRenderViewport *)viewport;

    managerFactory = std::shared_ptr<IManagerFactory>(new QtManagerFactory(viewport));

    {
        hierarchyWidget = new HierarchyWidget();
        addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, hierarchyWidget);
        connect(hierarchyWidget, &HierarchyWidget::selectionToggled, this, &MainWindow::selectionToggled);
    }

    {
        inspectorWidget = new InspectorWidget();
        addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, inspectorWidget);
        connect(inspectorWidget, &InspectorWidget::deleteObject, this, &MainWindow::deleteObject);
        connect(inspectorWidget, &InspectorWidget::transformChanged, this, &MainWindow::inspectorChanged);
    }

    connect((QtRenderViewport *)viewport, &QtRenderViewport::mousePressSignal, this, &MainWindow::mousePressViewport);
    connect((QtRenderViewport *)viewport, &QtRenderViewport::mouseMoveSignal, this, &MainWindow::mouseMoveViewport);
    connect((QtRenderViewport *)viewport, &QtRenderViewport::mouseReleaseSignal, this, &MainWindow::mouseReleaseViewport);
    connectActions();

    std::shared_ptr<Scene> scene;
    facade.execute(LoadEmptySceneCommand(*(managerFactory->getLoadManager()), scene));
    facade.execute(SetSceneCommand(*(managerFactory->getSceneManager()), scene));
    facade.execute(UpdateSceneCameraCommand(*(managerFactory->getCameraManager()), *scene));
    
    updateHierarchy();
    updateInspector();

    timer.callOnTimeout(this, &MainWindow::redrawScene);
    timer.start(100);
}

void MainWindow::redrawScene()
{
    std::shared_ptr<Scene> scene;
    std::shared_ptr<Camera> camera;

    facade.execute(RequestConstSceneCommand(*(managerFactory->getSceneManager()), scene));
    facade.execute(RequestConstActiveCameraCommand(*(managerFactory->getCameraManager()), camera));
    facade.execute(RenderSceneCommand(*(managerFactory->getRenderManager()), *scene, *camera));
    ui.mainViewport->update();
}

void MainWindow::appExitPressed()
{
    QApplication::quit();
}

void MainWindow::sceneCreatePressed()
{
    Scene* scene = nullptr;
    facade.execute(LoadEmptySceneCommand(*(managerFactory->getLoadManager()), scene));
    facade.execute(SetSceneCommand(*(managerFactory->getSceneManager()), scene));
    facade.execute(UpdateSceneCameraCommand(*(managerFactory->getCameraManager()), *scene));

    updateHierarchy();
}

void MainWindow::sceneLoadPressed()
{
    std::string filename = QFileDialog::getOpenFileName().toStdString();

    Scene* scene = nullptr;
    facade.execute(LoadFileSceneCommand(*(managerFactory->getLoadManager()), scene, filename));
    facade.execute(SetSceneCommand(*(managerFactory->getSceneManager()), scene));
    facade.execute(UpdateSceneCameraCommand(*(managerFactory->getCameraManager()), *scene));

    updateHierarchy();
}

void MainWindow::addObjHullModelPressed()
{
    Scene* scene = nullptr;
    std::shared_ptr<IObject> model = WireframeCubeDirector().makeObject();

    facade.execute(RequestSceneCommand(*(managerFactory->getSceneManager()), scene));
    facade.execute(AddObjectCommand(*(managerFactory->getObjectManager()), *scene, model));
    facade.execute(ClearSelectionCommand(*(managerFactory->getSelectionManager())));

    updateHierarchy();
}

void MainWindow::clearScenePressed()
{
    Scene* scene = nullptr;

    facade.execute(RequestSceneCommand(*(managerFactory->getSceneManager()), scene));
    facade.execute(ClearSceneCommand(*(managerFactory->getObjectManager()), *scene));

    updateHierarchy();
    redrawScene();
}

void MainWindow::deleteObject(IObject* object)
{
    Scene* scene = nullptr;

    facade.execute(RequestSceneCommand(*(managerFactory->getSceneManager()), scene));
    facade.execute(RemoveObjectCommand(*(managerFactory->getObjectManager()), *scene, object));
    facade.execute(ClearSelectionCommand(*(managerFactory->getSelectionManager())));

    updateHierarchy();
    updateInspector();
}

void MainWindow::selectionToggled(IObject* object, bool state)
{
    if (state)
        facade.execute(SelectObjectCommand(*(managerFactory->getSelectionManager()), object));
    else
        facade.execute(DeselectObjectCommand(*(managerFactory->getSelectionManager()), object));

    updateInspector();
}

void MainWindow::inspectorChanged()
{
    updateInspector();

    redrawScene();
}

void MainWindow::mousePressViewport(QMouseEvent* event)
{
    // if (event->button() == Qt::MouseButton::LeftButton)
    //     transformer.switchState(Transformer::State::Rotating);
    // else
    //     transformer.switchState(Transformer::State::Moving);
    // 
    // transformer.touchStart(event->pos().x(), event->pos().y());
}

void MainWindow::mouseMoveViewport(QMouseEvent* event)
{
    // Vector offset(2, 2, 2);
    // IObject* selection = nullptr;
    // 
    // facade.execute(GetSelectionCommand(*(managerFactory->getSelectionManager()), selection));
    // facade.execute(TranslateObjectCommand(*(managerFactory->getTransformManager()), selection, offset));
    // 
    // updateInspector();
    // redrawScene();
}

void MainWindow::mouseReleaseViewport(QMouseEvent* event)
{
    // transformer.touchMove(event->pos().x(), event->pos().y());
    // transformer.touchEnd();
}

void MainWindow::connectActions()
{
    connect(ui.appExit, &QAction::triggered, this, &MainWindow::appExitPressed);
    connect(ui.sceneCreate, &QAction::triggered, this, &MainWindow::sceneCreatePressed);
    connect(ui.sceneLoad, &QAction::triggered, this, &MainWindow::sceneLoadPressed);

    // add object actions
    connect(ui.objHullModel, &QAction::triggered, this, &MainWindow::addObjHullModelPressed);
    connect(ui.clearScene, &QAction::triggered, this, &MainWindow::clearScenePressed);
}

void MainWindow::updateHierarchy()
{
    if (hierarchyWidget)
    {
        Scene* scene = nullptr;
        facade.execute(RequestSceneCommand(*(managerFactory->getSceneManager()), scene));

        hierarchyWidget->updateHierarchy(*scene);
    }
}

void MainWindow::updateInspector()
{
    if (inspectorWidget)
    {
        IObject* selection = nullptr;
        facade.execute(GetSelectionCommand(*(managerFactory->getSelectionManager()), selection));

        auto group = static_cast<ObjectGroup*>(selection);
        if (group->begin() != group->end())
            inspectorWidget->inspect(selection);
        else
            inspectorWidget->inspect(nullptr);
    }
}
