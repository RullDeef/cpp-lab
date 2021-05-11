#include <memory>
#include "Engine/Qt/EngineQt.hpp"
#include "Engine/Tools/Logger.hpp"

int main(int argc, char *argv[])
{
    Logger::setLogFile("log/testing");

    LOG_FUNC;

    QApplication app(argc, argv);

    std::unique_ptr<Engine> engine = std::make_unique<EngineQt>(app);
    return engine->run(argc, argv);
}
