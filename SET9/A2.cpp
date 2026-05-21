#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

static void ternarSort(vector<string>& arr, int l, int r, int d, int& cnt) {
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
            swap(arr[m++], arr[i++]);
        } else if (t > v) {
            swap(arr[i], arr[n--]);
        } else {
            i++;
        }
    }
    
    ternarSort(arr, l, m - 1, d, cnt);
    if (v >= 0) {
        ternarSort(arr, m, n, d + 1, cnt);
    }
    ternarSort(arr, n + 1, r, d, cnt);
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
        ternarSort(arr, 0, n - 1, 0, cnt);
    }
    
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << "\n";
    }
    return 0;
}