cmake_minimum_required(VERSION 4.0)
project(sage)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false "src/*.cpp")
file(GLOB_RECURSE HEADERS LIST_DIRECTORIES false "src/*.h" "src/*.hpp")
file(GLOB_RECURSE DLLS "src/*.dll")
file(GLOB_RECURSE DLL_LIBS "src/*dll.lib")

add_executable(sage ${SOURCES} ${HEADERS})

foreach(LIB ${DLL_LIBS})
    target_link_libraries(sage ${LIB})
endforeach()

foreach(DLL ${DLLS})
    add_custom_command(TARGET sage POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${DLL}" "$<TARGET_FILE_DIR:sage>"
    )
endforeach()