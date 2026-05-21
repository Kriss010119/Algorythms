#ifndef STRING_SORT_TESTER_H
#define STRING_SORT_TESTER_H

#include <vector>
#include <string>
#include <map>

class StringSortTester {
public:
    struct SortStats {
        double time;
        int kol;
        bool isSorted;
    };
    
private:
    std::map<std::string, std::vector<std::pair<int, SortStats>>> res;
    static int cnt;
    
    void start(const std::string& test_name, int n, const SortStats& stats);
    
public:
    static bool checker(const std::string& a, const std::string& b);
    
    SortStats testQuickSort(std::vector<std::string> arr);
    SortStats testMergeSort(std::vector<std::string> arr);
    SortStats testTernarStrQuickSort(std::vector<std::string> arr);
    SortStats testStrMergeSort(std::vector<std::string> arr);
    SortStats testMSDRadixSort(const std::vector<std::string>& arr);
    SortStats testMSDRadixSortWithSwitch(const std::vector<std::string>& arr);
    
    void run();
    void save(const std::string& filename);
};

#endif