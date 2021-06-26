#pragma once

#include "API/Objects/ISceneObject.hpp"


class ISceneObjectBuilder
{
public:
    virtual ~ISceneObjectBuilder() = default;

    void setName(const std::string& name);
    void setTransform(const Transform& t);

    virtual std::shared_ptr<ISceneObject> build() = 0;

protected:
    const std::string& getName() const;
    const Transform& getTransform() const;

private:
    std::string name = "";
    Transform transform;
};
