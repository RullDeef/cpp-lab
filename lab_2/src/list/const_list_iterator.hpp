#pragma once

#include <iterator>
#include "list_node.hpp"
#include "exceptions.hpp"
#include "list_iterator.hpp"

template<typename T>
class const_list_iterator : public std::iterator<std::forward_iterator_tag, T>
{
public:
    const_list_iterator() noexcept = default;
    const_list_iterator(const const_list_iterator& iter) noexcept;
    const_list_iterator(const_list_iterator&& iter) noexcept;

    explicit const_list_iterator(const std::shared_ptr<list_node<T>>& node) noexcept;

    const T& operator*() const;
    const T* operator->() const;

    operator bool() const noexcept;

    inline bool operator==(const const_list_iterator& iter) const;
    inline bool operator!=(const const_list_iterator& iter) const;

    const_list_iterator& operator++();
    const_list_iterator operator++(int);

protected:
    std::weak_ptr<list_node<T>> _node;
};

#include "const_list_iterator_impl.hpp"
