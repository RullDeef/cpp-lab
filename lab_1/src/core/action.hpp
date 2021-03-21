#pragma once

#include "ext_math.hpp"

namespace core
{
    enum class ActionType
    {
        Init,                // initializes viewport
        Destroy,             // releases model resources
        Load,                // load model from file
        Save,                // saves model to file
        RecomputeProjection, // updates projection, if needed
        Translate,           // translate model
        Rotate,              // rotate model
        Scale                // scale model
    };

    struct Action
    {
        ActionType type;
        union
        {
            struct
            {
                double dx;
                double dy;
            };
            double factor;
            viewport viewport;
            const char* filename;
        };
    };
}
