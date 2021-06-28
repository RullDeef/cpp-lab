#pragma once

#include "Objects/IObject.hpp"
#include "Camera.hpp"


class CameraAdapter : public IObject
{
public:
    CameraAdapter(const std::string& name, Camera* camera);
    explicit CameraAdapter(Camera* camera);

    ~CameraAdapter();

    Camera& getCamera();
    const Camera& getCamera() const;

    void accept(IObjectVisitor& visitor) override;

private:
    Camera* camera;
};
