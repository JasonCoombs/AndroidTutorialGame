#pragma once

#include <string>
#include <GLES3/gl3.h>
#include <android/asset_manager.h>

class Texture {
public:
  explicit Texture(AAssetManager *asset_manager, const std::string &file_path);
  ~Texture();

  [[nodiscard]] auto get_width() const { return width; }

  [[nodiscard]] auto get_height() const { return height; }

  [[nodiscard]] auto get_id() const { return id; }

private:
  int width{}, height{};
  GLuint id{};
};
