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
inline list<T>& list<T>::operator=(const list<T>& lst)
{
    clear();
    for (const auto& value : lst)
        push_back(value);
    return *this;
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
    head = nullptr;
}

template<typename T>
inline bool list<T>::operator==(const list& lst) const noexcept
{
    return !(*this != lst);
}

template<typename T>
inline bool list<T>::operator!=(const list& lst) const noexcept
{
    node_ptr node_1 = head;
    node_ptr node_2 = lst.head;

    while (node_1 && node_2 && *node_1 == *node_2)
    {
        node_1 = node_1->next();
        node_2 = node_2->next();
    }

    return node_1 || node_2;
}

template<typename T>
inline list<T> list<T>::operator+(const list::value_type& value) const
{
    list res = *this;
    res.push_back(value);
    return res;
}

template<typename T>
inline list<T> list<T>::operator+(const list& lst) const
{
    list res = *this;
    res.push_back(lst);
    return res;
}

template<typename T>
inline void list<T>::push_front(const value_type& value)
{
    node_ptr new_node = create_new_node(value);
    new_node->insert_end(head);
    head = new_node;
}

template<typename T>
inline void list<T>::push_front(const list& lst)
{
    *this = lst + *this;
}

template<typename T>
inline void list<T>::push_back(const list::value_type& value)
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
inline void list<T>::push_back(const list& lst)
{
    for (const auto& value : lst)
        push_back(value);
}

template<typename T>
inline typename list<T>::iterator list<T>::begin() noexcept
{
    return iterator(head);
}

template<typename T>
inline typename list<T>::iterator list<T>::end() noexcept
{
    return iterator();
}

template<typename T>
inline typename list<T>::const_iterator list<T>::begin() const noexcept
{
    return const_iterator(head);
}

template<typename T>
inline typename list<T>::const_iterator list<T>::end() const noexcept
{
    return const_iterator();
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
