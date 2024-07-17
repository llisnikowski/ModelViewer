
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

set(GLAD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/glad)

add_library(glad
    ${GLAD_DIR}/src/glad.c
)

target_include_directories(glad
PUBLIC
    ${GLAD_DIR}/include
)

add_library(glad::glad ALIAS glad)
