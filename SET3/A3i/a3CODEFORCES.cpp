#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>

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

void insertionSort(std::vector<int>& arr, int l, int r) {
    for (int i = l + 1; i <= r; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= l && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

int quickHelper(std::vector<int>& arr, int l, int r) {
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

void quickSort(std::vector<int>& arr, int l, int r, int k, int maxi) {
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
    
    int m = quickHelper(arr, l, r);
    quickSort(arr, l, m - 1, k + 1, maxi);
    quickSort(arr, m + 1, r, k + 1, maxi);
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    int n = 0;
    std::cin >> n;
    int deep = 2 * static_cast<int>(log2(n));
    std::vector<int> v(n);
    for (int i = 0; i < n; i++) {
        std::cin >> v[i];
    }
    quickSort(v, 0, n - 1, 0, deep);
    for (int i = 0; i < n; i++) {
        std::cout << v[i] << " ";
    }
    return 0;
}