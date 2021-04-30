#pragma once

#include <iterator>
#include "list_node.hpp"
#include "exceptions.hpp"

template<typename T, typename _Base = std::iterator<std::forward_iterator_tag, T>>
class base_list_iterator : public _Base
{
public:
    using value_type = typename _Base::value_type;
    using reference = typename _Base::reference;
    using pointer = typename _Base::pointer;

    using node_ptr = typename list_node<value_type>::node_ptr;

    base_list_iterator() noexcept = default;
    explicit base_list_iterator(const node_ptr& node) noexcept : _node(node) {}

    const reference operator*() const { return node()->data(); }
    const pointer operator->() const { return &node()->data(); }

    inline bool operator==(const base_list_iterator& iter) const noexcept { return _node == iter._node; }
    inline bool operator!=(const base_list_iterator& iter) const noexcept { return _node != iter._node; }

    base_list_iterator& operator++()
    {
        _check_node_ptr();
        _node = _node->next();
        return *this;
    }

    base_list_iterator operator++(int)
    {
        base_list_iterator temp = *this;
        ++*this;
        return temp;
    }

protected:
    inline void _check_node_ptr() const
    {
        if (!_node) throw invalid_state_iterator_exception(__FILE__, typeid(*this).name(), __LINE__);
    }

    inline node_ptr& node() { _check_node_ptr(); return _node; }
    inline const node_ptr& node() const { _check_node_ptr(); return _node; }

    node_ptr _node = nullptr;
};
