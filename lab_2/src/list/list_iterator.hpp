#pragma once

#include "const_list_iterator.hpp"

template<typename T>
class list_iterator : public const_list_iterator<T>
{
public:
    list_iterator(const list_iterator& iter) noexcept;
    list_iterator(list_iterator&& iter) noexcept;

    explicit list_iterator(typename const base_list_node::node_ptr& node) noexcept;

    list_iterator& operator=(const list_iterator& iter);

    T& operator*();
    T* operator->();

    list_iterator& operator++();
    list_iterator operator++(int);

    list_iterator& operator--();
    list_iterator operator--(int);

protected:
    using const_list_iterator<T>::_node;
};

#include "list_iterator_impl.hpp"
