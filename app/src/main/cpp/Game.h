#pragma once

#include <game-activity/native_app_glue/android_native_app_glue.h>

#include "Renderer.h"
#include "Camera.h"

enum class TouchEventType {
  Down,
  Move,
  Up,
};

struct GameObject {
  glm::vec2 position{}, size{1.f};
  glm::vec4 color{1.f};
  Texture *texture{};

  std::function<void(glm::vec2 position, TouchEventType type)> on_touch{};
};

class Game {
public:
  explicit Game(android_app *app);

  void touch_event(glm::vec2 position, TouchEventType type);
  void update();

private:
  Camera camera;
  Renderer renderer;

  std::vector<GameObject> objects;
};
