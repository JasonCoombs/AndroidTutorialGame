#include "Game.h"
#include "glm/ext/matrix_transform.hpp"

Game::Game(android_app *app) : renderer(app),
                               test_texture(app->activity->assetManager, "android_robot.png") {}

void Game::update() {
  std::vector<DrawCommand> draw_commands{
      DrawCommand{glm::mat4(1.f)},
      DrawCommand{glm::translate(glm::mat4(1.f), glm::vec3(test_position, 0.f)), &test_texture},
  };

  renderer.do_frame(draw_commands);
}

void Game::touch_event(glm::vec2 position) {
  test_position = position / glm::vec2(renderer.get_size());
  test_position.y = 1.f - test_position.y;
  test_position *= 2.f;
  test_position -= 1.f;
  test_position = glm::inverse(renderer.get_projection()) * glm::vec4(test_position, 0.f, 1.f);
}
