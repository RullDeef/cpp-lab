#include "EmptySceneDirector.hpp"

#include "API/Objects/Builders/DefaultCameraBuilder.hpp"
#include "API/Objects/Builders/DefaultHullCubeBuilder.hpp"
#include "API/Objects/Builders/TransformBuilder.hpp"


EmptySceneDirector::EmptySceneDirector(std::shared_ptr<SceneBuilder> builder)
    : builder(builder)
{
}

std::shared_ptr<Scene> EmptySceneDirector::makeScene()
{
    builder->startBuild();

    DefaultCameraBuilder cameraBuilder;
    cameraBuilder.setName("Camera");
    cameraBuilder.setTransform(Transform::translation({ 0.0, 0.0, -10.0 }));
    cameraBuilder.setNear(0.01);
    cameraBuilder.setFar(1000.0);
    cameraBuilder.setViewport(Rect(0.0, 0.0, 640.0, 480.0));

    builder->addObject(cameraBuilder.build());

    DefaultHullCubeBuilder hullCubeBuilder;
    hullCubeBuilder.setName("Cube");
    hullCubeBuilder.setWidth(1.0);

    builder->addObject(hullCubeBuilder.build());

    {
        auto builder = DefaultHullCubeBuilder();
        builder.setWidth(0.2);
        for (double dx = -0.15; dx <= 0.15; dx += 0.15)
        {
            builder.setName(std::string("Cube #") + std::to_string(dx / 0.15 + 1));
            builder.setTransform(TransformBuilder()
                .translate({ dx, 0.0, 0.0 })
                .rotate({ 1.0, dx, 1.0 }, 3.1415 / 6)
                .build());
            this->builder->addObject(builder.build());
        }
    }

    return builder->getResult();
}
