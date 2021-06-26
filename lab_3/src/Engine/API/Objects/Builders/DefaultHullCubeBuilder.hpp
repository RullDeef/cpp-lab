#pragma once

#include "API/Objects/HullModel/HullModel.hpp"
#include "ISceneObjectBuilder.hpp"
#include "API/Objects/ISceneObject.hpp"


class DefaultHullCubeBuilder : public ISceneObjectBuilder
{
public:
    void setWidth(double newWidth);

    virtual std::shared_ptr<ISceneObject> build() override;

private:
    double width = 1.0;
};
