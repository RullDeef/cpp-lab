#pragma once

#include "API/Managers/ITransformManager.hpp"


class QtTransformManager : public ITransformManager
{
public:
    explicit QtTransformManager(std::shared_ptr<ISelectionManager> selectionManager);
    virtual ~QtTransformManager() = default;

    virtual void transformSelected(const Transform& t) override;

private:
    std::shared_ptr<ISelectionManager> selectionManager;
};
