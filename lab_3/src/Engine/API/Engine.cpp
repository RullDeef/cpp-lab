#include "Engine.hpp"
#include <thread>
#include <future>
#include <exception>
#include <QtWidgets/QMainWindow>
#include "../Tools/Logger.hpp"

#include "Engine/API/Commands/RenderSceneCommand.hpp"
#include "Engine/API/Commands/LoadSceneCommand.hpp"

Engine::Engine()
    : controller(new Controller())
{
}

int Engine::run(int argc, char* argv[])
{
    LOG_FUNC;

    try
    {
        prepareWorkspace(argc, argv);

        running = true;
        return runMainLoop();
    }
    catch (std::exception e)
    {
        LOGGER_ERROR(e.what());
        return -1;
    }
}

void Engine::processCommands()
{
    commandQueue.executeNext();
}

bool Engine::isRunning() const
{
    return running;
}

void Engine::shutdown()
{
    LOG_FUNC;

    running = false;
}

void Engine::setRenderer(std::shared_ptr<IRenderer> newRenderer)
{
    LOG_FUNC;

    renderer = newRenderer;
}

std::shared_ptr<IRenderer> Engine::getRenderer()
{
    return renderer;
}

Controller& Engine::getController()
{
    return *controller;
}

void Engine::renderScene()
{
    commandQueue.postCommand(std::shared_ptr<ICommand>(new RenderSceneCommand(controller, renderer)));
}
