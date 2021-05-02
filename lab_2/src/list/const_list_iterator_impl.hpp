#pragma once

#include "const_list_iterator.hpp"


template<typename T>
const_list_iterator<T>::const_list_iterator(const const_list_iterator& iter) noexcept
    : _node(iter._node)
{}

template<typename T>
const_list_iterator<T>::const_list_iterator(const_list_iterator&& iter) noexcept
    : _node(iter._node)
{}

template<typename T>
const_list_iterator<T>::const_list_iterator(typename const base_list_node::node_ptr& node) noexcept
    : _node(node)
{}

template<typename T>
const_list_iterator<T>& const_list_iterator<T>::operator=(const const_list_iterator& iter)
{
    _node = iter._node;
    return *this;
}

template<typename T>
const T& const_list_iterator<T>::operator*() const
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
const T* const_list_iterator<T>::operator->() const
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
inline const_list_iterator<T>::operator bool() const noexcept
{
    return bool(_node);
}

template<typename T>
inline bool const_list_iterator<T>::operator==(const const_list_iterator& iter) const
{
    return (_node.lock()) == (iter._node.lock());
}

template<typename T>
inline bool const_list_iterator<T>::operator!=(const const_list_iterator& iter) const
{
    return (_node.lock()) != (iter._node.lock());
}

template<typename T>
const_list_iterator<T>& const_list_iterator<T>::operator++()
{
    if (_node.expired())
        throw invalid_state_iterator_exception(__FILE__, typeid(*this).name(), __LINE__);
    _node = _node.lock()->next();
    return *this;
}

template<typename T>
const_list_iterator<T> const_list_iterator<T>::operator++(int)
{
    const_list_iterator<T> temp = *this;
    ++*this;
    return temp;
}

template<typename T>
const_list_iterator<T>& const_list_iterator<T>::operator--()
{
    if (_node.expired())
        throw invalid_state_iterator_exception(__FILE__, typeid(*this).name(), __LINE__);
    _node = _node.lock()->prev();
    return *this;
}

template<typename T>
const_list_iterator<T> const_list_iterator<T>::operator--(int)
{
    const_list_iterator<T> temp = *this;
    --* this;
    return temp;
}

template<typename T>
typename base_list_node::node_ptr const_list_iterator<T>::node()
{
    if (auto ptr = _node.lock())
        return ptr;
    else
        throw invalid_state_iterator_exception(__FILE__, typeid(*this).name(), __LINE__);
}
