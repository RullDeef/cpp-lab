#pragma once

#include "Controller.hpp"
#include <stdexcept>


template<typename _Manager>
_Manager& Controller::getManager()
{
    type_info type = typeid(_Manager);
    if (!managers[type])
        throw std::runtime_error("Controller: could not find proper manager");
    return *managers[type];
}
