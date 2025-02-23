#include "Game.h"
#include "glm/gtc/matrix_transform.hpp"
#include "logging.h"

Game::Game(android_app *app) : camera(2.5f), renderer(app) {
  objects = {
      GameObject{
          .tag = "Player",
          .size = {1.f, .25f},
          .color = {1.f, 1.f, 0.f, 1.f},
          .on_update = [](GameObject &self, GameState state) {
            self.position.y = state.camera.bottom + 1.f;
          },
          .on_touch = [](GameObject &self, GameState state, glm::vec2 pos, TouchEventType type) {
            if (type == TouchEventType::Down) {
              self.selected = true;
              self.selection_offset = pos - self.position;
            } else if (type == TouchEventType::Up) {
              self.selected = false;
            } else if (type == TouchEventType::Move && self.selected) {
              self.position.x = std::clamp((pos - self.selection_offset).x,
                                           state.camera.left + self.size.x / 2.f,
                                           state.camera.right - self.size.x / 2.f);
            }
          },
      },
  };
}

void Game::update() {
  RenderData data{camera, {.65f, .8f, 1.f}};

  GameState state{camera};
  for (auto &object : objects) {
    object.on_update(object, state);

    auto T = glm::translate(glm::mat4{1.f}, glm::vec3(object.position, 0.f));
    auto S = glm::scale(glm::mat4{1.f}, glm::vec3(object.size, 0.f));

    data.draw_cmds.push_back(DrawCommand{T * S, object.texture, object.color});
  }

  renderer.do_frame(data);
}

void Game::touch_event(glm::vec2 position, TouchEventType type) {
  position /= glm::vec2(renderer.get_size());
  position.y = 1.f - position.y;
  position *= 2.f;
  position -= 1.f;
  position = glm::inverse(camera.get_projection()) * glm::vec4(position, 0.f, 1.f);

  GameState state{camera};
  for (auto &object : objects) {
    if (object.selected || (object.on_touch && position.x > object.position.x - object.size.x / 2.f
        && position.x < object.position.x + object.size.x / 2.f
        && position.y > object.position.y - object.size.y / 2.f
        && position.y < object.position.y + object.size.y / 2.f)) {
      object.on_touch(object, state, position, type);
    }
  }
}
