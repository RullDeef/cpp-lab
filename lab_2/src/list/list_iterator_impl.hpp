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
list_iterator<T>::list_iterator(typename const base_list_node::node_ptr& node) noexcept
    : const_list_iterator<T>(node)
{}

template<typename T>
list_iterator<T>& list_iterator<T>::operator=(const list_iterator& iter)
{
    _node = iter._node;
    return *this;
}

template<typename T>
T& list_iterator<T>::operator*()
{
    if (auto ptr = _node.lock())
    {
        if (auto data_node = dynamic_cast<list_node<T>*>(ptr.get()))
            return **data_node;
        throw invalid_state_iterator_exception(__FILE__, typeid(*this).name(), __LINE__);
    }

    throw invalid_state_iterator_exception(__FILE__, typeid(*this).name(), __LINE__);
}

template<typename T>
T* list_iterator<T>::operator->()
{
    if (auto ptr = _node.lock())
    {
        if (auto data_node = dynamic_cast<list_node<T>*>(ptr.get()))
            return **data_node;
        throw invalid_state_iterator_exception(__FILE__, typeid(*this).name(), __LINE__);
    }

    throw invalid_state_iterator_exception(__FILE__, typeid(*this).name(), __LINE__);
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

template<typename T>
list_iterator<T>& list_iterator<T>::operator--()
{
    const_list_iterator<T>::operator--();
    return *this;
}

template<typename T>
list_iterator<T> list_iterator<T>::operator--(int)
{
    list_iterator tmp = *this;
    --* this;
    return tmp;
}
