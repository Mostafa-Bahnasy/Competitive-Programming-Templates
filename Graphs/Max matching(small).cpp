// Bipartite Maximum Matching using DFS-based Augmenting Path Algorithm
// Time Complexity: O(N * M), where N is number of nodes on left side, M is total edges
// Use Case: Matchings in bipartite graphs — job assignment, pairing problems, domino tiling, etc.

const int MX = 405;             // Max number of nodes on one side (adjustable)
vector<int> adj[MX];           // Adjacency list for left-side nodes (0-indexed)
int r[MX], l[MX];              // r[u] = right node matched to left node u, l[v] = left node matched to right node v
int vis[MX], vis_id;           // vis[] for visited check per DFS call, vis_id is incremented each DFS loop
int numR;                      // Number of left-side nodes (indexed 0 to numR-1)

// Tries to find an augmenting path starting from node `u` on the left side
bool match(int u) {
    if (vis[u] == vis_id) return false;  // Already visited in this DFS
    vis[u] = vis_id;

    for (int nxt : adj[u]) {
        // If `nxt` is unmatched or we can re-match its pair
        if (l[nxt] == -1 || match(l[nxt])) {
            l[nxt] = u;      // Match right node to left
            r[u] = nxt;      // Match left node to right
            return true;
        }
    }
    return false;  // No augmenting path found
}

// Main driver to find max matching
int runMatching() {
    int cc = 0;  // Count of matched pairs
    memset(r, -1, sizeof r);  // Unmatched initially
    memset(l, -1, sizeof l);

    for (int i = 0; i < numR; i++) {
        vis_id++;            // Fresh DFS round
        if (match(i)) cc++;  // Augmenting path found → increase match count
    }
    return cc;               // Total number of matched pairs
}
