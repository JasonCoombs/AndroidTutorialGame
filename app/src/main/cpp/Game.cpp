#include "Game.h"
#include "glm/ext/matrix_transform.hpp"

Game::Game(android_app *app) : renderer(app),
                               test_texture(app->activity->assetManager, "android_robot.png") {}

void Game::update() {
  std::vector<DrawCommand> draw_commands{
      DrawCommand{glm::mat4(1.f)},
      DrawCommand{glm::scale(glm::mat4(1.f), glm::vec3(.5f)), &test_texture},
  };

  renderer.do_frame(draw_commands);
}
