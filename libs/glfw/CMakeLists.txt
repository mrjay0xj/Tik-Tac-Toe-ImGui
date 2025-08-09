add_library(glfw3 STATIC IMPORTED)

set_target_properties(glfw3 PROPERTIES
  IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/lib/libglfw3.a"
  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/include"
)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw3 OpenGL::GL)

