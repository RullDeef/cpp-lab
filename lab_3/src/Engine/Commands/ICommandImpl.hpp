#pragma once

#include "ICommand.hpp"


template<typename _Manager, void (_Manager::* _ManagerMethod)()>
ManagerCommand<_Manager, _ManagerMethod>::ManagerCommand(_Manager& manager)
    : manager(manager)
{
}

template<typename _Manager, void (_Manager::* _ManagerMethod)()>
inline void ManagerCommand<_Manager, _ManagerMethod>::execute()
{
    (manager.*_ManagerMethod)();
}
