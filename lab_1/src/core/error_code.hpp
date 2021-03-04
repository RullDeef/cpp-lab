#pragma once

namespace core
{
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
