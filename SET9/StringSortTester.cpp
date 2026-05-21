#include "StringSortTester.h"
#include "StringGenerator.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>

static void mergeSort(std::vector<std::string>& arr, int l, int r, int& cnt) {
    if (l >= r) {
        return;
    }
    
    int mid = l + (r - l) / 2;
    mergeSort(arr, l, mid, cnt);
    mergeSort(arr, mid + 1, r, cnt);
    
    std::vector<std::string> t(r - l + 1);
    int k = 0;
    int i = l;
    int j = mid + 1;

    while (i <= mid && j <= r) {
        if (StringSortTester::checker(arr[i], arr[j])) {
            t[k++] = arr[i++];
        } else {
            t[k++] = arr[j++];
        }
    }
    
    while (i <= mid) {
        t[k++] = arr[i++];
    }
    while (j <= r) {
        t[k++] = arr[j++];
    }
    
    for (int ind = 0; ind < k; ++ind) {
        arr[l + ind] = t[ind];
    }
}

static void ternarSort(std::vector<std::string>& arr, int l, int r, int d, int& cnt) {
    if (r <= l) {
        return;
    }
    
    int m = l;
    int n = r;
    int i = l + 1;
    int v = (d < (int)arr[l].length()) ? arr[l][d] : -1;
    
    while (i <= n) {
        int t = (d < (int)arr[i].length()) ? arr[i][d] : -1;
        cnt++;
        if (t < v) {
            std::swap(arr[m++], arr[i++]);
        } else {
            cnt++;
            if (t > v) {
                std::swap(arr[i], arr[n--]);
            } else {
                i++;
            }
        }
    }
    
    ternarSort(arr, l, m - 1, d, cnt);
    if (v >= 0) {
        ternarSort(arr, m, n, d + 1, cnt);
    }
    ternarSort(arr, n + 1, r, d, cnt);
}

static int lcpLength(const std::string& a, const std::string& b, int& cnt) {
    int n = std::min(a.length(), b.length());
    int i = 0;
    while (i < n && a[i] == b[i]) {
        cnt++;
        i++;
    }
    if (i < n) {
        cnt++;
    }
    return i;
}

static void strMergeSort(std::vector<std::string>& arr, int l, int r, int& cnt) {
    if (l >= r) {
        return;
    }
    
    int mid = l + (r - l) / 2;
    strMergeSort(arr, l, mid, cnt);
    strMergeSort(arr, mid + 1, r, cnt);
    
    std::vector<std::string> t(r - l + 1);
    int i = l, j = mid + 1, k = 0;
    int lcpLeft = 0, lcpRight = 0;
    
    while (i <= mid && j <= r) {
        int minLcp = std::min(lcpLeft, lcpRight);
        int cmp = 0;
        int pos = minLcp;
        int len1 = arr[i].length(), len2 = arr[j].length();
        
        while (pos < len1 && pos < len2) {
            cnt++;
            if (arr[i][pos] < arr[j][pos]) {
                cmp = -1;
                break;
            } else if (arr[i][pos] > arr[j][pos]) {
                cmp = 1;
                break;
            }
            pos++;
        }
        if (pos == len1 || pos == len2) {
            cnt++;
            if (len1 <= len2) cmp = -1;
            else cmp = 1;
        }
        
        if (cmp <= 0) {
            t[k++] = arr[i++];
            if (i <= mid) {
                lcpLeft = lcpLength(arr[i-1], arr[i], cnt);
            } else {
                lcpLeft = 0;
            }
        } else {
            t[k++] = arr[j++];
            if (j <= r) {
                lcpRight = lcpLength(arr[j-1], arr[j], cnt);
            } else {
                lcpRight = 0;
            }
        }
    }
    
    while (i <= mid) {
        t[k++] = arr[i++];
    }
    while (j <= r) {
        t[k++] = arr[j++];
    }
    
    for (int idx = 0; idx < k; ++idx) {
        arr[l + idx] = t[idx];
    }
}

static void msdRadixSort(std::vector<std::string>& arr, std::vector<std::string>& data, int l, int r, int d, int& cnt) {
    if (r <= l) {
        return;
    }
    
    const int R = 256;
    std::vector<int> count(R + 2, 0);
    
    for (int i = l; i <= r; ++i) {
        int c = (d < (int)arr[i].length()) ? arr[i][d] + 1 : 0;
        count[c + 1]++;
    }
    
    for (int ch = 0; ch < R + 1; ++ch) {
        count[ch + 1] += count[ch];
    }
    
    for (int i = l; i <= r; ++i) {
        int c = (d < (int)arr[i].length()) ? arr[i][d] + 1 : 0;
        data[count[c]++] = arr[i];
    }
    
    for (int i = l; i <= r; ++i) {
        arr[i] = data[i - l];
    }
    
    for (int ch = 0; ch < R; ++ch) {
        msdRadixSort(arr, data, l + count[ch], l + count[ch + 1] - 1, d + 1, cnt);
    }
}

static void msdRadixSortWithSwitch(std::vector<std::string>& arr, std::vector<std::string>& data, int l, int r, int d, int& cnt) {
    const int ALPHABET_SIZE = 256;
    if (r - l + 1 < ALPHABET_SIZE) {
        ternarSort(arr, l, r, d, cnt);
        return;
    }
    if (r <= l) return;
    
    std::vector<int> count(ALPHABET_SIZE + 2, 0);
    
    for (int i = l; i <= r; ++i) {
        int c = (d < (int)arr[i].length()) ? arr[i][d] + 1 : 0;
        count[c + 1]++;
    }
    
    for (int ch = 0; ch < ALPHABET_SIZE + 1; ++ch) {
        count[ch + 1] += count[ch];
    }
    
    for (int i = l; i <= r; ++i) {
        int c = (d < (int)arr[i].length()) ? arr[i][d] + 1 : 0;
        data[count[c]++] = arr[i];
    }
    
    for (int i = l; i <= r; ++i) {
        arr[i] = data[i - l];
    }
    
    for (int ch = 0; ch < ALPHABET_SIZE; ++ch) {
        msdRadixSortWithSwitch(arr, data, l + count[ch], l + count[ch + 1] - 1, d + 1, cnt);
    }
}

int StringSortTester::cnt = 0;

bool StringSortTester::checker(const std::string& a, const std::string& b) {
    int n = std::min(a.length(), b.length());
    for (int i = 0; i < n; ++i) {
        cnt++;
        if (a[i] != b[i]) {
            return a[i] < b[i];
        }
    }
    cnt++;
    return a.length() < b.length();
}

void StringSortTester::start(const std::string& name, int n, const SortStats& stats) {
    res[name].push_back({n, stats});
}

StringSortTester::SortStats StringSortTester::testQuickSort(std::vector<std::string> arr) {
    const int RUNS = 5;
    double total_time = 0;
    int total_comparisons = 0;
    bool sorted = true;
    
    for (int run = 0; run < RUNS; ++run) {
        std::vector<std::string> copy = arr;
        cnt = 0;
        clock_t st = clock();

        std::sort(copy.begin(), copy.end(), [](const std::string& a, const std::string& b) {
            return checker(a, b);
        });
        
        clock_t end = clock();
        total_time += (double)(end - st) / CLOCKS_PER_SEC * 1000.0;
        total_comparisons += cnt;
        if (!std::is_sorted(copy.begin(), copy.end())) {
            sorted = false;
        }
    }
    
    SortStats stats;
    stats.time = total_time / RUNS;
    stats.kol = total_comparisons / RUNS;
    stats.isSorted = sorted;
    return stats;
}

StringSortTester::SortStats StringSortTester::testMergeSort(std::vector<std::string> arr) {
    const int RUNS = 5;
    double total_time = 0;
    int total_comparisons = 0;
    bool sorted = true;
    
    for (int run = 0; run < RUNS; ++run) {
        std::vector<std::string> copy = arr;
        cnt = 0;
        clock_t st = clock();
        mergeSort(copy, 0, (int)copy.size() - 1, cnt);
        clock_t end = clock();
        
        total_time += (double)(end - st) / CLOCKS_PER_SEC * 1000.0;
        total_comparisons += cnt;
        if (!std::is_sorted(copy.begin(), copy.end())) {
            sorted = false;
        }
    }
    
    SortStats stats;
    stats.time = total_time / RUNS;
    stats.kol = total_comparisons / RUNS;
    stats.isSorted = sorted;
    return stats;
}

StringSortTester::SortStats StringSortTester::testTernarStrQuickSort(std::vector<std::string> arr) {
    const int RUNS = 5;
    double total_time = 0;
    int total_comparisons = 0;
    bool sorted = true;
    
    for (int run = 0; run < RUNS; ++run) {
        std::vector<std::string> copy = arr;
        cnt = 0;
        clock_t st = clock();
        ternarSort(copy, 0, (int)copy.size() - 1, 0, cnt);
        clock_t end = clock();
        
        total_time += (double)(end - st) / CLOCKS_PER_SEC * 1000.0;
        total_comparisons += cnt;
        if (!std::is_sorted(copy.begin(), copy.end())) {
            sorted = false;
        }
    }
    
    SortStats stats;
    stats.time = total_time / RUNS;
    stats.kol = total_comparisons / RUNS;
    stats.isSorted = sorted;
    return stats;
}

StringSortTester::SortStats StringSortTester::testStrMergeSort(std::vector<std::string> arr) {
    const int RUNS = 5;
    double total_time = 0;
    int total_comparisons = 0;
    bool sorted = true;
    
    for (int run = 0; run < RUNS; ++run) {
        std::vector<std::string> copy = arr;
        cnt = 0;
        clock_t st = clock();
        strMergeSort(copy, 0, (int)copy.size() - 1, cnt);
        clock_t end = clock();
        
        total_time += (double)(end - st) / CLOCKS_PER_SEC * 1000.0;
        total_comparisons += cnt;
        if (!std::is_sorted(copy.begin(), copy.end())) {
            sorted = false;
        }
    }
    
    SortStats stats;
    stats.time = total_time / RUNS;
    stats.kol = total_comparisons / RUNS;
    stats.isSorted = sorted;
    return stats;
}

StringSortTester::SortStats StringSortTester::testMSDRadixSort(const std::vector<std::string>& arr) {
    const int RUNS = 5;
    double total_time = 0;
    bool sorted = true;
    
    for (int run = 0; run < RUNS; ++run) {
        auto copy = arr;
        cnt = 0;
        clock_t st = clock();
        std::vector<std::string> data(arr.size());
        msdRadixSort(copy, data, 0, (int)arr.size() - 1, 0, cnt);
        clock_t end = clock();
        
        total_time += (double)(end - st) / CLOCKS_PER_SEC * 1000.0;
        if (!std::is_sorted(copy.begin(), copy.end())) {
            sorted = false;
        }
    }
    
    SortStats stats;
    stats.time = total_time / RUNS;
    stats.kol = 0;
    stats.isSorted = sorted;
    return stats;
}

StringSortTester::SortStats StringSortTester::testMSDRadixSortWithSwitch(const std::vector<std::string>& arr) {
    const int RUNS = 5;
    double total_time = 0;
    bool sorted = true;
    
    for (int run = 0; run < RUNS; ++run) {
        auto copy = arr;
        cnt = 0;
        clock_t st = clock();
        std::vector<std::string> data(arr.size());
        msdRadixSortWithSwitch(copy, data, 0, (int)arr.size() - 1, 0, cnt);
        clock_t end = clock();
        
        total_time += (double)(end - st) / CLOCKS_PER_SEC * 1000.0;
        if (!std::is_sorted(copy.begin(), copy.end())) {
            sorted = false;
        }
    }
    
    SortStats stats;
    stats.time = total_time / RUNS;
    stats.kol = cnt / RUNS;
    stats.isSorted = sorted;
    return stats;
}

void StringSortTester::run() {
    StringGenerator gen;
    auto random  = gen.generateArr(3000, StringGenerator::RANDOM);
    auto reverse = gen.generateArr(3000, StringGenerator::REVERSE_SORTED);
    auto nearly  = gen.generateArr(3000, StringGenerator::NEARLY_SORTED);
    
    std::cout << "Начинаем тестирование. Выполняется по 5 замеров для каждого размера..." << std::endl;
    
    for (int n = 100; n <= 3000; n += 100) {
        auto random_arr = StringGenerator::getEls(random, n);
        auto reverse_arr = StringGenerator::getEls(reverse, n);
        auto nearly_arr = StringGenerator::getEls(nearly, n);

        std::cout << "Тестирование размера n = " << n << std::endl;
        
        start("QuickSort_Random", n, testQuickSort(random_arr));
        start("MergeSort_Random", n, testMergeSort(random_arr));
        start("TernarQS_Random", n, testTernarStrQuickSort(random_arr));
        start("StrMerge_Random", n, testStrMergeSort(random_arr));
        start("MSD_Radix_Random", n, testMSDRadixSort(random_arr));
        start("MSD_Radix_QS_Random", n, testMSDRadixSortWithSwitch(random_arr));
        
        start("QuickSort_Reverse", n, testQuickSort(reverse_arr));
        start("MergeSort_Reverse", n, testMergeSort(reverse_arr));
        start("TernarQS_Reverse", n, testTernarStrQuickSort(reverse_arr));
        start("StrMerge_Reverse", n, testStrMergeSort(reverse_arr));
        start("MSD_Radix_Reverse", n, testMSDRadixSort(reverse_arr));
        start("MSD_Radix_QS_Reverse", n, testMSDRadixSortWithSwitch(reverse_arr));
        
        start("QuickSort_Nearly", n, testQuickSort(nearly_arr));
        start("MergeSort_Nearly", n, testMergeSort(nearly_arr));
        start("TernarQS_Nearly", n, testTernarStrQuickSort(nearly_arr));
        start("StrMerge_Nearly", n, testStrMergeSort(nearly_arr));
        start("MSD_Radix_Nearly", n, testMSDRadixSort(nearly_arr));
        start("MSD_Radix_QS_Nearly", n, testMSDRadixSortWithSwitch(nearly_arr));
    }
}

void StringSortTester::save(const std::string& filename) {
    std::ofstream file(filename);
    file << "Algorithm,Size,Time_ms,Comparisons,Sorted\n";
    for (const auto& [name, data] : res) {
        for (const auto& [n, stats] : data) {
            file << name << "," << n << "," << stats.time << "," << stats.kol << "," << (stats.isSorted ? "yes" : "no") << "\n";
        }
    } 
    file.close();
    std::cout << "Результаты сохранены в файл: " << filename << std::endl;
}