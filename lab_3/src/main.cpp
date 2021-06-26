#include <QApplication>
#include "Utils/Logger.hpp"
#include "Qt/Forms/MainWindow.h"


int main(int argc, char *argv[])
{
    Logger::setLogFile("log/testing");

    QApplication qtApp(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return qtApp.exec();
}
