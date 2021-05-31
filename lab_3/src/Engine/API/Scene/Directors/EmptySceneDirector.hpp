#pragma once

#include "ISceneDirector.hpp"
#include "API/Scene/SceneBuilder.hpp"


class EmptySceneDirector : public ISceneDirector
{
public:
    EmptySceneDirector(std::shared_ptr<SceneBuilder> builer);
    virtual ~EmptySceneDirector() = default;

    virtual std::shared_ptr<Scene> makeScene() override;

private:
    std::shared_ptr<SceneBuilder> builder;
};
