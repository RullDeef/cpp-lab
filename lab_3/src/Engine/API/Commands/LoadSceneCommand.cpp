#include <QFileDialog>
#include "LoadSceneCommand.hpp"
#include "../../Tools/Logger.hpp"

LoadSceneCommand::LoadSceneCommand(std::shared_ptr<Controller> controller)
    : ICommand(controller)
{
}

void LoadSceneCommand::execute()
{
    LOG_FUNC;

    QString filename = QFileDialog::getOpenFileName(nullptr, "загрузить сцену",
        "Scene files (*.scn)");

    if (!filename.isEmpty())
    {
        QByteArray ba = filename.toLocal8Bit();
        getController()->loadScene(ba.data());
    }
}
