#pragma once

#include <type_traits>


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


template<typename _Manager, typename _DataType, bool is_const = std::is_const<_DataType>::value>
struct method_resolver;

template<typename _Manager, typename _DataType>
struct method_resolver<_Manager, _DataType, true>
{
    using value_type = const _DataType& (_Manager::*)() const;
};

template<typename _Manager, typename _DataType>
struct method_resolver<_Manager, _DataType, false>
{
    using value_type = _DataType& (_Manager::*)();
};


template<typename _Manager, typename _DataType, typename method_resolver<_Manager, _DataType>::value_type _Method>
class RequestCommand : public ICommand
{
public:
    RequestCommand(_Manager& manager, _DataType*& data);
    virtual void execute() override;

private:
    _Manager& manager;
    _DataType*& data;
};


#include "ICommandImpl.hpp"
