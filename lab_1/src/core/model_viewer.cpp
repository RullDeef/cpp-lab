#include <cstdio>
#include <cstdlib>
#include <memory>
#include "model_viewer.hpp"

using namespace core;

ErrorCode core::model_viewer(OUT const ProjectedModel** projmod, IN const Action& action)
{
    static Model m_model = model_init();
    static ProjectedModel m_projmod = projmod_init();
    static View m_view = view_init();

    static bool initialized = false;
    static bool model_loaded = false;
    static bool proj_need_recalc = false;

    ErrorCode status = ErrorCode::success;

    switch (action.type)
    {
    case ActionType::Init:
        model_destroy(m_model);
        projmod_destroy(m_projmod);
        m_view = view_init(action.viewport);
        proj_need_recalc = false;
        model_loaded = false;
        initialized = true;
        break;

    case ActionType::Destroy:
        model_destroy(m_model);
        projmod_destroy(m_projmod);
        initialized = false;
        break;

    case ActionType::Load:
        if (model_loaded)
        {
            model_destroy(m_model);
            projmod_destroy(m_projmod);
        }
        status = model_load(m_model, action.filename);
        view_reset(m_view);
        proj_need_recalc = true;
        model_loaded = true;
        break;

    case ActionType::Save:
        if (!initialized)
            status = ErrorCode::view_not_initialized;
        else if (!model_loaded)
            status = ErrorCode::model_not_loaded;
        else
            status = model_save_transformed(m_model, action.filename, m_view.view_mat);
        break;

    case ActionType::RecomputeProjection:
        if (!initialized)
            status = ErrorCode::view_not_initialized;
        else if (projmod == nullptr)
            status = ErrorCode::invalid_projection_ptr;
        else if (proj_need_recalc)
            status = projmod_project(m_projmod, m_model, m_view);

        if (status == ErrorCode::success)
        {
            proj_need_recalc = false;
            *projmod = &m_projmod;
        }
        break;

    case ActionType::Translate:
        status = view_translate(m_view, action.dx, action.dy);
        proj_need_recalc = true;
        break;

    case ActionType::Rotate:
        status = view_rotate(m_view, action.dx, action.dy);
        proj_need_recalc = true;
        break;

    case ActionType::Scale:
        status = view_scale(m_view, action.factor);
        proj_need_recalc = true;
        break;

    default:
        status = ErrorCode::unknown_action;
        break;
    }

    return status;
}
