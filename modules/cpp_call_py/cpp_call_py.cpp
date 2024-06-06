
// main.cpp
#include <pybind11/embed.h>
#include <iostream>

namespace py = pybind11;

int main() {
    py::scoped_interpreter guard{}; // Initialize the Python interpreter

    try {
        py::print("Hello, World!"); // Equivalent to Python's print()

        // Importing a Python module
        py::module sys = py::module::import("sys");
        sys.attr("path").attr("append")(".");

        // Running Python code
        py::exec(R"(
            import math
            print("Square root of 16 is", math.sqrt(16))
        )");

        // Defining and calling a Python function
        py::exec(R"(
            def add(a, b):
                return a + b
        )");

        py::object add = py::globals()["add"];
        int result = add(3, 4).cast<int>();
        std::cout << "Result of add(3, 4): " << result << std::endl;

    } catch (const py::error_already_set& e) {
        std::cerr << "Python error: " << e.what() << std::endl;
    }

    return 0;
}
