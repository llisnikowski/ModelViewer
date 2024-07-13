cmake_minimum_required(VERSION 3.13)

project(cad)

include(cmake/lib-imgui.cmake)


file(GLOB SRCS
    src/*.cpp
)

add_executable(${PROJECT_NAME}
    ${SRCS}
)

target_link_libraries(${PROJECT_NAME}
PRIVATE
    imgui::imgui    
)
