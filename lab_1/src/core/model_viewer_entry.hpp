#pragma once

#include "action.hpp"
#include "model_viewer.hpp"

namespace core
{
    ErrorCode model_viewer(OUT Projection& proj, IN const Action& action);
}
