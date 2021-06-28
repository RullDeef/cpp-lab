#include "WireframeCubeDirector.hpp"
#include "Objects/WireframeModel/WireframeModelAdapter.hpp"
#include "Creators/Builders/WireframeModelBuilder.hpp"
#include "Utils/Logger.hpp"


IObject* WireframeCubeDirector::makeObject()
{
    LOG_FUNC;

    constexpr double size = 100.0;
    constexpr double hsize = size / 2;

    WireframeModelBuilder builder;

    builder.addVertex(Vertex(Vector(-hsize, -hsize, -hsize)));
    builder.addVertex(Vertex(Vector( hsize, -hsize, -hsize)));
    builder.addVertex(Vertex(Vector(-hsize,  hsize, -hsize)));
    builder.addVertex(Vertex(Vector( hsize,  hsize, -hsize)));
    builder.addVertex(Vertex(Vector(-hsize, -hsize,  hsize)));
    builder.addVertex(Vertex(Vector( hsize, -hsize,  hsize)));
    builder.addVertex(Vertex(Vector(-hsize,  hsize,  hsize)));
    builder.addVertex(Vertex(Vector( hsize,  hsize,  hsize)));

    builder.addEdge(0, 1);
    builder.addEdge(0, 2);
    builder.addEdge(0, 4);
    builder.addEdge(1, 3);
    builder.addEdge(1, 5);
    builder.addEdge(2, 3);
    builder.addEdge(2, 6);
    builder.addEdge(3, 7);
    builder.addEdge(4, 5);
    builder.addEdge(4, 6);
    builder.addEdge(5, 7);
    builder.addEdge(6, 7);

    IObject* object = new WireframeModelAdapter(builder.getResult());
    object->setName("Cube");
    return object;
}
