#pragma once

#include "Objects/IObject.hpp"
#include "WireframeModel.hpp"


class WireframeModelAdapter : public IObject
{
public:
    WireframeModelAdapter(const std::string& name, WireframeModel* model);
    explicit WireframeModelAdapter(WireframeModel* model);

    ~WireframeModelAdapter();

    WireframeModel& getModel();
    const WireframeModel& getModel() const;

    void accept(IObjectVisitor& visitor) override;

private:
    WireframeModel* model;
};
