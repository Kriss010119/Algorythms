#include <string>
#include <vector>
#include <random>
#include <functional>

class RandomStreamGen {
public:
    std::mt19937 rnd;
    std::uniform_int_distribution<int> ch;
    std::uniform_int_distribution<int> len;
    std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-";
    

    RandomStreamGen(int x = 13) : 
        rnd(x),
        ch(0, 62),
        len(5, 30) {
    }
    
    std::string generate_str() {
        int l = len(rnd);
        std::string res;
        res.reserve(l);
        
        for (int i = 0; i < l; ++i) {
            res += alphabet[ch(rnd)];
        }
        
        return res;
    }
    
    std::vector<std::string> generate(size_t n) {
        std::vector<std::string> s;
        s.reserve(n);
        
        for (size_t i = 0; i < n; ++i) {
            s.push_back(generate_str());
        }
        
        return s;
    }
    
    std::vector<std::vector<std::string>> split(std::vector<std::string>& s, std::vector<double>& percent) { 
        std::vector<std::vector<std::string>> v;
        v.reserve(percent.size());
        
        for (double p : percent) {
            size_t end = static_cast<size_t>(s.size() * p / 100.0);
            std::vector<std::string> p(s.begin(), s.begin() + end);
            v.push_back(p);
        }
        return v;
    }
};