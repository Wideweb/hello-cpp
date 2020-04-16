cmake_minimum_required(VERSION 3.13)

project(Hello VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

set(OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

#include(external/SDL2/CMakeLists.txt)

function(add_external)
    set(options SHARED STATIC)
    set(oneValueArgs TARGET LIB)
    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "" ${ARGN})

    target_link_libraries(${ARG_TARGET} PRIVATE ${ARG_LIB})

    if (ARG_SHARED)
        get_target_property(LIB_FILE ${ARG_LIB} IMPORTED_LOCATION)

        add_custom_command(TARGET ${ARG_TARGET} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy ${LIB_FILE} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        )
    endif()
endfunction()

# add_subdirectory(hello-lib)
# add_subdirectory(hello-bin)
# add_subdirectory(hello-sdl)
add_subdirectory(hello-render)
