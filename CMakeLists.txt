cmake_minimum_required(VERSION 3.13)

project(cad)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(assimp REQUIRED)


include(cmake/lib-imgui.cmake)
include(cmake/lib-glad.cmake)
include(cmake/fileLists.cmake)
include(cmake/flags.cmake)
include(cmake/cppcheck.cmake)
include(cmake/clang-tidy.cmake)
include(cmake/clang-format.cmake)
include(cmake/pre-commit-check.cmake)


add_executable(${PROJECT_NAME}
    ${MAIN_SOURCES}
)

target_include_directories(${PROJECT_NAME}
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/stb
)

addDefaultFlags(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
PRIVATE
    imgui::imgui
    glad::glad
    glm::glm
    assimp::assimp
)
