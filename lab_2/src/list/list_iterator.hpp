#pragma once

#include "const_list_iterator.hpp"

template<typename T>
class list_iterator : public const_list_iterator<T>
{
public:
    list_iterator() noexcept = default;
    list_iterator(const list_iterator& iter) noexcept;
    list_iterator(list_iterator&& iter) noexcept;

    explicit list_iterator(const std::shared_ptr<list_node<T>>& node) noexcept;

    T& operator*();
    T* operator->();

    list_iterator& operator++();
    list_iterator operator++(int);

protected:
    using const_list_iterator<T>::_node;
};

#include "list_iterator_impl.hpp"
