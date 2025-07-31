// ===================== Fenwick Tree (Binary Indexed Tree - BIT) =====================
// ➤ Efficient structure for prefix sums and point updates.
// ➤ Time Complexity:
//     - Point update: O(log N)
//     - Prefix sum query: O(log N)
// ➤ Use Cases:
//     - Range sum queries (point update)
//     - Inversion count
//     - Frequency counters, lower_bound on prefix sums
// ➤ Note:
//     - Indexing is 0-based here
//     - Can be adapted for range updates and queries (via two BITs)
// ====================================================================================

struct FenwickTree { // zero indexed
    vector<int> bit;  // Binary Indexed Tree array
    int n;

    // Constructor: initialize BIT with size n (0-based indexing)
    FenwickTree(int n) {
        this->n = n;
        bit.assign(n, 0); // initialize with zeros
    }

    // Query prefix sum from 0 to r (inclusive)
    int sum(int r) {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    // Query range sum from l to r (inclusive)
    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    // Add `delta` to element at index `idx`
    void add(int idx, int delta) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }
};
