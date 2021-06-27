#pragma once

#include "ICommand.hpp"


template<typename _Manager, void (_Manager::* _ManagerMethod)()>
inline ManagerCommand<_Manager, _ManagerMethod>::ManagerCommand(_Manager& manager)
    : manager(manager)
{
}

template<typename _Manager, void (_Manager::* _ManagerMethod)()>
inline void ManagerCommand<_Manager, _ManagerMethod>::execute()
{
    (manager.*_ManagerMethod)();
}

template<typename _Manager, typename _DataType, typename method_resolver<_Manager, _DataType>::value_type _Method>
inline RequestCommand<_Manager, _DataType, _Method>::RequestCommand(_Manager& manager, _DataType*& data)
    : manager(manager), data(data)
{
}

template<typename _Manager, typename _DataType, typename method_resolver<_Manager, _DataType>::value_type _Method>
inline void RequestCommand<_Manager, _DataType, _Method>::execute()
{
    data = &(manager.*_Method)();
}
