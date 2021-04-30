#pragma once

#include "base_list_iterator.hpp"

template<typename T, typename _Base = base_list_iterator<T>>
class const_list_iterator : public _Base
{
public:
    using value_type = typename _Base::value_type;
    using reference = typename _Base::reference;
    using pointer = typename _Base::pointer;

    using node_ptr = typename _Base::node_ptr;

    const_list_iterator() noexcept = default;
    explicit const_list_iterator(const node_ptr& node) noexcept : _Base(node) {}
};
