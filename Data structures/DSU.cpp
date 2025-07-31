// Disjoint Set Union (Union-Find) with path compression and union by size
// Used to manage disjoint sets efficiently (e.g., Kruskal's MST, connectivity queries, cycle detection)
// Time Complexity: Nearly constant amortized per operation, O(α(N)), where α is inverse Ackermann

struct DSU {
    vector<int> par, sz;
    int groups; // Number of current disjoint sets

    DSU(int n) : par(n + 1), sz(n + 1, 1), groups(n) {
        iota(par.begin(), par.end(), 0); // Initialize each node as its own parent
    }

    int find(int u) {
        return par[u] == u ? u : par[u] = find(par[u]); // Path compression
    }

    bool unite(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return false; // Already in same group
        if (sz[v] > sz[u]) swap(u, v); // Union by size
        par[v] = u;
        sz[u] += sz[v];
        --groups;
        return true;
    }

    int size(int u) {
        return sz[find(u)]; // Size of the set containing u
    }
};
