#include <memory>
#include <QApplication>
#include "Engine/Utils/Logger.hpp"
#include "Engine/API/Commands/CommandList.hpp"
#include "Engine/API/Controller.hpp"
#include "Engine/API/Facade.hpp"
#include "Engine/Qt/QtManagerFactory.hpp"


int main(int argc, char *argv[])
{
    Logger::setLogFile("log/testing");

    LOG_FUNC;

    QApplication app(argc, argv);

    auto qtFactory = std::shared_ptr<IManagerFactory>(new QtManagerFactory());
    auto controller = std::make_shared<Controller>(qtFactory);
    auto facade = std::make_shared<Facade>();

    // create empty scene
    auto command = std::shared_ptr<ICommand>(new LoadSceneCommand(controller->getSceneManager()));
    facade->execute(command);

    return 0; // app.exec();
}
