#pragma once

template<typename T>
class base_list
{
public:
    using value_type = T;

    virtual ~base_list() = default;

    virtual bool is_empty() const noexcept = 0;
    virtual size_t size() const noexcept = 0;

    virtual void clear() noexcept = 0;
};
