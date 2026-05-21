#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

static void msdRadixSort(vector<string>& arr, vector<string>& data, int l, int r, int d, int& cnt) {
    if (r <= l) {
        return;
    }
    
    const int n = 256;
    vector<int> v(n + 2, 0);
    
    for (int i = l; i <= r; ++i) {
        int c = (d < (int)arr[i].length()) ? arr[i][d] + 1 : 0;
        v[c + 1]++;
    }
    
    for (int r = 0; r < n + 1; ++r) {
        v[r + 1] += v[r];
    }
    
    for (int i = l; i <= r; ++i) {
        int c = (d < (int)arr[i].length()) ? arr[i][d] + 1 : 0;
        data[v[c]++] = arr[i];
    }
    
    for (int i = l; i <= r; ++i) {
        arr[i] = data[i - l];
    }
    
    for (int r = 0; r < n; ++r) {
        msdRadixSort(arr, data, l + v[r], l + v[r + 1] - 1, d + 1, cnt);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    cin.ignore();
    
    vector<string> arr(n);
    for (int i = 0; i < n; ++i) {
        getline(cin, arr[i]);
    }
    
    if (n > 0) {
        int cnt = 0;
        vector<string> data(n);
        msdRadixSort(arr, data, 0, n - 1, 0, cnt);
    }
    
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << "\n";
    }
    return 0;
}