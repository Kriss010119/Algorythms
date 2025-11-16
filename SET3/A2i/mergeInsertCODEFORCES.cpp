#include <iostream>
#include <vector>
#include <cmath>
#include <random>

void insertionSort(std::vector<int>& arr, int l, int r) {
    for (int i = l + 1; i <= r; ++i) {
        int j = i - 1;
        int el = arr[i];

        while (el < arr[j]) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = el;
    }
}

void merge(std::vector<int> &arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int k = l;
    
    std::vector<int> v1(n1);
    std::vector<int> v2(n2);
    
    for (int i = 0; i < n1; ++i) {
        v1[i] = arr[l + i];
    }
    for (int i = 0; i < n2; ++i) {
        v2[i] = arr[m + 1 + i];
    }
    
    int i = 0;
    int j = 0;
    while (i < n1 && j < n2) {
        if (v1[i] < v2[j]) {
            arr[k] = v1[i];
            ++i;
        } else {
            arr[k] = v2[j];
            ++j;
        }
        ++k;
    }
    
    while (i < n1) {
        arr[k] = v1[i];
        ++i;
        ++k;
    }
    
    while (j < n2) {
        arr[k] = v2[j];
        ++j;
        ++k;
    }
}

void mergeSort(std::vector<int> &arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void hybridMergeSort(std::vector<int>& arr, int l, int r, int k) {
    if (r - l + 1 < k) {
        insertionSort(arr, l, r);
        return;
    }

    mergeSort(arr, l, r);
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);

    int n = 0;
    std::cin >> n;
    std::vector<int> v(n, 0);

    for(auto &el: v) {
        std::cin >> el;
    }

    hybridMergeSort(v, 0, n - 1, 15);

    for (int i = 0; i < n; ++i) {
        std::cout << v[i] << ' ';
    }
    return 0;
}

