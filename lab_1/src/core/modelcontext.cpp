#include <glm/gtc/matrix_transform.hpp>
#include "modelcontext.hpp"

using namespace core;
using namespace glm;

inline void update_camera_view(Camera& camera)
{
    camera.view = lookAt(camera.position, camera.look_center, vec3(0, 1, 0));
}

static void init_camera(Camera& camera, int left, int top, int width, int height)
{
    camera.position = vec3(0, 0, -10);
    camera.look_center = vec3(0, 0, 0);
    
    camera.projection = perspective(default_fov, static_cast<double>(width) / height, 0.1, 1000.0);
    camera.viewport = uvec4(left, top, width, height);

    update_camera_view(camera);
}

ModelContext core::wrap_model(Model model, int left, int top, int width, int height)
{
    ModelContext context;

    context.model = model;
    context.mode = EditMode::all;
    init_camera(context.camera, left, top, width, height);

    return context;
}

vec2 core::project(const ModelContext& context, const Model::Vertex& vertex)
{
    return glm::project(vec3(vertex.x, vertex.y, vertex.z),
        context.camera.view, context.camera.projection, context.camera.viewport);
}

void core::clear_selection(ModelContext& context)
{
    context.selected_verts.clear();
    context.selected_edges.clear();
}

// selection from viewport (depends on edit mode)
void core::select(ModelContext& context, double x, double y)
{
    clear_selection(context);
}

void core::toggle_selection(ModelContext& context, double x, double y)
{

}

void core::remove_selected(ModelContext& context)
{

}

void core::connect_selected_verts(ModelContext& context)
{

}

// from viewport
void core::add_vertex(ModelContext& context, double x, double y)
{

}

// navigation functions
void core::zoom(ModelContext& context, double delta)
{
    vec3 direction = normalize(context.camera.look_center - context.camera.position);

    direction.x *= delta;
    direction.y *= delta;
    direction.z *= delta;

    context.camera.position += direction;

    update_camera_view(context.camera);
}

void core::grab(ModelContext& context, double dx, double dy)
{
    mat4 inv = inverse(context.camera.view * context.camera.projection);
    vec3 local_delta = vec4(dx, dy, 0, 0) * context.camera.view;

    context.camera.position -= local_delta;
    context.camera.look_center -= local_delta;

    update_camera_view(context.camera);
}

void core::orbit_aroud_selection(ModelContext& context, float phi, float theta)
{
    vec3 local_x_axis = vec4(1, 0, 0, 0) * context.camera.view;
    vec3 local_y_axis = vec4(0, 1, 0, 0) * context.camera.view;

    context.camera.position = vec3(
        vec4(context.camera.position - context.camera.look_center, 1)
        * rotate(identity<mat4>(), phi, local_y_axis)
        * rotate(identity<mat4>(), -theta, local_x_axis))
        + context.camera.look_center;

    update_camera_view(context.camera);
}
