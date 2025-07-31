// Purpose:
// Efficiently answers how many numbers in range [l, r] are ≥ k.
//
// Core Use Cases (Catalan style explanation):
// 1. Range frequency queries (e.g., how many ≥ k, ≤ k, = k in [l, r])
// 2. K-th smallest/largest in a range
// 3. Range median queries
// 4. Solving static offline queries in O(log max_element) per query
//
// Time Complexity: O(log(max_element))
// Space Complexity: O(n log(max_element))


// Wavelet Tree: Count numbers ≥ k in range [l, r]

#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef long long ll;

const int N = 3e4 + 5;

struct node {
    vi arr, freq;
    int mn, mx, md;
    node *left = nullptr, *right = nullptr;

    node() {
        arr = {0};  // dummy to make it 1-indexed
    }

    // Builds the wavelet tree recursively
    void build() {
        mn = *min_element(arr.begin() + 1, arr.end());
        mx = *max_element(arr.begin() + 1, arr.end());
        if (mn == mx) return;

        freq = vi(arr.size(), 0);
        left = new node();
        right = new node();
        md = mn + (mx - mn) / 2;

        for (int i = 1; i < arr.size(); ++i) {
            if (arr[i] <= md) {
                left->arr.push_back(arr[i]);
                freq[i] = freq[i - 1] + 1;
            } else {
                right->arr.push_back(arr[i]);
                freq[i] = freq[i - 1];
            }
        }

        left->build();
        right->build();
    }

    // Returns number of elements in [s, e] that are ≥ k
    int query(int s, int e, int k) {
        if (mn == mx) return mn >= k ? (e - s + 1) : 0;

        int cnt = freq[e] - freq[s - 1];  // # elements sent to left in [s,e]
        int res = 0;

        if (k <= md) {
            // Elements in right child are ≥ k
            res += (e - s + 1) - cnt;
            if (cnt) {
                int new_s = freq[s - 1] + 1;
                int new_e = freq[e];
                res += left->query(new_s, new_e, k);
            }
        } else {
            if ((e - s + 1) - cnt) {
                int new_s = s - freq[s - 1];
                int new_e = e - freq[e];
                res = right->query(new_s, new_e, k);
            }
        }
        return res;
    }
};

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif

    int n, x;
    scanf("%d", &n);
    node root;

    for (int i = 0; i < n; ++i) {
        scanf("%d", &x);
        root.arr.push_back(x);
    }

    root.build();

    int q, s, e, k;
    scanf("%d", &q);
    while (q--) {
        scanf("%d %d %d", &s, &e, &k);
        printf("%d\n", root.query(s, e, k));
    }
}
