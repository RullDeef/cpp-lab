#pragma once

#include <memory>

class Scene;
class SceneObjectGroup;
class ICamera;
class HullModelAdapter;
class CameraAdapter;
class Vertex;
class Edge;


class IObjectVisitor
{
public:
    virtual ~IObjectVisitor() = default;

    virtual void visit(Scene& scene) {}
    virtual void visit(SceneObjectGroup& group) {}
    virtual void visit(ICamera& camera) {}
    virtual void visit(HullModelAdapter& hullModelAdapter) {}
    virtual void visit(CameraAdapter& cameraAdapter) {}
    virtual void visit(Vertex& vertex) {}
    virtual void visit(Edge& edge) {}

protected:
    IObjectVisitor() = default;
};
