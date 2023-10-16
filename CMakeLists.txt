cmake_minimum_required( VERSION 3.22 )

file( STRINGS RELEASES.md releases )
list( GET releases 0 ver )
project( skipbo VERSION ${ver} )

file( GLOB_RECURSE files src/*.h src/*.cpp )
list( FILTER files EXCLUDE REGEX .*src/main.cpp )

add_library( ${PROJECT_NAME}-object OBJECT ${files} )
target_compile_features( ${PROJECT_NAME}-object PRIVATE cxx_std_20 )

add_executable( ${PROJECT_NAME} $<TARGET_OBJECTS:${PROJECT_NAME}-object> src/main.cpp RELEASES.md )
target_compile_features( ${PROJECT_NAME} PRIVATE cxx_std_20 )

configure_file( src/version.h.in generated_files/version.h )
target_include_directories( ${PROJECT_NAME}-object PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/generated_files" )
target_include_directories( ${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/generated_files" )

include( FetchContent )
FetchContent_Declare( 
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.4.0
    )
FetchContent_MakeAvailable( Catch2 )

file( GLOB_RECURSE testfiles src/*.hh src/*.cc )
add_executable( ${PROJECT_NAME}-tests $<TARGET_OBJECTS:${PROJECT_NAME}-object> ${testfiles} )
target_compile_features( ${PROJECT_NAME}-tests PRIVATE cxx_std_20 )
target_link_libraries( ${PROJECT_NAME}-tests PRIVATE Catch2::Catch2WithMain )

add_custom_command(
    TARGET ${PROJECT_NAME}-tests
    COMMENT "Run Tests"
    POST_BUILD
    COMMAND ${PROJECT_NAME}-tests
)