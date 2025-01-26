#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera {
public:
  explicit Camera(float zoom = 1.f, glm::vec2 position = {}) : zoom(zoom), position(position),
                                                               projection(), view() {}

  void update_projection(float width, float height) {
    float inv_aspect = (float) height / (float) width;
    projection = glm::ortho(-zoom, zoom, -zoom * inv_aspect, zoom * inv_aspect);
  }

  void update_view() {
    view = glm::translate(glm::mat4{1.f}, -glm::vec3{position, 0.f});
  }

  glm::mat4 get_projection() const {
    return projection;
  }

  glm::mat4 get_view() const {
    return view;
  }

  glm::mat4 projection, view;
  glm::vec2 position;
  float zoom;
};
