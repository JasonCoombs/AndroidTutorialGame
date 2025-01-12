#include "Game.h"
#include "glm/gtc/matrix_transform.hpp"

Game::Game(android_app *app) : renderer(app),
                               test_texture(app->activity->assetManager, "android_robot.png") {}

void Game::update() {
  std::vector<DrawCommand> draw_commands{
      DrawCommand{glm::translate(glm::mat4(1.f), glm::vec3(test_position, 0.f))},
      // DrawCommand{glm::translate(glm::mat4(1.f), glm::vec3(test_position, 0.f)), &test_texture},
  };

  renderer.do_frame(draw_commands);
}

void Game::touch_event(glm::vec2 position, TouchEventType type) {
  position /= glm::vec2(renderer.get_size());
  position.y = 1.f - position.y;
  position *= 2.f;
  position -= 1.f;
  position = glm::inverse(renderer.get_projection()) * glm::vec4(position, 0.f, 1.f);

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
      if (test_selected) {
        test_position = position;
      }
      break;
    case TouchEventType::Up:
      test_selected = false;
      break;
  }
}
