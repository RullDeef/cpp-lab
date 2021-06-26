#pragma once

#include <memory>
#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "API/Facade.hpp"

#include "Qt/Forms/HierarhyWidget/HierarchyWidget.h"
#include "Qt/Forms/InspectorWidget/InspectorWidget.h"
#include "API/Transformer/Transformer.hpp"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(std::shared_ptr<IManagerFactory> managerFactory);

protected slots:
    void redrawScene();

    void appExitPressed();
    void sceneCreatePressed();
    void sceneLoadPressed();

    void addObjHullModelPressed();
    void clearScenePressed();

    void selectionToggled(std::shared_ptr<ISceneObject> object, bool state);

    void mousePressViewport(QMouseEvent* event);
    void mouseMoveViewport(QMouseEvent* event);
    void mouseReleaseViewport(QMouseEvent* event);

private:
    void connectActions();

    Ui::MainWindowClass ui;
    Facade facade;
    std::shared_ptr<IManagerFactory> managerFactory;

    Transformer transformer;
    HierarchyWidget* hierarchyWidget;
    InspectorWidget* inspectorWidget;
};
