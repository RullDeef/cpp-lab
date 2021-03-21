#pragma once

#include "sal.hpp"
#include "error_code.hpp"
#include "ext_math.hpp"
#include "action.hpp"

#include "model.hpp"
#include "projectedmodel.hpp"
#include "view.hpp"

namespace core
{
    // точка входа в прикладном домене
    ErrorCode model_viewer(OUT const ProjectedModel** projmod, IN const Action& action);
}
