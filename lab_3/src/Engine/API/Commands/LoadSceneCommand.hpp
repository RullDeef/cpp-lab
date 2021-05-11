#include "ICommand.hpp"


class LoadSceneCommand : public ICommand
{
public:
    LoadSceneCommand(std::shared_ptr<Controller> controller);

    void execute() override;
};
