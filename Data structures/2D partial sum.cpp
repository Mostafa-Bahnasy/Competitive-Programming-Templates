// ========================= 2D Difference Array + Prefix Sum =========================
// ➤ Purpose: Apply multiple rectangle updates on a 2D grid efficiently, and query point values.
// ➤ Time Complexity:
//     - update(x1,y1,x2,y2,val): O(1)
//     - calc(): O(N*M) to build final matrix
//     - access result: O(1) for any cell
// ➤ Best for:
//     - Applying many range updates in 2D (e.g., increase submatrices)
//     - Use cases: image processing, 2D simulation, grid-based accumulations
// ===================================================================================

using ll = long long;

struct partial_sum_2D {
    int n, m;
    vector<vector<ll>> upd;  // Difference array that holds lazy updates

    // Constructor: initializes an n × m 2D grid
    partial_sum_2D(int _n, int _m) {
        n = _n, m = _m;
        upd.assign(n, vector<ll>(m, 0));
    }

    // Rectangle update in range [x1, y1] to [x2, y2] by +val
    // Achieved using 2D difference array trick
    void update(int x1, int y1, int x2, int y2, ll val) {
        upd[x1][y1] += val;
        if (x2 + 1 < n) upd[x2 + 1][y1] -= val;
        if (y2 + 1 < m) upd[x1][y2 + 1] -= val;
        if (x2 + 1 < n && y2 + 1 < m) upd[x2 + 1][y2 + 1] += val;
    }

    // Finalize all updates by building prefix sums
    // After this, upd[i][j] holds the final value at cell (i, j)
    void calc() {
        // First pass: vertical prefix sum (column-wise)
        for (int i = 1; i < n; i++)
            for (int j = 0; j < m; j++)
                upd[i][j] += upd[i - 1][j];

        // Second pass: horizontal prefix sum (row-wise)
        for (int i = 0; i < n; i++)
            for (int j = 1; j < m; j++)
                upd[i][j] += upd[i][j - 1];
    }

    // Access result at cell (x, y): O(1)
    ll get(int x, int y) {
        return upd[x][y];
    }
};
