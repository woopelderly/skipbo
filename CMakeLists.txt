cmake_minimum_required( VERSION 3.22 )

file( STRINGS RELEASES.md releases )
list( GET releases 0 ver )
project( skipbo VERSION ${ver} )

file( GLOB_RECURSE files src/*.h src/*.cpp )
add_executable( ${PROJECT_NAME} ${files} RELEASES.md )
target_compile_features( ${PROJECT_NAME} PRIVATE cxx_std_20 )

configure_file( src/version.h.in generated_files/version.h )
target_include_directories( ${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/generated_files" )

include( FetchContent )
FetchContent_Declare( Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG    v3.4.0
)

FetchContent_MakeAvailable( Catch2 )

file( GLOB_RECURSE testfiles src/*.hh src/*.cc )
add_executable( ${PROJECT_NAME}-tests ${testfiles} )
target_link_libraries( ${PROJECT_NAME}-tests PRIVATE Catch2::Catch2WithMain )

add_custom_command(
    TARGET ${PROJECT_NAME}-tests
    COMMENT "Run Tests"
    POST_BUILD
    COMMAND ${PROJECT_NAME}-tests
)