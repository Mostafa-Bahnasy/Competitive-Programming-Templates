struct SegmentTree {
    int n;
    vector<long long> seg, lazy;

    // Constructor: Initialize with size n (array size)
    SegmentTree(int size) {
        n = size;
        seg.assign(4 * n, 0);   // segment tree
        lazy.assign(4 * n, 0);  // lazy propagation array
    }

    // Build the segment tree from input array `arr`
    // node: current node index in seg[], [l, r] is the range it covers
    void build(const vector<long long>& arr, int node, int l, int r) {
        if (l == r) {
            seg[node] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(arr, node * 2, l, mid);
        build(arr, node * 2 + 1, mid + 1, r);
        seg[node] = seg[node * 2] + seg[node * 2 + 1];
    }

    // Pushes lazy value at node to its children (if not a leaf)
    // Updates seg[node] and pushes the pending updates down
    void push(int ind, int low, int high) {
        if (lazy[ind] != 0) {
            seg[ind] += (high - low + 1) * lazy[ind];  // apply update
            if (low != high) {  // not a leaf -> push to children
                lazy[2 * ind + 1] += lazy[ind];
                lazy[2 * ind + 2] += lazy[ind];
            }
            lazy[ind] = 0;  // clear the current node's lazy
        }
    }

    // Range increment update: add `val` to range [l, r]
    void rangeUpdate(int ind, int low, int high, int l, int r, long long val) {
        push(ind, low, high);  // apply any pending updates

        // No overlap
        if (r < low || l > high || low > high) return;

        // Complete overlap: apply and propagate lazily
        if (l <= low && high <= r) {
            seg[ind] += (high - low + 1) * val;
            if (low != high) {
                lazy[2 * ind + 1] += val;
                lazy[2 * ind + 2] += val;
            }
            return;
        }

        // Partial overlap: go deeper
        int mid = (low + high) / 2;
        rangeUpdate(2 * ind + 1, low, mid, l, r, val);
        rangeUpdate(2 * ind + 2, mid + 1, high, l, r, val);
        seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
    }

    // Query sum in range [l, r] with lazy propagation
    long long querySumLazy(int ind, int low, int high, int l, int r) {
        push(ind, low, high);  // apply any pending updates

        // No overlap
        if (r < low || l > high || low > high) return 0;

        // Complete overlap
        if (l <= low && high <= r) return seg[ind];

        // Partial overlap
        int mid = (low + high) / 2;
        return querySumLazy(2 * ind + 1, low, mid, l, r) +
            querySumLazy(2 * ind + 2, mid + 1, high, l, r);
    }

    // Point update: set arr[idx] = val
    void update(int node, int l, int r, int idx, long long val) {
        if (l == r) {
            seg[node] = val;
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid) update(node * 2, l, mid, idx, val);
        else update(node * 2 + 1, mid + 1, r, idx, val);
        seg[node] = seg[node * 2] + seg[node * 2 + 1];
    }

    // Range query (without lazy) for verification or fallback
    long long query(int node, int l, int r, int ql, int qr) {
        if (ql > r || qr < l || r < l) return 0;
        if (ql <= l && qr >= r) return seg[node];
        int mid = (l + r) / 2;
        long long query1 = query(node * 2, l, mid, ql, qr);
        long long query2 = query(node * 2 + 1, mid + 1, r, ql, qr);
        return (query1 + query2);
    }
};
