#pragma once

#include <memory>

class base_list_node
{
public:
    using node_ptr = std::shared_ptr<base_list_node>;
    using wnode_ptr = std::weak_ptr<base_list_node>;

    base_list_node() noexcept = default;
    base_list_node(const base_list_node& node) = delete;

    virtual ~base_list_node();

    base_list_node& operator=(const base_list_node& node) noexcept = delete;

    node_ptr next() const noexcept;
    node_ptr prev() const noexcept;

    void unlink_next() noexcept;
    void insert_end(node_ptr this_ptr, node_ptr node);
    node_ptr remove_this(node_ptr this_ptr); // removes *this node from chain connecting prev with next

    virtual bool is_empty() const noexcept;

private:
    node_ptr _next;
    wnode_ptr _prev;
};
