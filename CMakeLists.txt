cmake_minimum_required( VERSION 3.22 )

file( STRINGS RELEASES.md releases )
list( GET releases 0 ver )
project( skipbo VERSION ${ver} )

file( GLOB_RECURSE files src/*.h src/*.cpp )
add_executable( ${PROJECT_NAME} ${files} RELEASES.md )
target_compile_features( ${PROJECT_NAME} PRIVATE cxx_std_20 )

configure_file( src/version.h.in generated_files/version.h )
target_include_directories( ${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/generated_files" )