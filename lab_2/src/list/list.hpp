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
    using value_type = T;
    using node_ptr = typename list_node<value_type>::node_ptr;

    using iterator = base_list_iterator<value_type>;
    using const_iterator = base_list_iterator<value_type>;

    list() noexcept = default;
    list(const list& lst);
    list(list&& temp) noexcept;

    list(std::initializer_list<value_type> init_list);

    list& operator=(const list& lst);

    bool is_empty() const noexcept override { return !head; }

    size_t size() const noexcept override;
    void clear() noexcept override;

    operator bool() const noexcept { return !is_empty(); }

    bool operator==(const list& lst) const noexcept;
    bool operator!=(const list& lst) const noexcept;

    list operator+(const value_type& value) const;
    list operator+(const list& lst) const;

    void push_front(const value_type& value);
    void push_front(const list& lst);

    void push_back(const value_type& value);
    void push_back(const list& lst);

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
