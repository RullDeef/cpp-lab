#pragma once

#include "list_node.hpp"

template<typename T>
list_node<T>::list_node(const T& value)
    : _data(value)
{}

template<typename T>
list_node<T>::list_node(T&& value) noexcept
    : _data(value)
{}

template<typename T>
list_node<T>::operator list_node<const T>() const noexcept
{
    return list_node<const T>(_data);
}

template<typename T>
inline T& list_node<T>::operator*() noexcept
{
    return _data;
}

template<typename T>
inline T* list_node<T>::operator->() noexcept
{
    return _data;
}

template<typename T>
inline const T& list_node<T>::operator*() const noexcept
{
    return _data;
}

template<typename T>
inline const T* list_node<T>::operator->() const noexcept
{
    return _data;
}

template<typename T>
bool list_node<T>::is_empty() const
{
    return false;
}
