#pragma once

#include <cstdlib>
#include "list.hpp"

template<typename T>
template<typename U>
list<T>::list(const list<U>& lst)
{
    for (const auto& value : lst)
        push_back(T(value));
}

template<typename T>
list<T>::list(const list& lst)
{
    for (const auto& value : lst)
        push_back(value);
}

template<typename T>
inline list<T>::list(list&& temp) noexcept
{
    head.swap(temp.head);
}

template<typename T>
inline list<T>::list(std::initializer_list<T> init_list)
{
    for (const auto& value : init_list)
        push_back(value);
}

template<typename T>
template<typename... Args>
list<T>::list(const T& first, const T& second, const Args&... other)
    : list(other...)
{
    push_front(second);
    push_front(first);
}

template<typename T>
list<T>::list(const T& first, const T& second)
{
    push_front(second);
    push_front(first);
}

template<typename T>
list<T>::list(const T& value)
{
    push_front(value);
}

template<typename T>
list<T>::list(T* array, size_t size)
{
    if (!array && size != 0)
        throw invalid_rawptr_list_exception(__FILE__, typeid(*this).name(), __LINE__);
    else if (!array && size == 0)
        return;

    for (size_t i = 0; i < size; i++)
        push_back(array[i]);
    free(array);
}

template<typename T>
template<typename _Iter>
list<T>::list(_Iter begin, _Iter end)
{
    for (_Iter iter = begin; iter != end; ++iter)
        push_back(*iter);
}

template<typename T>
list<T>::~list()
{
    clear();
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
    head.swap(lst.head);
    return *this;
}

template<typename T>
size_t list<T>::size() const noexcept
{
    size_t size = 0;
    for (const auto& item : *this)
        size++;
    return size;
}

template<typename T>
bool list<T>::is_empty() const noexcept
{
    return !(head->next());
}

template<typename T>
inline void list<T>::clear() noexcept
{
    head->unlink_next();
}

template<typename T>
list<T>::operator bool() const noexcept
{
    return bool(head->next());
}

template<typename T>
template<typename U>
inline bool list<T>::operator==(const list<U>& lst) const noexcept
{
    return !(*this != lst);
}

template<typename T>
template<typename U>
bool list<T>::operator!=(const list<U>& lst) const noexcept
{
    auto iter_1 = begin();
    auto iter_2 = lst.begin();

    while (iter_1 != end() && iter_2 != lst.end() && *iter_1 == *iter_2)
        ++iter_1, ++iter_2;

    return iter_1 != end() || iter_2 != lst.end();
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
    if (!(head->next()))
        head->insert_end(head, create_new_node(value));
    else
    {
        node_ptr new_node = create_new_node(value);
        head->next()->insert_end(head->next(), new_node);
    }
}

template<typename T>
inline void list<T>::push_front(const list& lst)
{
    *this = lst + *this;
}

template<typename T>
inline void list<T>::push_back(const T& value)
{
    head->insert_end(head, create_new_node(value));
}

template<typename T>
inline void list<T>::push_back(const list& lst)
{
    for (const auto& value : lst)
        push_back(value);
}

template<typename T>
typename list<T>::iterator list<T>::insert(const_iterator pos, const T& value)
{
    if (begin() == end() && (pos == begin() || pos == end()))
    {
        push_front(value);
        return begin();
    }
    else if (pos == begin())
    {
        push_front(value);
        return ++begin();
    }
    else
    {
        node_ptr new_node = create_new_node(value);
        node_ptr node = pos.node();

        node->insert_end(node, new_node);
        return iterator(new_node);

        // node_ptr node = head;
        // while (node->next() && node->next() != pos.node())
        //     node = node->next();
        // 
        // new_node->insert_end(node->next());
        // node->next() = new_node;
        // return iterator(node->next());
    }
}

template<typename T>
typename list<T>::iterator list<T>::insert(const_iterator pos, T&& value)
{
    if (pos == begin() || begin() == end())
    {
        push_front(value);
        return begin();
    }

    node_ptr new_node = create_new_node(value);
    pos.node()->insert_end(pos.node(), new_node);
    return iterator(new_node);

    // node_ptr new_node = create_new_node(value);
    // 
    // node_ptr node = head;
    // while (node->next() && node->next() != pos.node())
    //     node = node->next();
    // 
    // new_node->insert_end(node->next());
    // node->next() = new_node;
    // return iterator(new_node);
}

template<typename T>
typename list<T>::iterator list<T>::insert(const_iterator pos, size_t count, const T& value)
{
    if (count == 0)
        return iterator(pos.node());

    if (pos == begin() || begin() == end())
    {
        while (count-- > 0)
            push_front(value);
        return begin();
    }

    node_ptr new_node = create_new_node(value);
    while (--count > 0)
        new_node->insert_end(new_node, create_new_node(value));

    pos.node()->insert_end(pos.node(), new_node);
    return iterator(new_node);
}

template<typename T>
template<typename InputIt>
typename list<T>::iterator list<T>::insert(const_iterator pos, InputIt first, InputIt last)
{
    if (first == last)
    {
        iterator res = begin();
        while (res != pos) ++res;
        return res;
    }
    else
    {
        iterator res = insert(pos, *first);
        pos = res;

        while (++first != last)
            pos = insert(++pos, *first);

        return res;
    }
}

template<typename T>
typename list<T>::iterator list<T>::insert(const_iterator pos, std::initializer_list<T> ilist)
{
    return insert(pos, ilist.begin(), ilist.end());
}

template<typename T>
list<T> list<T>::sublist(const_iterator first, const_iterator last)
{

}

template<typename T>
list<T> list<T>::sublist(const_iterator pos, size_t count)
{
    if (count == 0)
        return list();

    const_iterator last = pos;
    while (count-- > 0) ++last;
    return sublist(pos, last);
}

template<typename T>
T& list<T>::at(size_t index)
{
    if (index >= size())
        throw out_of_bounds_list_exception(__FILE__, typeid(*this).name(), __LINE__);

    node_ptr node = head->next();
    for (size_t i = 0; i < index; i++)
        node = node->next();
    return **static_cast<list_node<T>*>(node.get());
}

template<typename T>
const T& list<T>::at(size_t index) const
{
    if (index >= size())
        throw out_of_bounds_list_exception(__FILE__, typeid(*this).name(), __LINE__);

    node_ptr node = head->next();
    for (size_t i = 0; i < index; i++)
        node = node->next();
    return **static_cast<list_node<T>*>(node.get());
}

template<typename T>
inline T& list<T>::front()
{
    if (auto first = head->next())
        return **static_cast<list_node<T>*>(first.get());
    throw out_of_bounds_list_exception(__FILE__, typeid(*this).name(), __LINE__);
}

template<typename T>
inline const T& list<T>::front() const
{
    if (auto first = head->next())
        return **static_cast<list_node<const T>*>(first.get());
    throw out_of_bounds_list_exception(__FILE__, typeid(*this).name(), __LINE__);
}

template<typename T>
inline T& list<T>::back()
{
    if (auto last = head->prev())
        return **static_cast<list_node<T>*>(last.get());
    else
        throw out_of_bounds_list_exception(__FILE__, typeid(*this).name(), __LINE__);
}

template<typename T>
inline const T& list<T>::back() const
{
    if (auto last = head->prev())
        return **static_cast<list_node<const T>*>(last.get());
    else
        throw out_of_bounds_list_exception(__FILE__, typeid(*this).name(), __LINE__);
}

template<typename T>
inline typename list<T>::iterator list<T>::begin() noexcept
{
    if (head->next())
        return iterator(head->next());
    return iterator(head);
}

template<typename T>
inline typename list<T>::iterator list<T>::end() noexcept
{
    return iterator(head);
}

template<typename T>
inline typename list<T>::const_iterator list<T>::begin() const noexcept
{
    if (head->next())
        return iterator(head->next());
    return iterator(head);
}

template<typename T>
inline typename list<T>::const_iterator list<T>::end() const noexcept
{
    return const_iterator(head);
}

template<typename T>
inline typename list<T>::const_iterator list<T>::cbegin() const noexcept
{
    if (head->next())
        return iterator(head->next());
    return iterator(head);
}

template<typename T>
inline typename list<T>::const_iterator list<T>::cend() const noexcept
{
    return const_iterator(head);
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

template<typename T>
typename list<T>::node_ptr list<T>::create_new_node(T&& value)
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
