#pragma once


class base_list
{
public:
    virtual ~base_list() = default;

    virtual size_t size() const noexcept = 0;
    virtual bool is_empty() const noexcept = 0;

    virtual void clear() noexcept = 0;
};
