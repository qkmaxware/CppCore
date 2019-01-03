cmake_minimum_required(VERSION 2.8)
project(CppCore)
set(CMAKE_CXX_STANDARD 17)

file(GLOB Sources src/**/*.cpp)
file(GLOB Headers src/**/*.hpp)

add_library(libcppcore STATIC ${Sources} ${Headers})
target_include_directories(libcppcore PUBLIC src/headers)

install(TARGETS libcppcore DESTINATION lib)
install(FILES ${Headers} DESTINATION include)



##################################
# Download and install GoogleTest
 
include(ExternalProject)
set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)
ExternalProject_Add(googletest
    GIT_REPOSITORY  https://github.com/google/googletest
    GIT_TAG         master
    CMAKE_ARGS      -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
)
 
include_directories(${EXTERNAL_INSTALL_LOCATION}/include)
link_directories(${EXTERNAL_INSTALL_LOCATION}/lib)

#################################
# Add unit tests
add_executable(test_all test/all.cpp)
target_include_directories(test_all PUBLIC test/cases)
add_dependencies(test_all googletest)
target_link_libraries(test_all libcppcore gmock gtest pthread)