#pragma once

#include "Objects/IObject.hpp"

class ObjectGroup;
class WireframeModelAdapter;
class CameraAdapter;


class IObjectVisitor
{
public:
    virtual ~IObjectVisitor() = default;

    virtual void visit(ObjectGroup& object) {}
    virtual void visit(WireframeModelAdapter& object) {}
    virtual void visit(CameraAdapter& object) {}

protected:
    IObjectVisitor() = default;
};
