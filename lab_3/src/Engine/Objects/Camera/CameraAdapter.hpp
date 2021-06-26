#pragma once

#include "Objects/IObject.hpp"
#include "Camera.hpp"


class CameraAdapter : IObject
{
public:
    CameraAdapter(const std::string& name, Camera* camera);
    explicit CameraAdapter(Camera* camera);

    ~CameraAdapter();

    void accept(IObjectVisitor& visitor) override;

private:
    Camera* camera;
};
