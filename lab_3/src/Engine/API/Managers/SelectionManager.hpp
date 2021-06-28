#pragma once

#include "IManager.hpp"
#include "Objects/ObjectGroup.hpp"


class SelectionManager : public IManager
{
public:
    void selectObject(IObject* object);
    void deselectObject(IObject* object);

    IObject* getSelection();
    const IObject* getSelection() const;

    void clearSelection();

private:
    bool isObjectSelected(const IObject* object) const;

    ObjectGroup selection = ObjectGroup("{selection}", false);
};
