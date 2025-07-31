// Treap (Cartesian Tree) implementation
// Supports fast insertion, cyclic shift, reverse in range, and query by index.
// Combines binary search tree (by implicit key = position) and heap (by random priority).
// Time Complexity per operation: O(log N) on average.

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Node structure
struct node {
    int prior, cnt, val; // prior: priority (heap), cnt: subtree size, val: stored value
    int lazy; // for lazy propagation (reversal flag)
    node *left, *right;

    node(int _val) : val(_val), prior(rand()), cnt(1), lazy(0), left(nullptr), right(nullptr) {}
    ~node() { delete left; delete right; }
};

using nodePtr = node*;

class Treap {
    nodePtr root;

    int cnt(nodePtr a) {
        return a ? a->cnt : 0;
    }

    void update(nodePtr a) {
        if (a) a->cnt = 1 + cnt(a->left) + cnt(a->right);
    }

    // Propagate the lazy reversal flag
    void pushDown(nodePtr &a) {
        if (a && a->lazy) {
            swap(a->left, a->right);
            if (a->left) a->left->lazy ^= 1;
            if (a->right) a->right->lazy ^= 1;
            a->lazy = 0;
        }
    }

    // Split treap into: [0...key] and [key+1...]
    void split(nodePtr cur, nodePtr &l, nodePtr &r, int key, int curKey = 0) {
        if (!cur) return void(l = r = nullptr);
        pushDown(cur);

        int realKey = curKey + cnt(cur->left) + 1;
        if (key >= realKey) {
            split(cur->right, cur->right, r, key, realKey);
            l = cur;
        } else {
            split(cur->left, l, cur->left, key, curKey);
            r = cur;
        }
        update(cur);
    }

    // Merge two treaps
    void merge(nodePtr &cur, nodePtr l, nodePtr r) {
        pushDown(l);
        pushDown(r);
        if (!l || !r)
            cur = l ? l : r;
        else if (l->prior > r->prior) {
            merge(l->right, l->right, r);
            cur = l;
        } else {
            merge(r->left, l, r->left);
            cur = r;
        }
        update(cur);
    }

public:
    Treap() : root(nullptr) {}
    ~Treap() { delete root; }

    // Insert value v at position pos (1-based)
    void insert(int pos, int v) {
        nodePtr a, b, c = new node(v);
        split(root, a, b, pos - 1);
        merge(a, a, c);
        merge(root, a, b);
    }

    // Cyclic right shift of subarray [l, r]
    void cyclic_shift(int l, int r) {
        nodePtr a, b, c, d;
        split(root, a, b, r);
        split(a, a, c, r - 1);
        split(a, d, a, l - 1);
        merge(a, c, a);     // bring last element to front
        merge(a, a, b);
        merge(root, d, a);
    }

    // Reverse subarray [l, r]
    void reverse(int l, int r) {
        nodePtr a, b, c;
        split(root, a, b, r);
        split(a, c, a, l - 1);
        a->lazy ^= 1;       // mark for lazy reverse
        merge(a, c, a);
        merge(root, a, b);
    }

    // Return the value at index i (1-based)
    int at(int i) {
        nodePtr cur = root;
        int curKey = cnt(cur->left) + 1;
        while (curKey != i) {
            pushDown(cur);
            if (i > curKey) {
                cur = cur->right;
                curKey += cnt(cur->left) + 1;
            } else {
                cur = cur->left;
                curKey -= cnt(cur->right) + 1;
            }
        }
        pushDown(cur);
        return cur->val;
    }
};

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
#endif
    // Input:
    // n: number of elements
    // q: number of operations
    // m: number of queries
    int n, q, m, x;
    scanf("%d %d %d", &n, &q, &m);
    Treap t;

    for (int i = 1; i <= n; ++i) {
        scanf("%d", &x);
        t.insert(i, x); // build the treap
    }

    // q operations: type 1 = cyclic shift, type 2 = reverse
    int type, l, r;
    while (q--) {
        scanf("%d %d %d", &type, &l, &r);
        if (type == 1)
            t.cyclic_shift(l, r);
        else
            t.reverse(l, r);
    }

    // m index queries
    for (int i = 0; i < m; ++i) {
        scanf("%d", &x);
        printf("%d ", t.at(x));
    }
}
