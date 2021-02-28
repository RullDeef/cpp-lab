#pragma once

#include <list>
#include <glm/glm.hpp>
#include "model.hpp"

namespace core
{
    enum class EditMode
    {
        vertex,
        edge,
        all
    };

    struct Camera
    {
        glm::vec3 position;
        glm::vec3 look_direction;

        glm::mat4 view;
        glm::mat4 projection;
        glm::uvec4 viewport;
    };

    struct ModelContext
    {
        Model model;
        Camera camera;
        EditMode mode;

        std::list<unsigned int> selected_verts;
        std::list<unsigned int> selected_edges;
    };

    constexpr double default_fov = glm::radians(75.0);

    ModelContext wrap_model(Model model, int left, int top, int width, int height);

    glm::vec2 project(const ModelContext& context, const Model::Vertex& vertex);

    void clear_selection(ModelContext& context);
    
    // selection from viewport (depends on edit mode)
    void select(ModelContext& context, double x, double y);
    void toggle_selection(ModelContext& context, double x, double y);

    void remove_selected(ModelContext& context);
    void connect_selected_verts(ModelContext& context);

    // from viewport
    void add_vertex(ModelContext& context, double x, double y);

    // navigation functions
    void zoom(ModelContext& context, double delta);
    void grab(ModelContext& context, double dx, double dy);
    void orbit_aroud_selection(ModelContext& context, float phi, float theta);
}
