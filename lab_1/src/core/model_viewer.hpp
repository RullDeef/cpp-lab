#pragma once

#include "error_code.hpp"
#include "context.hpp"
#include "action.hpp"

namespace core
{
    // ����� ����� � ���������� ������
    ErrorCode model_viewer(Context& context, const Action& action);

    // ������ ���������� ��������
    ErrorCode do_translation(mat& view, const TranslateAction& action);
    ErrorCode do_rotation(mat& view, const RotateAction& action);
    ErrorCode do_scale(mat& view, const ScaleAction& action);

    /**
     * @brief ��������� ������ �� �����
     * 
     * @param model ������ (��������������������)
     * @param filename ��� �������� �����
     */
    ErrorCode do_load(Model& model, const char* filename);
    ErrorCode do_save(const Model& model, mat view, const char* filename);

    ErrorCode do_init(Context& context, viewport viewport);
    ErrorCode do_destroy(Context& context);
}
