#include <algorithm>
#include <iostream>
#include <chrono>

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
using namespace std::chrono;

int main() {
    double x = 0;
    double y = 0;
    constexpr double maxY = 10.000;
    bool isUp = true;
    constexpr int hz = 250;
    time_point<high_resolution_clock> start = high_resolution_clock::now();
    time_point<high_resolution_clock> movementTime = high_resolution_clock::now();

    constexpr int msPerTick = 1000000 / hz;
    while (true) {
        constexpr int switchDirectionTime = 5;
        if (duration_cast<microseconds>(high_resolution_clock::now() - movementTime).count() > msPerTick) {
            if (isUp) {
                if (y < maxY) {
                    y += 0.001;
                }
            } else {
                if (y > 0) {
                    y -= 0.001;
                }
            }
            y = std::ranges::clamp(y, static_cast<double>(0), maxY);
            movementTime += microseconds(msPerTick);
        }

        if (auto duration = duration_cast<seconds>(high_resolution_clock::now() - start); duration.count() > switchDirectionTime) {
            isUp = !isUp;
            start = high_resolution_clock::now();
        }
        std::cout << x << " " << y << " " << isUp << std::endl;
    }

    return 0;
}
