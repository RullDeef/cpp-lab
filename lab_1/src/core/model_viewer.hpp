#pragma once

#include "sal.hpp"
#include "error_code.hpp"
#include "action.hpp"
#include "projectedmodel.hpp"

namespace core
{
    // ����� ����� � ���������� ������
    ErrorCode model_viewer(OUT ProjectedModel& projmod, IN const Action& action);
}
