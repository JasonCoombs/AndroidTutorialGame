#pragma once

#include <game-activity/native_app_glue/android_native_app_glue.h>

#include "Renderer.h"
#include "Camera.h"

enum class TouchEventType {
  Down,
  Move,
  Up,
};

struct GameState {
  Camera &camera;
  float dt;
};

struct GameObject {
  std::string tag{};
  glm::vec2 position{}, size{1.f};
  glm::vec4 color{1.f};
  Texture *texture{};

  bool selected{};
  glm::vec2 selection_offset{};

  glm::vec2 direction{};
  float speed{};

  std::function<void(GameObject &, GameState)> on_update{};
  std::function<void(GameObject &, GameState, glm::vec2, TouchEventType)> on_touch{};
};

class Game {
public:
  explicit Game(android_app *app);

  void touch_event(glm::vec2 position, TouchEventType type);
  void update(float dt);

private:
  Camera camera;
  Renderer renderer;

  std::vector<GameObject> objects;
};
