// Kosaraju's Algorithm for Strongly Connected Components (SCC)
// Time Complexity: O(N + M)
// Use Case: Works on directed graphs to find SCCs — used in 2-SAT, condensation DAGs, cycles detection, etc.

struct SCC {
    int n;
    vector<vector<int>> adj[2];  // adj[0]: original graph, adj[1]: reversed graph
    vector<bool> vis;
    vector<vector<int>> com;     // List of SCCs
    stack<int> stk;

    SCC(int _n) {
        n = _n;
        adj[0].resize(n + 1);
        adj[1].resize(n + 1);
    }

    void addEdge(int u, int v) {
        // Add edge u → v to original graph
        // Also add v → u to reversed graph for second DFS
        adj[0][u].push_back(v);
        adj[1][v].push_back(u);
    }

    void dfs1(int u) {
        // First DFS: used to determine finishing times
        vis[u] = true;
        for (int v : adj[0][u]) {
            if (!vis[v]) dfs1(v);
        }
        stk.push(u); // Push finished node onto stack
    }

    void dfs2(int u, vector<int>& group) {
        // Second DFS: collect all reachable nodes from u in the reversed graph
        vis[u] = true;
        group.push_back(u);
        for (int v : adj[1][u]) {
            if (!vis[v]) dfs2(v, group);
        }
    }

    void build() {
        // Step 1: Run DFS on original graph to fill stack with finish times
        vis.assign(n + 1, false);
        for (int i = 1; i <= n; i++) {
            if (!vis[i]) dfs1(i);
        }

        // Step 2: Run DFS on reversed graph in decreasing order of finish times
        vis.assign(n + 1, false);
        while (!stk.empty()) {
            int u = stk.top(); stk.pop();
            if (!vis[u]) {
                com.emplace_back();
                dfs2(u, com.back());  // Store one SCC
            }
        }
    }
};
