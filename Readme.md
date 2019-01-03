## C++ Core Library - A C++ standard library based on modular namespaces

###Compile with G++ using Make
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