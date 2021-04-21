#pragma once

#include <cstddef>
#include "list_node.hpp"

#include "exceptions.hpp"

// forward declaration
template<typename T, typename _Base = std::iterator<std::forward_iterator_tag, T>>
class base_list_iterator;

template<typename T>
using list_iterator = base_list_iterator<T>;

template<typename T>
using const_list_iterator = base_list_iterator<const T>;

template<typename T, typename _Base>
class base_list_iterator : public _Base
{
public:
    using value_type = typename _Base::value_type;
    using reference = typename _Base::reference;
    using pointer = typename _Base::pointer;

    using node_ptr = typename list_node<value_type>::node_ptr;

    base_list_iterator() noexcept = default;

    explicit base_list_iterator(const node_ptr& ptr) noexcept : _node(ptr) {}

    base_list_iterator(const base_list_iterator& iter) noexcept : _node(iter._node) {}
    base_list_iterator(base_list_iterator&& iter) noexcept : _node(iter._node) {}

    reference operator*() { return _node->data(); }
    pointer operator->() { return &_node->data(); }

    bool operator==(const base_list_iterator& iter) const { return _node == iter._node; }
    bool operator!=(const base_list_iterator& iter) const { return _node != iter._node; }

    base_list_iterator& operator++()
    {
        if (!_node) throw invalid_state_iterator_exception(__FILE__, typeid(*this).name(), __LINE__);
        _node = _node->next();
        return *this;
    }

    base_list_iterator operator++(int) { base_list_iterator temp = *this; ++*this; return temp; }

    node_ptr& node() { return _node; }
    const node_ptr& node() const { return _node; }

private:
    node_ptr _node;
};


