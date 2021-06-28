#include "FileWireframeModelDirector.hpp"
#include "Creators/Loaders/OBJLoader/OBJLoader.hpp"
#include "Creators/Builders/WireframeModelBuilder.hpp"
#include "Objects/WireframeModel/WireframeModelAdapter.hpp"


FileWireframeModelDirector::FileWireframeModelDirector(const std::string& filename)
    : filename(filename)
{
}

IObject* FileWireframeModelDirector::makeObject()
{
    WireframeModelBuilder builder;
    OBJLoader loader(filename);

    for (const auto& pos : loader.getPositions())
        builder.addVertex(Vertex(pos));

    for (const auto& face : loader.getFaces())
    {
        const auto& positions = face.getPositions();
        if (positions.size() >= 3)
        {
            for (auto iter = positions.begin(); ++iter-- != positions.end(); iter++)
                builder.addEdge(*iter - 1, *(++iter--) - 1);
            builder.addEdge(positions.back() - 1, positions.front() - 1);
        }
    }

    return new WireframeModelAdapter(builder.getResult());
}
