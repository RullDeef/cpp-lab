#pragma once

#include "API/Objects/HullModel/HullModel.hpp"
#include "ISceneObjectBuilder.hpp"
#include "API/Objects/ISceneObject.hpp"


class DefaultHullCubeBuilder : public ISceneObjectBuilder
{
public:
    DefaultHullCubeBuilder& setWidth(double newWidth);

    std::shared_ptr<ISceneObject> build(const Transform& t = Transform()) override;

private:
    double width = 1.0;
};
