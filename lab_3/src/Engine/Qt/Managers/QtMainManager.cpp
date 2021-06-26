#include "QtMainManager.hpp"

QtMainManager::QtMainManager(int argc, char* argv[])
    : qtApp(argc, argv)
{
    mainWindow = new MainWindow();
    mainWindow->show();

    QMenu* ampMenu = new QMenu("[&>]");
    QAction* action = ampMenu->addAction(u8"Выйти");

    QObject::connect(action, &QAction::triggered, this, &QtMainManager::close);

    addMenu(ampMenu);
}

QtMainManager::~QtMainManager()
{
    delete mainWindow;
}

void QtMainManager::addMenu(QMenu* menu)
{
    mainWindow->addMenu(menu);
}

void QtMainManager::shutDown(int exitCode)
{
    if (exitCode == 0)
        qtApp.quit();
    else
        qtApp.exit(exitCode);
}

int QtMainManager::runMainloop()
{
    return qtApp.exec();
}

void QtMainManager::close()
{
    qtApp.quit();
}
