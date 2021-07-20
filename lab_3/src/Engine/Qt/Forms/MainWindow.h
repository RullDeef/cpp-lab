#pragma once

#include <memory>
#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "API/Facade/Facade.hpp"
#include "API/Managers/IManagerFactory.hpp"

#include "Qt/Forms/HierarhyWidget/HierarchyWidget.h"
#include "Qt/Forms/InspectorWidget/InspectorWidget.h"

class IObject;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

protected slots:
    void redrawScene();

    void appExitPressed();
    void sceneCreatePressed();
    void sceneLoadPressed();

    void addObjHullModelPressed();
    void clearScenePressed();

    void deleteObject(IObject* object);
    void selectionToggled(IObject* object, bool state);
    void inspectorChanged();

    void mousePressViewport(QMouseEvent* event);
    void mouseMoveViewport(QMouseEvent* event);
    void mouseReleaseViewport(QMouseEvent* event);

private:
    void connectActions();

    void updateHierarchy();
    void updateInspector();

    Ui::MainWindowClass ui;
    Facade facade;
    std::shared_ptr<IManagerFactory> managerFactory;

    HierarchyWidget* hierarchyWidget;
    InspectorWidget* inspectorWidget;
};
