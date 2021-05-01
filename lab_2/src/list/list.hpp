#pragma once

#include <iostream>
#include <initializer_list>
#include "exceptions.hpp"
#include "list_node.hpp"
#include "base_list.hpp"
#include "list_iterator.hpp"
#include "const_list_iterator.hpp"

template<typename T>
class list : public base_list
{
public:
    using node_ptr = typename list_node<T>::node_ptr;

    using iterator = list_iterator<T>;
    using const_iterator = const_list_iterator<T>;

    list() noexcept = default;
    list(const list& lst);
    list(list&& temp) noexcept;

    list(std::initializer_list<T> init_list);

    // list(T* array, size_t size) // from C-array
    // list s peremennim chislom parametrov

    template<typename _Iter>
    list(_Iter begin, _Iter end);

    virtual ~list() = default;

    list& operator=(const list& lst);
    list& operator=(list&& lst) noexcept;

    size_t size() const noexcept override;
    bool is_empty() const noexcept override;

    void clear() noexcept override;

    operator bool() const noexcept;

    template<typename S>
    operator list<S>() const;

    bool operator==(const list& lst) const noexcept;
    bool operator!=(const list& lst) const noexcept;

    template<typename U = T>
    auto operator+(const list<U>& lst) const -> decltype(list<decltype(T() + U())>());
    list operator+(const T& value) const;

    template<typename U = T>
    list& operator+=(const list<U>& lst);
    list& operator+=(const T& value);

    size_t count(const T& value) const;
    bool contains(const T& value) const;

    void push_front(const T& value);
    void push_front(const list& lst);

    void push_back(const T& value);
    void push_back(const list& lst);

    // emplace_front(...)
    // emplace_back(...)

    // sublist(...)

    T& at(size_t index);
    const T& at(size_t index) const;

    inline iterator begin() noexcept;
    inline iterator end() noexcept;

    inline const_iterator begin() const noexcept;
    inline const_iterator end() const noexcept;

    inline const_iterator cbegin() const noexcept;
    inline const_iterator cend() const noexcept;

private:
    node_ptr create_new_node(const T& value);

    node_ptr head;
};

template<typename T, typename U = T>
auto operator+(const U& value, const list<T>& lst) -> decltype(list<decltype(U() + T())>());

template<typename T>
std::ostream& operator<<(std::ostream& stream, const list<T>& lst);

#include "list_impl.hpp"
