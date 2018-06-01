cmake_minimum_required(VERSION 2.8.12)
project(cmake_example)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(pybind11)

add_library(prueba
  SHARED
  #STATIC
  src/prueba.cpp
)

target_link_libraries(prueba
  pybind11::module
)

set_property(TARGET prueba PROPERTY POSITION_INDEPENDENT_CODE ON)

pybind11_add_module(prueba_bindings src/prueba_bindings.cpp)

target_link_libraries(prueba_bindings
  PRIVATE
  prueba
  pybind11::module
)

