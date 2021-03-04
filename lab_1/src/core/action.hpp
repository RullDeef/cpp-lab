#pragma once

#include "ext_math.hpp"

namespace core
{
    enum class ActionType
    {
        Init,       // initializes viewport
        Translate,  // translate model
        Rotate,     // rotate model
        Scale,      // scale model
        Load,       // load model from file
        Save,       // saves model to file
        Destroy     // releases model resources
    };

    struct TranslateAction
    {
        double dx;
        double dy;
    };

    struct RotateAction
    {
        double dx;
        double dy;
    };

    struct ScaleAction
    {
        double factor;
    };

    struct Action
    {
        ActionType type;
        union
        {
            viewport viewport;
            TranslateAction translate;
            RotateAction rotate;
            ScaleAction scale;
            const char* filename;
        };
    };
}
