#include "model.hpp"
#include "view.hpp"
#include "model_viewer.hpp"

using namespace core;

ErrorCode do_init(OUT View& view, VAR Model& model, VAR ProjectedModel& projmod, IN viewport viewport);
ErrorCode do_destroy(VAR Model& model, VAR ProjectedModel& projmod);

ErrorCode do_load(OUT View& view, VAR Model& model, VAR ProjectedModel& projmod, IN const char* filename);
ErrorCode do_save(IN const Model& model, IN const View& view, IN const char* filename);

ErrorCode do_recompute_projection(OUT ProjectedModel& projmod_ptr, VAR ProjectedModel& projmod, IN const Model& model, IN const View& view);

ErrorCode core::model_viewer(OUT ProjectedModel& projmod, IN const Action& action)
{
    static Model m_model = model_init();
    static ProjectedModel m_projmod = projmod_init();
    static View m_view = view_init();

    ErrorCode status;

    switch (action.type)
    {
    case ActionType::Init:
        status = do_init(m_view, m_model, m_projmod, action.viewport);
        break;

    case ActionType::Destroy:
        status = do_destroy(m_model, m_projmod);
        break;

    case ActionType::Load:
        status = do_load(m_view, m_model, m_projmod, action.filename);
        break;

    case ActionType::Save:
        status = do_save(m_model, m_view, action.filename);
        break;

    case ActionType::RecomputeProjection:
        status = do_recompute_projection(projmod, m_projmod, m_model, m_view);
        break;

    case ActionType::Translate:
        status = view_translate(m_view, action.dx, action.dy);
        break;

    case ActionType::Rotate:
        status = view_rotate(m_view, action.dx, action.dy);
        break;

    case ActionType::Scale:
        status = view_scale(m_view, action.factor);
        break;

    default:
        status = ErrorCode::unknown_action;
        break;
    }

    return status;
}

ErrorCode do_init(OUT View& view, VAR Model& model, VAR ProjectedModel& projmod, IN viewport viewport)
{
    model_destroy(model);
    projmod_destroy(projmod);
    view = view_init(viewport);

    return ErrorCode::success;
}

ErrorCode do_destroy(VAR Model& model, VAR ProjectedModel& projmod)
{
    model_destroy(model);
    projmod_destroy(projmod);

    return ErrorCode::success;
}

ErrorCode do_load(OUT View& view, VAR Model& model, VAR ProjectedModel& projmod, IN const char* filename)
{
    Model copy;
    ErrorCode status = model_load(copy, filename);

    if (status == ErrorCode::success)
    {
        model_destroy(model);
        model_clone(model, copy);

        projmod_destroy(projmod);
        view_reset(view);
    }

    return status;
}

ErrorCode do_save(IN const Model& model, IN const View& view, IN const char* filename)
{
    Model copy;

    ErrorCode status = model_clone(copy, model);
    if (status == ErrorCode::success)
    {
        status = model_transform(copy, view.view_mat);
        if (status == ErrorCode::success)
            status = model_save(copy, filename);

        model_destroy(copy);
    }

    return status;
}

ErrorCode do_recompute_projection(OUT ProjectedModel& projmod_ptr, VAR ProjectedModel& projmod, IN const Model& model, IN const View& view)
{
    ErrorCode status = projmod_project(projmod, model, view);

    if (status == ErrorCode::success)
        projmod_ptr = projmod;

    return status;
}
