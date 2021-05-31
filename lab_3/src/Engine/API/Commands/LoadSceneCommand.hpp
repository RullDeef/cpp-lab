#include "ICommand.hpp"
#include <memory>

#include "API/Managers/ISceneManager.hpp"


class LoadSceneCommand : public ICommand
{
public:
    LoadSceneCommand(std::shared_ptr<ISceneManager> manager);

    virtual void execute() override;

private:
    std::weak_ptr<ISceneManager> manager;
};
