#include <chrono>
#include <iostream>
#include <mutex>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <thread>

#include "prueba.cpp"

namespace py = pybind11;

PYBIND11_MODULE(prueba_bindings, m) {
  py::class_<Prueba>(m, "Prueba")
    .def(py::init<>())
    .def("add", &Prueba::add)
    .def("start", &Prueba::start)
    .def("add_step_callback", &Prueba::add_step_callback);
}
