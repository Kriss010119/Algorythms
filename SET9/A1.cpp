#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

static void strMergeSort(vector<string>& arr, int l, int r, int& cnt) {
    if (l >= r) {
        return;
    }
    
    int mid = l + (r - l) / 2;
    strMergeSort(arr, l, mid, cnt);
    strMergeSort(arr, mid + 1, r, cnt);
    
    auto helper = [&](const string& a, const string& b) -> int {
        int n = min(a.length(), b.length());
        int i = 0;
        while (i < n && a[i] == b[i]) {
            cnt++;
            i++;
        }
        if (i < n) {
            cnt++;
        }
        return i;
    };
    
    int k = 0;
    int i = l;
    int j = mid + 1;
    int h_i = 0;
    int h_j = 0;
    vector<string> t(r - l + 1);
    
    while (i <= mid && j <= r) {
        if (h_i == h_j) {
            int el = helper(arr[i], arr[j]);
            if (el < (int)arr[i].length() && el < (int)arr[j].length()) {
                if (arr[i][el] < arr[j][el]) {
                    t[k++] = arr[i++];
                    h_i = (i <= mid) ? helper(arr[i-1], arr[i]) : 0;
                    h_j = el;
                } else {
                    t[k++] = arr[j++];
                    h_j = (j <= r) ? helper(arr[j-1], arr[j]) : 0;
                    h_i = el;
                }
            } else {
                if (arr[i].length() <= arr[j].length()) {
                    t[k++] = arr[i++];
                    h_i = (i <= mid) ? helper(arr[i-1], arr[i]) : 0;
                    h_j = el;
                } else {
                    t[k++] = arr[j++];
                    h_j = (j <= r) ? helper(arr[j-1], arr[j]) : 0;
                    h_i = el;
                }
            }
        } else if (h_i > h_j) {
            t[k++] = arr[i++];
            h_i = (i <= mid) ? helper(arr[i-1], arr[i]) : 0;
        } else {
            t[k++] = arr[j++];
            h_j = (j <= r) ? helper(arr[j-1], arr[j]) : 0;
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
        strMergeSort(arr, 0, n - 1, cnt);
    }

    for (int i = 0; i < n; ++i) {
        cout << arr[i] << "\n";
    }
    return 0;
}