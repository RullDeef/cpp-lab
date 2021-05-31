#pragma once

#include "API/Managers/IManagerFactory.hpp"
#include "MainWindow.h"

class QtManagerFactory : public IManagerFactory
{
public:
    virtual ~QtManagerFactory() {}

    virtual std::shared_ptr<IStateManager> createStateManager() override;
    virtual std::shared_ptr<ISceneManager> createSceneManager(std::shared_ptr<IStateManager> stateManager) override;

private:
    QApplication* qtApp;
    MainWindow* mainWindow;
};
