#pragma once

#include <memory>
#include "API/Objects/ISceneObject.hpp"
#include "ICamera.hpp"


class CameraAdapter : public ISceneObject
{
public:
    explicit CameraAdapter(std::shared_ptr<ICamera> camera);
    virtual ~CameraAdapter() = default;

    virtual std::shared_ptr<ISceneObject> clone() const override;

    virtual void accept(IObjectVisitor* visitor) override;
    virtual bool isVisible() const override;

    std::shared_ptr<ICamera> getCamera();

    virtual std::shared_ptr<Memento> saveState() override;
    virtual void restoreState(std::shared_ptr<Memento> memento) override;

    virtual ISceneObjectIterator begin() override;
    virtual ISceneObjectIterator end() override;
    virtual ISceneObjectConstIterator begin() const override;
    virtual ISceneObjectConstIterator end() const override;

private:
    std::shared_ptr<ICamera> camera;
};
