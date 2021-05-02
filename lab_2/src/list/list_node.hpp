#pragma once

#include "base_list_node.hpp"

template<typename T>
class list_node : public base_list_node
{
public:
    explicit list_node(const T& value);
    explicit list_node(T&& value) noexcept;

    operator list_node<const T>() const noexcept;

    inline T& operator*() noexcept;
    inline T* operator->() noexcept;

    inline const T& operator*() const noexcept;
    inline const T* operator->() const noexcept;

    bool is_empty() const override;

private:
    T _data;
};

#include "list_node_impl.hpp"
