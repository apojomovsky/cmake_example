#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

class Prueba {
 public:

  Prueba(void) {}

  ~Prueba(void) {}

  int add(int i, int j) {
      return i + j;
  }

  void add_step_callback(std::function<void()> callable) {
    std::lock_guard<std::mutex> lock(mutex_);
    step_callbacks_.push_back(callable);
  }

  void run(void) {
    py::gil_scoped_release release;
    int i=0;
    while(i<50) {
      std::cout << "Hola!" << std::endl;
      std::cout << 1 << std::endl;
      std::vector<std::function<void()>> callbacks;
      {
        std::lock_guard<std::mutex> lock(mutex_);
        callbacks = step_callbacks_;
      }
      std::cout << 2 << std::endl;
      {
        std::cout << 3 << std::endl;
        // Commenting out this release ends up blocking the execution.
        std::cout << 4 << std::endl;
        for (std::function<void()> callback : callbacks) {
          std::cout << 5 << std::endl;
          // Calling this or not doesn't affect the demo
          // py::gil_scoped_acquire acquire;
          callback();
          std::cout << 6 << std::endl;
        }
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      i++;
    }
  }

  void start(void) {
    main_thread_ = std::thread( [=] { run(); } );
    main_thread_.join();
  }

 private:
  std::vector<std::function<void()>> step_callbacks_;
  std::mutex mutex_;
  std::thread main_thread_;

};

