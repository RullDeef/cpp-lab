#pragma once

#include <string>

class IObjectVisitor;


class IObject
{
public:
    explicit IObject(const std::string& name = "(unnamed)");
    virtual ~IObject() = default;

    const std::string& getName() const;
    void setName(const std::string& newName);

    virtual void accept(IObjectVisitor& visitor) {};

private:
    std::string name;
};