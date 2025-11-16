#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
#include <chrono>

class ArrayGenerator {
private:
    std::random_device rnd;

public:
    std::mt19937 gen;
    ArrayGenerator() : gen(rnd()) {}

    std::vector<int> genRandArr(int n, int mini = 0, int maxi = 100000) {
        std::vector<int> arr(n);
        std::uniform_int_distribution<int> dist(mini, maxi);
        for (int i = 0; i < n; ++i) {
            arr[i] = dist(gen);
        }
        return arr;
    }

    std::vector<int> genRevArr(int n) {
        std::vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            arr[i] = n - i;
        }
        return arr;
    }

    std::vector<int> genSortedArr(int n, int c = 10) {
        std::vector<int> arr(n);
        std::uniform_int_distribution<int> dist(0, n - 1);
        for (int i = 0; i < n; ++i) {
            arr[i] = i;
        }
        for (int i = 0; i < c; ++i) {
            int i1 = dist(gen);
            int i2 = dist(gen);
            std::swap(arr[i1], arr[i2]);
        }
        return arr;
    }
};

class SortTester {
private:
    ArrayGenerator generator;

public: 
    void insertionSort(std::vector<int>& arr, int l, int r) {
        for (int i = l + 1; i <= r; ++i) {
            int key = arr[i];
            int j = i - 1;
            
            while (j >= l && arr[j] > key) {
                arr[j + 1] = arr[j];
                --j;
            }
            arr[j + 1] = key;
        }
    }

    void heapify(std::vector<int>& a, int st, int end, int offset) {
        int k = st;
        int l = 2 * st + 1;
        int r = 2 * st + 2;
        if (l < end && a[offset + l] > a[offset + k]) {
            k = l;
        }
        if (r < end && a[offset + r] > a[offset + k]) {
            k = r;
        }
        if (k != st) {
            std::swap(a[offset + st], a[offset + k]);
            heapify(a, k, end, offset);
        }
    }

    void buildMaxHeap(std::vector<int>& a, int n, int offset) {
        for (int i = n / 2 - 1; i >= 0; --i) {
            heapify(a, i, n, offset);
        }
    }

    void heapSort(std::vector<int>& a, int l, int r) {
        int n = r - l + 1;
        buildMaxHeap(a, n, l);
        for (int i = n - 1; i > 0; i--) {
            std::swap(a[l], a[l + i]);
            heapify(a, 0, i, l);
        }
    }

    int quickHelper(std::vector<int>& arr, int l, int r) {
        std::uniform_int_distribution<int> dist(l, r);
        int randomIndex = dist(generator.gen);
        std::swap(arr[randomIndex], arr[r]);
        
        int pivot = arr[r];
        int i = l - 1;
        
        for (int j = l; j < r; j++) {
            if (arr[j] <= pivot) {
                i++;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[r]);
        return i + 1;
    }

    void quickSort(std::vector<int>& arr, int l, int r) {
        if (l < r) {
            int pi = quickHelper(arr, l, r);
            quickSort(arr, l, pi - 1);
            quickSort(arr, pi + 1, r);
        }
    }

    void hybridQHI(std::vector<int>& arr, int l, int r, int k, int maxi) {
        if (l >= r) {
            return;
        }
        if (r - l + 1 < 16) {
            insertionSort(arr, l, r);
            return;
        }
        if (k >= maxi) {
            heapSort(arr, l, r);
            return;
        }
        
        int pi = quickHelper(arr, l, r);
        hybridQHI(arr, l, pi - 1, k + 1, maxi);
        hybridQHI(arr, pi + 1, r, k + 1, maxi);
    }

    void hybridQHI(std::vector<int>& arr, int l, int r, int maxi) {
        hybridQHI(arr, l, r, 0, maxi);
    }

    long long testQuickSort(std::vector<int> arr) {
        auto start = std::chrono::high_resolution_clock::now();
        quickSort(arr, 0, arr.size() - 1);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        return std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    }

    long long testHybridHQI(std::vector<int> arr, int k) {
        auto start = std::chrono::high_resolution_clock::now();
        hybridQHI(arr, 0, arr.size() - 1, k);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        return std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    }
};

int main() {
    SortTester sorter;
    ArrayGenerator gen;
    std::vector<int> sizes;

    for (int size = 500; size <= 10000; size += 500) {
        sizes.push_back(size);
    }

    std::vector<int> thresholds = {5, 10, 20, 30, 50};
    std::vector<std::string> type_names = {"random", "reverse", "almost_sorted"};
    std::vector<std::vector<int>> test_data;
    test_data.push_back(gen.genRandArr(10000));
    test_data.push_back(gen.genRevArr(10000));
    test_data.push_back(gen.genSortedArr(10000, 10));

    std::cout << "---> quick.csv\n";
    std::cout << "type,size,algorithm,threshold,time\n";
    
    for (int i = 0; i < 3; ++i) {
        auto& data = test_data[i];

        for (int size : sizes) {
            if (size > data.size()) continue;
            
            long long quickTime = 0;
            for (int j = 0; j < 3; ++j) {
                std::vector<int> tempArr(data.begin(), data.begin() + size);
                quickTime += sorter.testQuickSort(tempArr);
            }
            std::cout << type_names[i] << "," << size << ",quick,0," << quickTime/3 << "\n";
        }
    }

    std::cout << "\n---> hibrid.csv\n";
    std::cout << "type,size,algorithm,threshold,time\n";

    for (int i = 0; i < 3; ++i) {
        auto& data = test_data[i];

        for (int size : sizes) {
            if (size > data.size()) continue;
            
            for (int k : thresholds) {
                long long hybridTime = 0;
                for (int j = 0; j < 3; ++j) { 
                    std::vector<int> tempArr(data.begin(), data.begin() + size);
                    hybridTime += sorter.testHybridHQI(tempArr, k);
                }
                std::cout << type_names[i] << "," << size << ",hybrid," << k << "," << hybridTime/3 << "\n";
            }
        }
    }
    return 0;
}