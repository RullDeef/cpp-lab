#include "model_viewer.hpp"


ErrorCode do_init(OUT View& view, IN viewport viewport)
{
    view = view_init(viewport);

    return ErrorCode::success;
}

ErrorCode do_destroy(VAR Model& model, VAR Projection& proj)
{
    model_destroy(model);
    proj_destroy(proj);

    return ErrorCode::success;
}

ErrorCode do_load(VAR Model& model, IN const char* filename)
{
    Model copy = model_init();
    ErrorCode status = model_load(copy, filename);

    if (status == ErrorCode::success)
    {
        model_destroy(model);
        model_clone(model, copy);
    }

    return status;
}

ErrorCode do_save(IN const Model& model, IN const View& view, IN const char* filename)
{
    Model copy;

    ErrorCode status = model_clone(copy, model);
    if (status == ErrorCode::success)
    {
        status = model_transform(copy, view.model_tf);
        if (status == ErrorCode::success)
            status = model_save(copy, filename);

        model_destroy(copy);
    }

    return status;
}

ErrorCode do_project(OUT Projection& proj, IN const Model& model, IN const View& view)
{
    return proj_update(proj, model, view);
}
