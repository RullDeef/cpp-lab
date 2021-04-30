#pragma once

#include <initializer_list>
#include "exceptions.hpp"
#include "list_node.hpp"
#include "base_list.hpp"
#include "list_iterator.hpp"
#include "const_list_iterator.hpp"

template<typename T>
class list : public base_list<T>
{
public:
    using value_type = T;
    using node_ptr = typename list_node<value_type>::node_ptr;

    using iterator = list_iterator<value_type>;
    using const_iterator = const_list_iterator<value_type>;

    list() noexcept = default;
    list(const list& lst);
    list(list&& temp) noexcept;

    list(std::initializer_list<value_type> init_list);

    virtual ~list() = default;

    list& operator=(const list& lst);

    bool is_empty() const noexcept override { return !head; }

    size_t size() const noexcept override;
    void clear() noexcept override;

    operator bool() const noexcept { return !is_empty(); }

    template<typename S>
    operator list<S>() const;

    bool operator==(const list& lst) const noexcept;
    bool operator!=(const list& lst) const noexcept;

    list operator+(const value_type& value) const;
    list operator+(const list& lst) const;

    size_t count(const value_type& value) const;
    inline bool contains(const value_type& value) const { return count(value) > 0; }

    void push_front(const value_type& value);
    void push_front(const list& lst);

    void push_back(const value_type& value);
    void push_back(const list& lst);

    value_type& at(size_t index);
    const value_type& at(size_t index) const;

    iterator begin() noexcept;
    iterator end() noexcept;

    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;

    const_iterator cbegin() const noexcept { return begin(); }
    const_iterator cend() const noexcept { return end(); }

protected:
    node_ptr create_new_node(const T& value);

private:
    node_ptr head;
};

#include "list_impl.hpp"
