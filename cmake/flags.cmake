
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

macro(addDefaultFlags target)

    if (MSVC)
        target_compile_options(${target} PRIVATE -W4 /XW)
    else ()
        target_compile_options(${target} PRIVATE -Wall -Wextra -pedantic -Wno-unused-function -Wno-unused-parameter -Wno-unused-variable -Wno-error=unused-private-field -Werror)
    endif ()

    if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
        target_compile_options(${target} PRIVATE -fdiagnostics-color=always)
    elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
        target_compile_options(${target} PRIVATE -fcolor-diagnostics)
    endif ()

endmacro()
