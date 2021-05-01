#pragma once

#include "sal.hpp"
#include "error_code.hpp"
#include "view/view.hpp"
#include "model/model.hpp"
#include "projection/projection.hpp"


ErrorCode do_init(OUT View& view, IN viewport viewport);
ErrorCode do_destroy(VAR Model& model, VAR Projection& proj);

ErrorCode do_load(VAR Model& model, IN const char* filename);
ErrorCode do_save(IN const Model& model, IN const View& view, IN const char* filename);

ErrorCode do_project(OUT Projection& proj, IN const Model& model, IN const View& view);
