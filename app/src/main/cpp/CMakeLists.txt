cmake_minimum_required(VERSION 3.22.1)

project("mygame")

add_library(mygame SHARED
        main.cpp
        Renderer.cpp)

add_subdirectory(glm)
find_package(game-activity REQUIRED CONFIG)

target_link_libraries(mygame
        game-activity::game-activity
        glm
        EGL
        GLESv3
        jnigraphics
        android
        log)