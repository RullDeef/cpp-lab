#include "model_viewer_entry.hpp"

using namespace core;

ErrorCode core::model_viewer(OUT Projection& proj, IN const Action& action)
{
    static Model m_model = model_init();
    static View m_view = view_init();

    ErrorCode status;

    switch (action.type)
    {
    case ActionType::Init:
        status = do_init(m_view, action.viewport);
        break;

    case ActionType::Destroy:
        status = do_destroy(m_model, proj);
        break;

    case ActionType::Load:
        status = do_load(m_model, action.filename);
        break;

    case ActionType::Save:
        status = do_save(m_model, m_view, action.filename);
        break;

    case ActionType::ComputeProjection:
        status = do_project(proj, m_model, m_view);
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
