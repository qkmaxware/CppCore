# C++ Core Library - A C++ standard library based on namespace hierarchy
Collection of C++ classes organized into a rigid inheritance hierarchy. 
This library is meant as a tool to teach myself C++ as well as to create useful utilities.

## Compile library
### Compile directly using G++
```
g++ -std=c++14 -c src/sources/System.cpp src/sources/System.IO.cpp src/sources/System.Math.cpp -Isrc/headers
ar rvs header.a $(wildcard *.o)
g++ main.cpp header.a
```
### Compile with CMAKE
```
mkdir build && cd build
cmake .. --build
```