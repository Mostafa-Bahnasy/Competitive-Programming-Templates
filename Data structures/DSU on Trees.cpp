#include <bits/stdc++.h>
using namespace std;

// ===================== DSU on Tree (a.k.a. "Small to Large") =====================
// ➤ Solves subtree queries on trees efficiently.
// ➤ Time Complexity: O(N log N) — each node's data is added/removed at most logN times.
// ➤ Use Cases:
//      - Most frequent element in subtree
//      - Count of colors/frequencies/values in subtree
//      - Any DSU-like structure per subtree
// ➤ Approach:
//      - Use Euler Tour + subtree sizes
//      - Recursively process light children first (not keeping their data)
//      - Process heavy (big) child and keep its data
//      - Merge light children into big child data
//      - Process queries for current node
//      - If not `keep`, remove data to save memory/time
// =================================================================================

const int N = 1e5 + 5;

int sz[N], in[N];
vector<int> adj[N], e; // Euler tour traversal array

// Step 1: Preprocessing DFS — computes subtree sizes and entry times
int dfs(int u, int p) {
    sz[u] = 1;
    in[u] = e.size(); // Entry index in Euler tour
    e.push_back(u);   // Add node to Euler tour
    for (int v : adj[u]) {
        if (v != p) {
            sz[u] += dfs(v, u);
        }
    }
    return sz[u];
}

// Step 2: User-defined update function
// ➤ Modify this according to the problem:
//    - delta = +1 to add node u's data
//    - delta = -1 to remove node u's data
void update(int u, int delta) {
    // Example:
    // cnt[color[u]] += delta;
}

// Step 3: DSU on Tree logic
// ➤ Processes subtree of `u` with parent `p`
// ➤ If keep = true: keeps subtree data after processing
void dsu(int u, int p, bool keep) {
    int big = -1, max_sz = -1;

    // Identify heavy child (largest subtree)
    for (int v : adj[u]) {
        if (v != p && sz[v] > max_sz) {
            max_sz = sz[v];
            big = v;
        }
    }

    // Process all light children — don't keep their data
    for (int v : adj[u]) {
        if (v != p && v != big) {
            dsu(v, u, false);
        }
    }

    // Process heavy child — keep its data
    if (big != -1) {
        dsu(big, u, true);
    }

    // Add data from light children's subtrees
    for (int v : adj[u]) {
        if (v != p && v != big) {
            for (int i = in[v]; i < in[v] + sz[v]; ++i) {
                update(e[i], +1);
            }
        }
    }

    // Add current node's data
    update(u, +1);

    // ➤ Place subtree query logic here for node u
    // For example:
    // ans[u] = mostFrequentColor();

    // If not keeping, remove data after processing
    if (!keep) {
        for (int i = in[u]; i < in[u] + sz[u]; ++i) {
            update(e[i], -1);
        }
    }
}
