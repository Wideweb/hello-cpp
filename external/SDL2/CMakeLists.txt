set(SDL2_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/SDL2)

# Create imported target SDL2::SDL2-static
add_library(SDL2::SDL2-static STATIC IMPORTED)

set_target_properties(SDL2::SDL2-static PROPERTIES
    IMPORTED_LOCATION ${SDL2_DIR}/lib/libSDL2d.a
    IMPORTED_LOCATION_DEBUG ${SDL2_DIR}/lib/libSDL2d.a
    INTERFACE_INCLUDE_DIRECTORIES ${SDL2_DIR}/include
)

# Create imported target SDL2::SDL2
add_library(SDL2::SDL2 SHARED IMPORTED)

set_target_properties(SDL2::SDL2 PROPERTIES
    IMPORTED_LOCATION ${SDL2_DIR}/lib/libSDL2-2.0d.so
    IMPORTED_LOCATION_DEBUG ${SDL2_DIR}/lib/libSDL2-2.0d.so
    INTERFACE_INCLUDE_DIRECTORIES ${SDL2_DIR}/include
)

# Create imported target SDL2::SDL2main
add_library(SDL2::SDL2main STATIC IMPORTED)

set_target_properties(SDL2::SDL2main PROPERTIES
    IMPORTED_LOCATION ${SDL2_DIR}/lib/SDL2dmain.a
    IMPORTED_LOCATION_DEBUG ${SDL2_DIR}/lib/SDL2dmain.a
    INTERFACE_INCLUDE_DIRECTORIES ${SDL2_DIR}/include
)
