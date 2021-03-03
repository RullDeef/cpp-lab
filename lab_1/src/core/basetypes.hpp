#pragma once

namespace core
{
    using real = double;
    using integer = int;
    using index = unsigned int;

    using angle = double;

    struct vec
    {
        real x;
        real y;
        real z;
    };

    struct mat
    {
        real data[16];
    };

    struct edge
    {
        index p1;
        index p2;
    };

    struct screen_point
    {
        integer x;
        integer y;
    };

    struct section
    {
        screen_point p1;
        screen_point p2;
    };

    struct viewport
    {
        integer left;
        integer top;
        integer width;
        integer height;
    };

    enum class ErrorCode
    {
        success,
        unknown_action,
        invalid_viewport,
        invalid_model,
        invalid_projection,
        invalid_file_name,
        cannot_open_file,
        cannot_write_file,
        invalid_file,
        bad_malloc
    };
}
