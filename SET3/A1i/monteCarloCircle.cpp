#include <iostream>
#include <vector>
#include <random>
#include <cmath>

bool isInCircle(double x1, double y1, double r, double x, double y) {
    return (x - x1) * (x - x1) + (y - y1) * (y - y1) <= r * r;
}

int main () {
    double x1 = 0; 
    double y1 = 0; 
    double r1 = 0;

    double x2 = 0; 
    double y2 = 0; 
    double r2 = 0;

    double x3 = 0; 
    double y3 = 0; 
    double r3 = 0;

    double minX = 0;
    double minY = 0;
    double maxX = 0;
    double maxY = 0;

    double res = 0;
    double cnt = 0;

    std::random_device rnd;
    std::mt19937 gen(rnd());

    std::cin >> x1 >> y1 >> r1;
    std::cin >> x2 >> y2 >> r2;
    std::cin >> x3 >> y3 >> r3;

    minX = std::min(std::min(x1 - r1, x2 - r2), x3 - r3);
    maxX = std::max(std::max(x1 + r1, x2 + r2), x3 + r3);
    minY = std::min(std::min(y1 - r1, y2 - r2), y3 - r3);
    maxY = std::max(std::max(y1 + r1, y2 + r2), y3 + r3);

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
        res += S;
        cnt += 1;
    }
    
    std:: cout << res / cnt;
    return 0;
}


#include <iostream>
#include <vector>
#include <random>
#include <cmath>

bool isInCircle(double x1, double y1, double r, double x, double y) {
    return (x - x1) * (x - x1) + (y - y1) * (y - y1) <= r * r;
}

int main () {
    double x1 = 0; 
    double y1 = 0; 
    double r1 = 0;

    double x2 = 0; 
    double y2 = 0; 
    double r2 = 0;

    double x3 = 0; 
    double y3 = 0; 
    double r3 = 0;

    double minX = 0;
    double minY = 0;
    double maxX = 0;
    double maxY = 0;

    double res = 0;
    double cnt = 0;

    std::random_device rnd;
    std::mt19937 gen(rnd());

    std::cin >> x1 >> y1 >> r1;
    std::cin >> x2 >> y2 >> r2;
    std::cin >> x3 >> y3 >> r3;

    minX = std::min(std::min(x1 - r1, x2 - r2), x3 - r3);
    maxX = std::max(std::max(x1 + r1, x2 + r2), x3 + r3);
    minY = std::min(std::min(y1 - r1, y2 - r2), y3 - r3);
    maxY = std::max(std::max(y1 + r1, y2 + r2), y3 + r3);

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
        res += S;
        cnt += 1;
    }
    
    std:: cout << res / cnt;
    return 0;
}