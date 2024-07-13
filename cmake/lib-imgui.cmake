
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui)


file(GLOB IMGUI_SOURCES
    ${IMGUI_DIR}/*.cpp
)

add_library(imgui
    ${IMGUI_SOURCES}
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui
PUBLIC
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

target_link_libraries(imgui
PUBLIC
    OpenGL::GL
    glfw
)

add_library(imgui::imgui ALIAS imgui)
