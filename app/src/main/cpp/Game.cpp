#include "Game.h"
#include "glm/gtc/matrix_transform.hpp"

Game::Game(android_app *app) : camera(2.5f), renderer(app),
                               test_texture(app->activity->assetManager, "android_robot.png") {}

void Game::update() {
  RenderData data{camera};
  camera.position = test_position;

  data.draw_cmds = {
      // DrawCommand{glm::translate(glm::mat4(1.f), glm::vec3(test_position, 0.f))},
      // DrawCommand{glm::translate(glm::mat4(1.f), glm::vec3(test_position, 0.f)), &test_texture},
  };

  data.text_cmds = {
      TextCommand{"Hi!"},
  };

  renderer.do_frame(data);
}

void Game::touch_event(glm::vec2 position, TouchEventType type) {
  position /= glm::vec2(renderer.get_size());
  position.y = 1.f - position.y;
  position *= 2.f;
  position -= 1.f;
  position = glm::inverse(camera.get_projection()) * glm::vec4(position, 0.f, 1.f);

  switch (type) {
    case TouchEventType::Down:
      if (position.x > test_position.x - test_size / 2.f &&
          position.x < test_position.x + test_size / 2.f &&
          position.y > test_position.y - test_size / 2.f &&
          position.y < test_position.y + test_size / 2.f) {
        test_selected = true;
      }
      break;
    case TouchEventType::Move:
      test_position = position;
      break;
    case TouchEventType::Up:
      test_selected = false;
      break;
  }
}
