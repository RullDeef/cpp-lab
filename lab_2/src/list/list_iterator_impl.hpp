#pragma once

#include "list_iterator.hpp"


template<typename T>
list_iterator<T>::list_iterator(const list_iterator& iter) noexcept
    : const_list_iterator<T>(iter)
{}

template<typename T>
list_iterator<T>::list_iterator(list_iterator&& iter) noexcept
    : const_list_iterator<T>(iter)
{}

template<typename T>
list_iterator<T>::list_iterator(const std::shared_ptr<list_node<T>>& node) noexcept
    : const_list_iterator<T>(node)
{}

template<typename T>
T& list_iterator<T>::operator*()
{
    if (_node.expired())
        throw invalid_state_iterator_exception(__FILE__, typeid(*this).name(), __LINE__);
    return _node.lock()->data();
}

template<typename T>
T* list_iterator<T>::operator->()
{
    if (_node.expired())
        throw invalid_state_iterator_exception(__FILE__, typeid(*this).name(), __LINE__);
    return &_node.lock()->data();
}

template<typename T>
list_iterator<T>& list_iterator<T>::operator++()
{
    const_list_iterator<T>::operator++();
    return *this;
}

template<typename T>
list_iterator<T> list_iterator<T>::operator++(int)
{
    list_iterator tmp = *this;
    ++*this;
    return tmp;
}
