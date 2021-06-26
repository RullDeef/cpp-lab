#pragma once

#include "API/Managers/IMainManager.hpp"


class QtMainManager : public IMainManager
{
public:
    QtMainManager();
    virtual ~QtMainManager();

    virtual void shutDown(int exitCode = 0) override;
    virtual int runMainloop() override;

protected slots:
    void close();

private:
    QApplication qtApp;
    MainWindow* mainWindow;
};
