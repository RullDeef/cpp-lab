#pragma once

#include <memory>
#include <string>
#include "SceneDirector.hpp"


class FileSceneDirector : public SceneDirector
{
public:
    explicit FileSceneDirector(const std::string& filename);
    std::shared_ptr<Scene> makeScene() override;

private:
    std::string filename;
};
