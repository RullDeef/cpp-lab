#pragma once

#include <iterator>
#include "list_node.hpp"
#include "exceptions.hpp"
#include "list_iterator.hpp"

template<typename T>
class list;

template<typename T>
class const_list_iterator : public std::iterator<std::bidirectional_iterator_tag, T>
{
public:
    const_list_iterator(const const_list_iterator& iter) noexcept;
    const_list_iterator(const_list_iterator&& iter) noexcept;

    explicit const_list_iterator(typename const base_list_node::node_ptr& node) noexcept;

    const_list_iterator& operator=(const const_list_iterator& iter);

    const T& operator*() const;
    const T* operator->() const;
    operator bool() const noexcept;

    inline bool operator==(const const_list_iterator& iter) const;
    inline bool operator!=(const const_list_iterator& iter) const;

    const_list_iterator& operator++();
    const_list_iterator operator++(int);

    const_list_iterator& operator--();
    const_list_iterator operator--(int);

    friend typename list<T>::iterator list<T>::insert(typename list<T>::const_iterator pos, const T& value);
    friend typename list<T>::iterator list<T>::erase(typename list<T>::const_iterator pos);
    friend typename list<T>::iterator list<T>::erase(typename list<T>::const_iterator first, typename list<T>::const_iterator last);

protected:
    typename base_list_node::node_ptr node();

    base_list_node::wnode_ptr _node;
};

#include "const_list_iterator_impl.hpp"
