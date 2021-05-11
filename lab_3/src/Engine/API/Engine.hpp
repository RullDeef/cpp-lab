#pragma once

#include "Commands/CommandQueue.hpp"
#include "Controller.hpp"
#include "Renderer/IRenderer.hpp"

class Engine
{
public:
    Engine();
    virtual ~Engine() {};

    int run(int argc, char* argv[]);

protected:
    // подготавливает рабочее пространство перед запуском
    // открывает окошки + запускает backend
    virtual void prepareWorkspace(int argc, char* argv[]) = 0;

    // запускает главный цикл работы движка
    virtual int runMainLoop() = 0;

    // обработка поступивших команд
    void processCommands();

    bool isRunning() const;
    void shutdown();

    void setRenderer(std::shared_ptr<IRenderer> newRenderer);
    std::shared_ptr<IRenderer> getRenderer();

    Controller& getController();

#pragma region Commands
    void renderScene();
#pragma endregion

private:
    std::shared_ptr<Controller> controller;
    CommandQueue commandQueue;

    std::shared_ptr<IRenderer> renderer;

    bool running = false;
};
