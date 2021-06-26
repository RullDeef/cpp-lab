#pragma once


class ICommand;

class Facade
{
public:
    void execute(ICommand& command);
};

