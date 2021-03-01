#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/intersect.hpp>
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

static vec3 ray_trace_from(const Camera& camera, int x, int y)
{
    float m_x = x / (camera.viewport.z * 0.5f) - 1.0f;
    float m_y = y / (camera.viewport.w * 0.5f) - 1.0f;

    glm::mat4 inv_VP = glm::inverse(camera.projection * camera.view);
    glm::vec4 screen_pos = glm::vec4(m_x, m_y, 1.0f, 1.0f);
    glm::vec4 world_pos = inv_VP * screen_pos;

    return glm::normalize(glm::vec3(world_pos));
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
void core::select(ModelContext& context, int x, int y)
{
    clear_selection(context);

    constexpr auto radius = 0.04f;
    vec3 dir = ray_trace_from(context.camera, x, y);

    float closest_dist = 0.0f;
    unsigned int selected_vertex_index = 0;
    bool selected = false;

    for (unsigned int i = 0; i < context.model.verts.size(); i++)
    {
        Model::Vertex vert = context.model.verts[i];
        vec3 v_pos = vec3(vert.x, vert.y, vert.z);
        float dist;
        if (intersectRaySphere(context.camera.position, dir, v_pos, radius, dist))
        {
            if (!selected || dist < closest_dist)
            {
                selected_vertex_index = i;
                closest_dist = dist;
            }
            selected = true;
        }
    }

    if (selected)
        context.selected_verts.push_back(selected_vertex_index);
}

void core::toggle_selection(ModelContext& context, int x, int y)
{
    constexpr auto radius = 0.04f;
    vec3 dir = ray_trace_from(context.camera, x, y);

    float closest_dist = 0.0f;
    unsigned int selected_vertex_index = 0;
    bool selected = false;

    for (unsigned int i = 0; i < context.model.verts.size(); i++)
    {
        Model::Vertex vert = context.model.verts[i];
        vec3 v_pos = vec3(vert.x, vert.y, vert.z);
        float dist;
        if (intersectRaySphere(context.camera.position, dir, v_pos, radius, dist))
        {
            if (!selected || dist < closest_dist)
            {
                selected_vertex_index = i;
                closest_dist = dist;
            }
            selected = true;
        }
    }

    if (selected)
    {
        auto iter = std::find(context.selected_verts.begin(), context.selected_verts.end(), selected_vertex_index);
        if (iter != context.selected_verts.end())
            context.selected_verts.erase(iter);
        else
            context.selected_verts.push_back(selected_vertex_index);
    }
}

// not done yet
void core::remove_selected(ModelContext& context)
{
    std::vector<Model::Vertex> new_verts;
    size_t new_size = context.selected_verts.size() - context.selected_verts.size();

    if (new_size == 0)
    {
        // ...
    }
    else
    {
        new_verts.resize(new_size);
        auto sel_iter = context.selected_verts.begin();

        for (unsigned int i = 0; i < context.model.verts.size(); i++)
        {
            if (i == *sel_iter)
            {
                sel_iter++;
            }
            else
                new_verts.push_back(context.model.verts[i]);
        }

        // ...
    }

    core::clear_selection(context);
}

void core::connect_selected_verts(ModelContext& context)
{
    auto iter_1 = context.selected_verts.begin();
    auto iter_2 = context.selected_verts.begin();

    iter_2++;
    while (iter_2 != context.selected_verts.end())
    {
        unsigned int v1_id = *iter_1;
        unsigned int v2_id = *iter_2;

        context.model.edges.push_back(Model::Edge {v1_id, v2_id});

        iter_1++;
        iter_2++;
    }
}

// from viewport
void core::add_vertex(ModelContext& context, int x, int y)
{
    vec3 dir = ray_trace_from(context.camera, x, y);
    float distance;

    intersectRayPlane(context.camera.position, dir, context.camera.look_center,
        context.camera.position - context.camera.look_center, distance);

    dir.x *= distance;
    dir.y *= distance;
    dir.z *= distance;

    vec3 v_pos = context.camera.position + dir;
    core::model_vertex_add(context.model, Model::Vertex {v_pos.x, v_pos.y, v_pos.z});
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

void core::orbit_around_selection(ModelContext& context, float phi, float theta)
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
