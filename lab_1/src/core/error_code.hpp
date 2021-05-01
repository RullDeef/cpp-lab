#pragma once

enum class ErrorCode
{
    success,
    unknown_action,
    invalid_viewport,
    invalid_view,
    invalid_model,
    invalid_projection,
    invalid_projection_ptr,
    invalid_file_name,
    cannot_open_file,
    cannot_write_file,
    invalid_file,
    bad_malloc,
    model_not_loaded,
    view_not_initialized,
    invalid_vert_array,
    invalid_edge_array,
    invalid_rotation_axis,
    invalid_scale_factor
};
