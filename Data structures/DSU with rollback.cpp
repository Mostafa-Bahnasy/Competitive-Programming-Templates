// Disjoint Set Union (Rollback version)
// Supports undoing merges — useful in offline queries, Mo's on trees, D&C on graphs

class RollbackDSU {
private:
    int n;
    vector<int> par, sz;
    stack<pair<int, int>> st; // Stack to track merge history
public:
    int components;

    RollbackDSU(int _n) : n(_n), par(_n + 5), sz(_n + 5, 1), components(_n) {
        iota(par.begin(), par.end(), 0);
    }

    int find(int u) {
        return par[u] == u ? u : find(par[u]); // No path compression for rollback support
    }

    bool unite(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return false;

        // Union by size and record the merge for undo
        if (sz[u] < sz[v]) swap(u, v);
        par[v] = u;
        sz[u] += sz[v];
        st.emplace(u, v); // Save state to undo later
        --components;
        return true;
    }

    int size(int u) {
        return sz[find(u)];
    }

    // Mark a rollback checkpoint (non-merge action)
    void checkpoint() {
        st.emplace(-1, -1);
    }

    // Undo all merges until last checkpoint
    void undo() {
        while (!st.empty() && st.top().first != -1) {
            auto [u, v] = st.top(); st.pop();
            sz[u] -= sz[v];
            par[v] = v;
            ++components;
        }
        if (!st.empty()) st.pop(); // Pop the marker
    }
};
