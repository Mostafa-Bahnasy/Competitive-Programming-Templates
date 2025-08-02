#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define FIO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
using namespace std;
const ll N = 4e5 + 5, INF = 1e9, mod = 1e9 + 7, LOG = 23;
int n, q, timer = 1;
vector<int> adj[N];
int ancestor[N][LOG], lvl[N], in[N], out[N];
ll flat[N], value[N];

struct LCA {

    void init(int root = 1) {
        timer = 1;
        BuildAncestors(root, 0, 0);
    }

    // Precomputes in-time, out-time, level, and binary lifting table
    void BuildAncestors(int node, int par, int depth) {
        ancestor[node][0] = par;
        lvl[node] = depth;
        in[node] = timer++;  // in-time for Euler tour
        flat[in[node]] = value[node];  // store value in Euler array

        // Fill ancestor table for binary lifting
        for (int bit = 1; bit < LOG; bit++) {
            int p = ancestor[node][bit - 1];
            ancestor[node][bit] = ancestor[p][bit - 1];
        }

        for (auto& v : adj[node]) {
            if (v == par) continue;
            BuildAncestors(v, node, depth + 1);
        }
        out[node] = timer - 1; // out-time for subtree range queries
    }

    // Returns the k-th ancestor of a node using binary lifting
    int KthAncestor(int node, int k) {
        for (int bit = LOG - 1; bit >= 0; bit--) {
            if ((k >> bit) & 1) {
                node = ancestor[node][bit];
            }
        }
        return node;
    } 

    int get_kth_on_path(int u, int v, int k) { // the k-th node on the path from u to v
        int lca = get_LCA(u, v);
        int d1 = lvl[u] - lvl[lca];
        if (k <= d1)
            return KthAncestor(u, k);
        int d2 = lvl[v] - lvl[lca];
        return KthAncestor(v, d1 + d2 - k);
    }

    int get_LCA(int u, int v) {
        if (lvl[u] < lvl[v]) swap(u, v);
        // Bring u to the same level as v
        u = KthAncestor(u, lvl[u] - lvl[v]);
        if (u == v) return u;
        // Binary lift both u and v until their parents match
        for (int bit = LOG - 1; bit >= 0; bit--) {
            if (ancestor[u][bit] != ancestor[v][bit]) {
                u = ancestor[u][bit];
                v = ancestor[v][bit];
            }
        }
        return ancestor[u][0];
    }

    // Returns the distance (number of edges) between u and v
    int dis(int u, int v) {
        int lca = get_LCA(u, v);
        return lvl[u] - lvl[lca] + lvl[v] - lvl[lca];
    }

    // Returns true if u is an ancestor of v (based on Euler tour times)
    bool isAncestor(int u, int v) {
        return in[u] <= in[v] && out[v] <= out[u];
    }

} lcaTool;
