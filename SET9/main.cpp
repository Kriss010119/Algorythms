#include "StringSortTester.h"
#include <iostream>

int main() {
    std::cout << "Начали думать..." << std::endl;
    StringSortTester tester;
    tester.run();
    tester.save("sorting_res.csv");
    std::cout << "Конец. Результаты тут: sorting_res.csv";
    return 0;
}