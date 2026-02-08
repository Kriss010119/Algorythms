#include <string>
#include <functional>

typedef unsigned int uint;

class HashFuncGen {
public:
    uint seed;

    HashFuncGen(uint s = 13) : seed(s) {}
    
    uint murmur_hash(const std::string& s) {
        uint c1 = 0xcc9e2d51;
        uint c2 = 0x1b873593;
        uint r1 = 15;
        uint r2 = 13;
        uint m = 5;
        uint n = 0xe6546b64;
        uint h = seed;
        size_t l = s.length();
        
        for (size_t i = 0; i < l; i += 4) {
            uint k = 0;
            for (int j = 0; j < 4 && (i + j) < l; ++j) {
                k |= (static_cast<uint>(s[i + j]) << (8 * j));
            }
            k *= c1;
            k = (k << r1) | (k >> (32 - r1));
            k *= c2;
            h ^= k;
            h = (h << r2) | (h >> (32 - r2));
            h = h * m + n;
        }
        
        h ^= l;
        h ^= h >> 16;
        h *= 0x85ebca6b;
        h ^= h >> 13;
        h *= 0xc2b2ae35;
        h ^= h >> 16;
        return h;
    }
};