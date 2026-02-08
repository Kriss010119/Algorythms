#include <vector>
#include <cmath>
#include <algorithm>
#include <functional>
#include <iostream>
#include <unordered_set>

typedef unsigned int uint;

class HashFuncGen;

class HyperLogLog {
public:
    int b;
    int m;
    double alpha_m;
    std::vector<uint> reg;
    std::function<uint(const std::string&)> foo;
    
    int cnt_zeros(uint x, int maxb) {
        if (x == 0) return maxb;
        int count = 0;
        while (count < maxb && ((x >> (maxb - 1 - count)) & 1) == 0) {
            ++count;
        }
        return count + 1;
    }
    
    int get_m() { 
        return m; 
    }

    int get_b() { 
        return b; 
    }

    const std::vector<uint>& get_registers() { 
        return reg; 
    }

    HyperLogLog(int bits = 8, std::function<uint(const std::string&)> hf = nullptr) : b(bits) {
        m = 1 << b;
        reg.resize(m, 0);
        
        if (m == 16) alpha_m = 0.673;
        else if (m == 32) alpha_m = 0.697;
        else if (m == 64) alpha_m = 0.709;
        else alpha_m = 0.7213 / (1.0 + 1.079 / m);
        
        if (!hf) {
            HashFuncGen h;
            foo = [h](const std::string& s) { return h.murmur_hash(s); };
        } else {
            foo = hf;
        }
    }
    
    void add(const std::string& s) {
        uint el = foo(s);
        uint i = el >> (32 - b);
        uint val = el & ((1u << (32 - b)) - 1);
        int zeroKol = cnt_zeros(val, 32 - b);
        
        if (zeroKol > reg[i]) reg[i] = zeroKol;
    }
    
    double e() {
        double sum = 0.0;
        for (int i = 0; i < m; ++i) sum += 1.0 / (1 << reg[i]);
        
        double e = alpha_m * m * m / sum;
        
        if (e <= 2.5 * m) {
            int zero_cnt = std::count(reg.begin(), reg.end(), 0);
            if (zero_cnt) e = m * log(m / (double)zero_cnt);
        }
        
        if (e > (1.0 / 30.0) * (1ULL << 32)) {
            e = -(1ULL << 32) * log(1.0 - e / (1ULL << 32));
        }
        
        return e;
    }
    
    void clear() {
        std::fill(reg.begin(), reg.end(), 0);
    }
    
    static size_t cnt_unique(const std::vector<std::string>& data) {
        std::unordered_set<std::string> s(data.begin(), data.end());
        return s.size();
    }
    
    double err_small() { 
        return 1.04 / sqrt(m); 
    }

    double err_big() { 
        return 1.3 / sqrt(m); 
    }
};