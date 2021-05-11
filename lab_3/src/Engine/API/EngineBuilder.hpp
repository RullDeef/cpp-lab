#pragma once

#include "Engine.hpp"

class EngineBuilder
{
public:
    Engine&& build();

    EngineBuilder& useRenderer();
};
