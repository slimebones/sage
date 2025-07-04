cmake_minimum_required(VERSION 3.0)
project(sage)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false "src/*.cpp")
file(GLOB_RECURSE HEADERS LIST_DIRECTORIES false "src/*.h" "src/*.hpp")
file(GLOB_RECURSE DLLS "src/*.dll")
file(GLOB_RECURSE DLL_LIBS "src/*dll.lib")

add_executable(sage ${SOURCES} ${HEADERS})

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(sage PRIVATE
        -Wno-all
    )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(sage PRIVATE
        -Wno-all
    )
elseif(MSVC)
    target_compile_options(sage PRIVATE
        /w
    )
endif()

foreach(LIB ${DLL_LIBS})
    target_link_libraries(sage ${LIB})
endforeach()

foreach(DLL ${DLLS})
    add_custom_command(TARGET sage POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${DLL}" "$<TARGET_FILE_DIR:sage>"
    )
endforeach()

# Copy resources to binary folder.
set(RESOURCE_FOLDER ${CMAKE_SOURCE_DIR}/res)
add_custom_command(
    TARGET sage POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${RESOURCE_FOLDER}
        $<TARGET_FILE_DIR:sage>/res
)
