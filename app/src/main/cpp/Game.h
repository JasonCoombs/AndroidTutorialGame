#pragma  once

#include <game-activity/native_app_glue/android_native_app_glue.h>

#include "Renderer.h"

class Game {
public:
  explicit Game(android_app *app);

  void update();

private:
  Renderer renderer;
  Texture test_texture;
};
