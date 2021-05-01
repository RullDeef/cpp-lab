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
const_list_iterator<T>::const_list_iterator(const std::shared_ptr<list_node<T>>& node) noexcept
    : _node(node)
{}

template<typename T>
const T& const_list_iterator<T>::operator*() const
{
    if (_node.expired())
        throw invalid_state_iterator_exception(__FILE__, typeid(*this).name(), __LINE__);
    return _node.lock()->data();
}

template<typename T>
const T* const_list_iterator<T>::operator->() const
{
    if (_node.expired())
        throw invalid_state_iterator_exception(__FILE__, typeid(*this).name(), __LINE__);
    return &_node.lock()->data();
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
    if (auto ptr = _node.lock())
        _node = ptr->next();
    else
        throw out_of_bounds_iterator_exception(__FILE__, typeid(*this).name(), __LINE__);
    return *this;
}

template<typename T>
const_list_iterator<T> const_list_iterator<T>::operator++(int)
{
    const_list_iterator<T> temp = *this;
    ++*this;
    return temp;
}
