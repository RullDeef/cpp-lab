#pragma once

#include "base_list_node.hpp"

base_list_node::~base_list_node()
{}

// template<typename T>
// base_list_node<T>& base_list_node<T>::operator=(const base_list_node& node) noexcept
// {
//     _data = node._data;
//     _next = node._next;
//     _prev = node._prev;
//     return *this;
// }

typename base_list_node::node_ptr base_list_node::next() const noexcept
{
    return _next;
}

typename base_list_node::node_ptr base_list_node::prev() const noexcept
{
    return _prev.lock();
}

void base_list_node::unlink_next() noexcept
{
    _next = nullptr;
}

void base_list_node::insert_end(node_ptr this_ptr, node_ptr node)
{
    if (auto prev = _prev.lock())
    {
        if (auto old_prev = node->_prev.lock())
        {
            old_prev->_next = this_ptr;
            _prev = old_prev;
        }
        else
        {
            node->_next = this_ptr;
            _prev = node;
        }

        prev->_next = node;
        node->_prev = prev;
    }
    else
    {
        if (auto old_prev = node->_prev.lock())
        {
            old_prev->_next = this_ptr;
            _prev = old_prev;
        }
        else
        {
            node->_next = this_ptr;
            _prev = node;
        }

        _next = node;
        node->_prev = this_ptr;
    }

    // if (!_next)
    //     _next = node;
    // else
    // {
    //     node_ptr it = _next;
    //     while (it->_next)
    //         it = it->_next;
    //     it->_next = node;
    // }
}

bool base_list_node::is_empty() const
{
    return true;
}
