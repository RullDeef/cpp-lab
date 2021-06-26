#pragma once


class ICommand
{
public:
    virtual ~ICommand() = default;
    virtual void execute() = 0;
};


template<typename _Manager, void (_Manager::* _ManagerMethod)()>
class ManagerCommand : public ICommand
{
public:
    explicit ManagerCommand(_Manager& manager);
    virtual void execute() override;

private:
    _Manager& manager;
};


#include "ICommandImpl.hpp"
