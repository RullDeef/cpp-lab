#pragma once

#include "list.hpp"

template<typename T>
list<T>::list(const list& lst)
{
    for (const auto& value : lst)
        push_back(value);
}

template<typename T>
inline list<T>::list(list&& temp) noexcept
    : head(temp.head)
{}

template<typename T>
inline list<T>::list(std::initializer_list<T> init_list)
{
    for (const auto& value : init_list)
        push_back(value);
}

template<typename T>
size_t list<T>::size() const noexcept
{
    size_t size = 0;
    for (node_ptr node = head; node; node = node->next())
        size++;
    return size;
}

template<typename T>
inline void list<T>::clear() noexcept
{
    head = node_ptr(nullptr);
}

template<typename T>
inline void list<T>::push_back(const T& value)
{
    if (!head)
        head = create_new_node(value);
    else
    {
        node_ptr new_node = create_new_node(value);
        head->insert_end(new_node);
    }
}

template<typename T>
inline typename list<T>::iterator list<T>::begin() noexcept
{
    return iterator(head);
}

template<typename T>
inline typename list<T>::iterator list<T>::end() noexcept
{
    return iterator(node_ptr(nullptr));
}

template<typename T>
inline typename list<T>::const_iterator list<T>::begin() const noexcept
{
    // return const_iterator(list_node<const T>::node_ptr(list_node<const T>(*head)));
    return const_iterator(list_node<const T>::node_ptr(nullptr));
}

template<typename T>
inline typename list<T>::const_iterator list<T>::end() const noexcept
{
    return const_iterator(list_node<const T>::node_ptr(nullptr));
}

template<typename T>
typename list<T>::node_ptr list<T>::create_new_node(const T& value)
{
    try
    {
        return node_ptr(new list_node<T>(value));
    }
    catch (std::bad_alloc)
    {
        throw memory_list_exception(__FILE__, typeid(*this).name(), __LINE__);
    }
}
