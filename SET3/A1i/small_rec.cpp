#include <iostream>
#include <vector>
#include <random>
#include <cmath>

bool isInCircle(double x1, double y1, double r, double x, double y) {
    return (x - x1) * (x - x1) + (y - y1) * (y - y1) <= r * r;
}

int main () {
    double x1 = 1.0; 
    double y1 = 1.0; 
    double r1 = 1.0;

    double x2 = 1.5; 
    double y2 = 2.0; 
    double r2 = sqrt(5.0) / 2.0;

    double x3 = 2.0; 
    double y3 = 1.5; 
    double r3 = sqrt(5.0) / 2.0;

    double minX = std::max(std::max(x1 - r1, x2 - r2), x3 - r3);
    double maxX = std::min(std::min(x1 + r1, x2 + r2), x3 + r3);
    double minY = std::max(std::max(y1 - r1, y2 - r2), y3 - r3);
    double maxY = std::min(std::min(y1 + r1, y2 + r2), y3 + r3);

    if (minX >= maxX || minY >= maxY) {
        minX = 1.0;
        maxX = 2.0;
        minY = 1.0;
        maxY = 2.0;
    }

    double exact = 0.25 * M_PI + 1.25 * asin(0.8) - 1;
    std::cout << "Точная площадь: " << exact << std::endl;
    std::cout << "Узкая область: [" << minX << ", " << maxX << "] x [" << minY << ", " << maxY << "]" << std::endl;
    std::cout << "N,ApproximateArea,RelativeError" << std::endl;

    std::random_device rnd;
    std::mt19937 gen(rnd());

    std::uniform_real_distribution<> distr_x(minX, maxX);
    std::uniform_real_distribution<> distr_y(minY, maxY);

    for (int N = 100; N <= 100000; N += 500) {
        double M = 0;
        for (int j = 0; j < N; ++j) {
            double x = distr_x(gen);
            double y = distr_y(gen);

            if (isInCircle(x1, y1, r1, x, y) && isInCircle(x2, y2, r2, x, y) && isInCircle(x3, y3, r3, x, y)) {
                ++M;
            }
        }
        double Srec = std::abs((maxX - minX) * (maxY - minY));
        double S = (M / N) * Srec;
        double relativeError = std::abs(S - exact) / exact;
        
        std::cout << N << "," << S << "," << relativeError << std::endl;
    }
    
    return 0;
}