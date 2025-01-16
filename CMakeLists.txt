cmake_minimum_required(VERSION 3.10)
project(sage)

set(RAYLIB_DIR "${CMAKE_SOURCE_DIR}/lib/raylib")
set(RAYLIB_DLL "${RAYLIB_DIR}/lib/raylib.dll")

find_library(RAYLIB_LIBRARY NAMES raylibdll PATHS "${RAYLIB_DIR}/lib")

include_directories("${RAYLIB_DIR}/include")

add_executable(main src/main.c)

target_link_libraries(main ${RAYLIB_LIBRARY})

add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${RAYLIB_DLL}"
    "$<TARGET_FILE_DIR:main>"
)
