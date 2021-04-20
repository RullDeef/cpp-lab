#pragma once

#include <initializer_list>

#include "base_list.hpp"
#include "exceptions.hpp"

#include <list>

#include "list_node.hpp"
#include "list_iterator.hpp"

template<typename T>
class list : public base_list<T>
{
public:
    using node_ptr = typename list_node<T>::node_ptr;

    using iterator = base_list_iterator<T>;
    using const_iterator = base_list_iterator<const T>;

    list() noexcept = default;
    list(const list& lst);
    list(list&& temp) noexcept;

    bool is_empty() const noexcept override { return !head; }

    size_t size() const noexcept override;
    void clear() noexcept override;

    list(std::initializer_list<T> init_list);

    void push_back(const T& value);

    iterator begin() noexcept;
    iterator end() noexcept;

    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;

    const_iterator cbegin() const noexcept { return begin(); }
    const_iterator cend() const noexcept { return end(); }

private:
    node_ptr create_new_node(const T& value);

    node_ptr head;
};

#include "list_impl.hpp"
