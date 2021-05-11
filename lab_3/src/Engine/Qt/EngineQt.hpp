#pragma once

#include "Engine/API/Engine.hpp"
#include "MainWindow.h"
#include <QObject>

class EngineQt : public QObject, public Engine
{
    Q_OBJECT

public:
    EngineQt(QApplication& qtApp);
    ~EngineQt();

public slots:
    void processCommandsQt();

protected:
    virtual void prepareWorkspace(int argc, char* argv[]) override;

    virtual int runMainLoop() override;

private:
    QApplication* qtApp;
    MainWindow* mainWindow;
};
