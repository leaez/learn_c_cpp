#include <pybind11/embed.h>
#include <pybind11/stl.h>
#include <vector>
#include <iostream>
#include <algorithm>


namespace py = pybind11;

class MotionController {
public:
    double position;
    double velocity;
    double acceleration;
    double deceleration;
    double maxVelocity;

    MotionController()
        : position(0.0), velocity(0.0), acceleration(10.0), deceleration(10.0), maxVelocity(100.0) {}

    void moveToPosition(double targetPosition, double deltaTime) {
        double distanceToTarget = targetPosition - position;
        double stoppingDistance = (velocity * velocity) / (2 * deceleration);

        if (distanceToTarget > stoppingDistance) {
            if (velocity < maxVelocity) {
                velocity += acceleration * deltaTime;
            } else {
                velocity = maxVelocity;
            }
        } else {
            if (velocity > 0) {
                velocity -= deceleration * deltaTime;
            } else {
                velocity = 0;
            }
        }
        position += velocity * deltaTime;
    }
};

void plot_waveform(const std::vector<double>& x, const std::vector<double>& y) {
    py::scoped_interpreter guard{}; // Initialize the Python interpreter

    try {
        py::module_ plt = py::module_::import("matplotlib.pyplot");

        plt.attr("plot")(x, y);
        plt.attr("xlabel")("Time");
        plt.attr("ylabel")("Amplitude");
        plt.attr("title")("Waveform");
        plt.attr("grid")(true);
        //plt.attr("legend")();
        plt.attr("legend")("['y = x^2']");
        plt.attr("show")();
    } catch (const py::error_already_set& e) {
        std::cerr << "Python error: " << e.what() << std::endl;
    }
    


}

int main() {

    double targetPosition = 1000.0;
    double deltaTime = 0.01;

    MotionController controller;
    std::vector<double> positions;
    std::vector<double> velocities;
    std::vector<double> times;

    for (double time = 0; time <= 10; time += deltaTime) {
        controller.moveToPosition(targetPosition, deltaTime);
        positions.push_back(controller.position);
        velocities.push_back(controller.velocity);
        times.push_back(time);
    }
    //print vector
    //std::copy(positions.begin(), positions.end(), std::ostream_iterator<int>(std::cout, " "));

#if 1
    plot_waveform(positions, times);

#else
    //one window tow figure
    py::scoped_interpreter guard{}; // Initialize Python interpreter
    py::module_ plt = py::module_::import("matplotlib.pyplot");

    py::object figure = plt.attr("figure")();
    py::object ax1 = figure.attr("add_subplot")(2, 1, 1);
    py::object ax2 = figure.attr("add_subplot")(2, 1, 2);

    ax1.attr("plot")(times, positions, "b-", py::arg("label") = "Position");
    ax1.attr("set_xlabel")("Time (s)");
    ax1.attr("set_ylabel")("Position");
    ax1.attr("legend")();

    ax2.attr("plot")(times, velocities, "r-", py::arg("label") = "Velocity");
    ax2.attr("set_xlabel")("Time (s)");
    ax2.attr("set_ylabel")("Velocity");
    ax2.attr("legend")();

    plt.attr("show")();
#endif

    return 0;
}
