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
    using node_ptr = typename base_list_node::node_ptr;

    using iterator = list_iterator<T>;
    using const_iterator = const_list_iterator<T>;

    list() = default;

    template<typename U>
    list(const list<U>& lst);
    list(const list& lst);

    list(list&& temp) noexcept;

    list(std::initializer_list<T> init_list);

    template<typename... Args>
    list(const T& first, const T& second, const Args&... other);
    list(const T& first, const T& second);
    explicit list(const T& value);

    template<typename _Iter>
    list(_Iter begin, _Iter end);

    list(T* array, size_t size); // steals C-array

    virtual ~list();

    list& operator=(const list& lst);
    list& operator=(list&& lst) noexcept;

    size_t size() const noexcept override;
    bool is_empty() const noexcept override;

    void clear() noexcept override;

    operator bool() const noexcept;

    template<typename U>
    bool operator==(const list<U>& lst) const noexcept;

    template<typename U>
    bool operator!=(const list<U>& lst) const noexcept;

    template<typename U>
    auto operator+(const list<U>& lst) const -> decltype(list<decltype(T() + U())>());
    list operator+(const T& value) const;

    template<typename U>
    list& operator+=(const list<U>& lst);
    list& operator+=(const T& value);

    size_t count(const T& value) const;
    bool contains(const T& value) const;

    void push_front(const T& value);
    void push_front(const list& lst);

    void push_back(const T& value);
    void push_back(const list& lst);

    iterator insert(const_iterator pos, const T& value);
    iterator insert(const_iterator pos, T&& value);
    iterator insert(const_iterator pos, size_t count, const T& value);
    template<typename InputIt>
    iterator insert(const_iterator pos, InputIt first, InputIt last);
    iterator insert(const_iterator pos, std::initializer_list<T> ilist);

    iterator erase(const_iterator pos);
    iterator erase(const_iterator first, const_iterator last);

    list sublist(const_iterator first, const_iterator last);
    list sublist(const_iterator pos, size_t count);

    T& at(size_t index);
    const T& at(size_t index) const;

    inline T& front();
    inline const T& front() const;

    inline T& back();
    inline const T& back() const;

    inline iterator begin() noexcept;
    inline iterator end() noexcept;

    inline const_iterator begin() const noexcept;
    inline const_iterator end() const noexcept;

    inline const_iterator cbegin() const noexcept;
    inline const_iterator cend() const noexcept;

private:
    node_ptr create_new_node(const T& value);
    node_ptr create_new_node(T&& value);

    node_ptr head = std::make_shared<base_list_node>();
};

template<typename T, typename U>
auto operator+(const U& value, const list<T>& lst) -> decltype(list<decltype(U() + T())>());

template<typename T>
std::ostream& operator<<(std::ostream& stream, const list<T>& lst);

#include "list_impl.hpp"
