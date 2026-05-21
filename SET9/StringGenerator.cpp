#include "StringGenerator.h"

const std::string StringGenerator::ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#%:;^&*()-";

StringGenerator::StringGenerator(unsigned int n) : rng(n) {}

std::string StringGenerator::generateRandomStr(int minN, int maxN) {
    int n = minN + (rng() % (maxN - minN + 1));
    std::string res;
    res.reserve(n);
    
    for (int i = 0; i < n; ++i) {
        res += ALPHABET[rng() % ALPHABET.size()];
    }
    
    return res;
}

std::vector<std::string> StringGenerator::generateStr(int cnt, int minN, int maxN) {
    std::vector<std::string> res;
    res.reserve(cnt);
    
    for (int i = 0; i < cnt; ++i) {
        res.push_back(generateRandomStr(minN, maxN));
    }
    
    return res;
}

std::vector<std::string> StringGenerator::generateArr(int n, ArrayType type, int l) {
    auto str = generateStr(n);
    
    switch (type) {
        case RANDOM:
            return str;
            
        case REVERSE_SORTED:
            std::sort(str.begin(), str.end(), std::greater<std::string>());
            return str;
            
        case NEARLY_SORTED: {
            std::sort(str.begin(), str.end());
            int k = std::max(1, n / 20);
            
            for (int i = 0; i < k; ++i) {
                int ind1 = rng() % n;
                int ind2 = rng() % n;
                std::swap(str[ind1], str[ind2]);
            }
            return str;
        }
    }
    
    return str;
}

std::vector<std::string> StringGenerator::generateSamePref(int n, int len) {
    std::string pref = generateRandomStr(len, len);
    std::vector<std::string> res;
    res.reserve(n);
    
    for (int i = 0; i < n; ++i) {
        res.push_back(pref + generateRandomStr(10, 200));
    }
    
    return res;
}

std::vector<std::string> StringGenerator::getEls(const std::vector<std::string>& data, int n) {
    if (n >= static_cast<int>(data.size())) {
        return data;
    }
    return std::vector<std::string>(data.begin(), data.begin() + n);
}