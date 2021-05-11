#pragma once

#include "../HullModel.hpp"
#include "ISceneObjectBuilder.hpp"


class DefaultHullCubeBuilder : public ISceneObjectBuilder
{
public:
    DefaultHullCubeBuilder& setWidth(double newWidth);

    std::shared_ptr<ISceneObject> build(const Transform& t = Transform()) override;

private:
    double width = 1.0;
};
