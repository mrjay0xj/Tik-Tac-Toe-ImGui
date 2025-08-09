cmake_minimum_required(VERSION 3.10)
project(tik-tak-toe-imgui)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
  "main.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_SOURCE_DIR}/libs/glfw/include/"
    "${CMAKE_SOURCE_DIR}/libs/imgui/"
    "${CMAKE_SOURCE_DIR}/libs/imgui/backends")

if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        "${CMAKE_SOURCE_DIR}/libs/glfw/thelib/glfw3.lib"
        "${CMAKE_SOURCE_DIR}/libs/imguiLib/imgui.lib"
        opengl32
        gdi32
        user32
        shell32
        advapi32
    )
else()
    find_package(OpenGL REQUIRED)
    target_link_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/libs/thelib")
    target_link_libraries(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/libs/glfw/thelib/libglfw3.a"
        imgui
        OpenGL::GL
        pthread
        dl
    )
endif()
