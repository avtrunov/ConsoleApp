This is the Chatbot project using CMake.

# Requirements

* CMake 3.21 or better
* A C++17 compatible compiler
* Boost libraries: algorithm and regex (header only)
* REST-SDK
* SQLite3
* OpenCV
* tabulate
* FTXUI
* GoogleTest (optional)

# Adding dependencies

You must have installed vcpkg on your computer.

* vcpkg install sqlite3 sqlite3:x64-windows
* vcpkg install cpprest cpprest:x64-windows
* vcpkg install opencv opencv:x64-windows
* vcpkg install tabulate tabulate:x64-windows
* vcpkg install ftxui ftxui:x64-windows
* vcpkg install gtest gtest:x64-windows (optional)
* vcpkg integrate install

# Configuring

* mkdir build
* cd build

# Disable testing - default

* cmake ..

# Enable testing

* cmake .. -D BUILD_TESTS=ON

# Building

* cmake --build .
