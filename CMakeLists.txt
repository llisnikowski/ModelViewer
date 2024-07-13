cmake_minimum_required(VERSION 3.13)

project(cad)

include(cmake/lib-imgui.cmake)
include(cmake/fileLists.cmake)
include(cmake/flags.cmake)
include(cmake/cppcheck.cmake)
include(cmake/clang-tidy.cmake)
include(cmake/clang-format.cmake)
include(cmake/pre-commit-check.cmake)


add_executable(${PROJECT_NAME}
    ${MAIN_SOURCES}
)

addDefaultFlags(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
PRIVATE
    imgui::imgui
)
