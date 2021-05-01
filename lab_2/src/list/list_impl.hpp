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
    : head(std::move(temp.head))
{}

template<typename T>
inline list<T>::list(std::initializer_list<T> init_list)
{
    for (const auto& value : init_list)
        push_back(value);
}

template<typename T>
template<typename _Iter>
list<T>::list(_Iter begin, _Iter end)
{
    for (_Iter iter = begin; iter != end; ++iter)
        push_back(*iter);
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
list<T>& list<T>::operator=(list<T>&& lst) noexcept
{
    clear();
    head = std::move(lst.head);
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
bool list<T>::is_empty() const noexcept
{
    return !head;
}

template<typename T>
inline void list<T>::clear() noexcept
{
    head = nullptr;
}

template<typename T>
list<T>::operator bool() const noexcept
{
    return bool(head);
}

template<typename T>
template<typename S>
inline list<T>::operator list<S>() const
{
    list<S> result;
    for (const auto& value : *this)
        result.push_back(S(value));
    return result;
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
template<typename U>
auto list<T>::operator+(const list<U>& lst) const -> decltype(list<decltype(T() + U())>())
{
    list<decltype(T() + U())> res = *this;
    res.push_back(lst);
    return res;
}

template<typename T>
list<T> list<T>::operator+(const T& value) const
{
    list res = *this;
    res.push_back(value);
    return res;
}

template<typename T>
template<typename U>
list<T>& list<T>::operator+=(const list<U>& lst)
{
    for (const auto& value : lst)
        push_back(static_cast<T>(value));
    return *this;
}

template<typename T>
list<T>& list<T>::operator+=(const T& value)
{
    push_back(value);
    return *this;
}

template<typename T>
size_t list<T>::count(const T& value) const
{
    size_t amount = 0;
    for (const auto& item : *this)
        if (item == value)
            amount++;
    return amount;
}

template<typename T>
bool list<T>::contains(const T& value) const
{
    for (const auto& item : *this)
        if (item == value)
            return true;
    return false;
}

template<typename T>
inline void list<T>::push_front(const T& value)
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
inline void list<T>::push_back(const list& lst)
{
    for (const auto& value : lst)
        push_back(value);
}

template<typename T>
T& list<T>::at(size_t index)
{
    node_ptr node = head;
    for (size_t i = 0; i < index; i++)
        node = node->next();
    return node->data();
}

template<typename T>
const T& list<T>::at(size_t index) const
{
    node_ptr node = head;
    for (size_t i = 0; i < index; i++)
        node = node->next();
    return node->data();
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
inline typename list<T>::const_iterator list<T>::cbegin() const noexcept
{
    return const_iterator(head);
}

template<typename T>
inline typename list<T>::const_iterator list<T>::cend() const noexcept
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

template<typename T, typename U>
auto operator+(const U& value, const list<T>& lst) -> decltype(list<decltype(U() + T())>())
{
    decltype(list<decltype(U() + T())>()) res = lst;
    res.push_front(value);
    return res;
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, const list<T>& lst)
{
    stream << "{";

    int i = 0;
    for (const auto& value : lst)
    {
        if (i++ > 0) stream << ", ";
        stream << value;
    }

    return stream << "}";
}
