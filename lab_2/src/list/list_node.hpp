#pragma once

#include <memory>

template<typename T>
class list_node
{
public:
    using node_ptr = std::shared_ptr<list_node<T>>;

    list_node() noexcept : _next(nullptr) {}
    list_node(const T& value) noexcept : _data(value), _next(nullptr) {}

    list_node(const list_node& node) noexcept
        : _data(node._data), _next(node._next) {}

    list_node(list_node&& temp) noexcept
        : _data(temp._data), _next(temp._next) { temp._next = nullptr; }

    virtual ~list_node() {}

    operator list_node<const T>() const noexcept { return list_node(_data); }

    list_node& operator=(const list_node& node) noexcept
    {
        _data = node._data;
        _next = node._next;
        return *this;
    }

    T& operator*() noexcept { return _data; }
    T* operator->() noexcept { return &_data; }

    const T& operator*() const noexcept { return _data; }
    const T* operator->() const noexcept { return &_data; }

    node_ptr next() noexcept { return _next; }
    const node_ptr next() const noexcept { return _next; }

    T& data() noexcept { return _data; }
    const T& data() const noexcept { return _data; }

    bool operator==(const list_node& node) const noexcept
    {
        return _data == node._data && _next == node._next;
    }

    bool operator!=(const list_node& node) const noexcept
    {
        return _data != node._data || _next != node._next;
    }

    // inserts given _node as last in chain
    void insert_end(node_ptr node)
    {
        if (!_next)
            _next = node;
        else
        {
            node_ptr it = _next;
            while (it->_next)
                it = it->_next;
            it->_next = node;
        }
    }

private:
    T _data;
    node_ptr _next;
};
