#ifndef STRING_GENERATOR_H
#define STRING_GENERATOR_H

#include <vector>
#include <string>
#include <random>
#include <algorithm>

class StringGenerator {
private:
    std::mt19937 rng;
    static const std::string ALPHABET;
    std::string generateRandomStr(int minN, int maxN);
    
public:
    StringGenerator(unsigned int seed = 42);
    
    enum ArrayType {
        RANDOM,
        REVERSE_SORTED,
        NEARLY_SORTED
    };
    
    std::vector<std::string> generateStr(int cnt, int minN = 10, int maxN = 200);
    std::vector<std::string> generateArr(int n, ArrayType type, int l = 0);
    std::vector<std::string> generateSamePref(int n, int len);
    static std::vector<std::string> getEls(const std::vector<std::string>& data, int n);
};

#endif