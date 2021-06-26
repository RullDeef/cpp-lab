#include "MainWindow.h"
#include "API/Commands/CommandList.hpp"
#include "Qt/QtManagerFactory.hpp"
#include <QTimer>
#include <QMouseEvent>

#include "API/Objects/Builders/DefaultHullCubeBuilder.hpp"


static QTimer timer;

MainWindow::MainWindow(std::shared_ptr<IManagerFactory> managerFactory)
    : managerFactory(managerFactory), facade(managerFactory)
{
    ui.setupUi(this);

    RenderViewport* viewport = new RenderViewport();
    ui.mainViewport->parentWidget()->layout()->replaceWidget(ui.mainViewport, viewport);
    ui.mainViewport = viewport;

    {
        hierarchyWidget = new HierarchyWidget(managerFactory->createSceneManager());
        addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, hierarchyWidget);
        connect(hierarchyWidget, &HierarchyWidget::selectionToggled, this, &MainWindow::selectionToggled);
    }

    {
        inspectorWidget = new InspectorWidget();
        addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, inspectorWidget);
    }

    connect(viewport, &RenderViewport::mousePressSignal, this, &MainWindow::mousePressViewport);
    connect(viewport, &RenderViewport::mouseMoveSignal, this, &MainWindow::mouseMoveViewport);
    connect(viewport, &RenderViewport::mouseReleaseSignal, this, &MainWindow::mouseReleaseViewport);
    connectActions();

    timer.callOnTimeout(this, &MainWindow::redrawScene);
    timer.start(100);
}

void MainWindow::redrawScene()
{
    facade->execute(std::make_shared<RenderSceneCommand>());
    ui.mainViewport->update();
}

void MainWindow::appExitPressed()
{
    QApplication::quit();
}

void MainWindow::sceneCreatePressed()
{
    facade->execute(std::make_shared<CreateEmptySceneCommand>());

    if (hierarchyWidget)
        hierarchyWidget->updateHierarchy();

    transformer.reset(managerFactory->createCameraManager()->getActiveCamera());
}

void MainWindow::sceneLoadPressed()
{
    facade->execute(std::make_shared<LoadSceneCommand>());

    if (hierarchyWidget)
        hierarchyWidget->updateHierarchy();

    transformer.reset(managerFactory->createCameraManager()->getActiveCamera());
}

void MainWindow::addObjHullModelPressed()
{
    auto builder = DefaultHullCubeBuilder();
    builder.setName("Hull Cube");
    builder.setWidth(1.0);
    auto object = builder.build();

    auto command = std::shared_ptr<ICommand>(new AddHullModelCommand(object));
    facade->execute(command);

    if (hierarchyWidget)
        hierarchyWidget->updateHierarchy();
}

void MainWindow::clearScenePressed()
{
    auto command = std::shared_ptr<ICommand>(new ClearSceneCommand());
    facade->execute(command);

    if (hierarchyWidget)
        hierarchyWidget->updateHierarchy();

    transformer.reset();
    redrawScene();
}

void MainWindow::selectionToggled(std::shared_ptr<ISceneObject> object, bool state)
{
    auto command = std::shared_ptr<ICommand>(new ToggleSelectionCommand(object));
    facade->execute(command);

    auto selection = managerFactory->createSelectionManager()->getSelected();
    if (selection->size() == 1)
        inspectorWidget->inspect(*selection->begin());
    else
        inspectorWidget->inspect(nullptr);
}

void MainWindow::mousePressViewport(QMouseEvent* event)
{
    if (event->button() == Qt::MouseButton::LeftButton)
        transformer.switchState(Transformer::State::Rotating);
    else
        transformer.switchState(Transformer::State::Moving);

    transformer.touchStart(event->pos().x(), event->pos().y());
}

void MainWindow::mouseMoveViewport(QMouseEvent* event)
{
    if (transformer.isActive())
    {
        transformer.touchMove(event->pos().x(), event->pos().y());
        Transform t = transformer.getResult();
        auto command = std::shared_ptr<ICommand>(new TransformSelectedCommand(t));
        facade->execute(command);
    }
}

void MainWindow::mouseReleaseViewport(QMouseEvent* event)
{
    transformer.touchMove(event->pos().x(), event->pos().y());
    transformer.touchEnd();
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
