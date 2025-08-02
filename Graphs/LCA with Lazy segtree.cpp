#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define FIO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
using namespace std;
const ll N = 4e5 + 5, INF = 1e9, mod = 1e9 + 7, LOG = 23;
int n, q, timer = 1;
vector<int> adj[N];
int ancestor[N][LOG], lvl[N], in[N], out[N];
ll flat[N], seg[4 * N], lazy[4 * N], color[N];

struct LCA {

    void init(int root = 1) {
        timer = 1;
        BuildAncestors(root, 0, 0);
    }

    void BuildAncestors(int node, int par, int depth) {
        ancestor[node][0] = par;
        lvl[node] = depth;
        in[node] = timer++;
        flat[in[node]] = color[node];
        for (int bit = 1; bit < LOG; bit++) {
            int p = ancestor[node][bit - 1];
            ancestor[node][bit] = ancestor[p][bit - 1];
        }

        for (auto& v : adj[node]) {
            if (v == par) continue;
            BuildAncestors(v, node, depth + 1);
        }
        out[node] = timer - 1;
    }

    int KthAncestor(int node, int k) {
        for (int bit = LOG - 1; bit >= 0; bit--) {
            if ((k >> bit) & 1) {
                node = ancestor[node][bit];
            }
        }
        return node;
    }

    int get_LCA(int u, int v) {
        if (lvl[u] < lvl[v]) swap(u, v);
        u = KthAncestor(u, lvl[u] - lvl[v]);
        if (u == v) return u;
        for (int bit = LOG - 1; bit >= 0; bit--) {
            if (ancestor[u][bit] != ancestor[v][bit]) {
                u = ancestor[u][bit];
                v = ancestor[v][bit];
            }
        }
        return ancestor[u][0];
    }

    int dis(int u, int v) {
        int lca = get_LCA(u, v);
        return lvl[u] - lvl[lca] + lvl[v] - lvl[lca];
    }

    bool isAncestor(int u, int v) {
        return in[u] <= in[v] && out[v] <= out[u];
    }

} lcaTool;

struct SegmentTree {

    void build(int node, int l, int r) {
        if (l == r) {
            seg[node] = flat[l];
            return;
        }
        int mid = (l + r) / 2;
        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);
        seg[node] = (seg[node * 2] | seg[node * 2 + 1]);
    }

    void update(int node, int l, int r, int idx, int val) {
        if (l == r) {
            seg[node] = val;
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid) update(node * 2, l, mid, idx, val);
        else update(node * 2 + 1, mid + 1, r, idx, val);
        seg[node] = (seg[node * 2] | seg[node * 2 + 1]);
    }

    ll query(int node, int l, int r, int ql, int qr) {
        if (ql > r or qr < l or r < l) return 0;
        if (ql <= l and qr >= r) return seg[node];
        int mid = (l + r) / 2;
        ll query1 = query(node * 2, l, mid, ql, qr);
        ll query2 = query(node * 2 + 1, mid + 1, r, ql, qr);
        return (query1 | query2);
    }

    void rangeUpdate(int node, int l, int r, int ql, int qr, ll val) {
        // lazy propagation
        if (lazy[node] != 0) {
            seg[node] = lazy[node];
            if (l != r) {
                lazy[node * 2] = lazy[node];
                lazy[node * 2 + 1] = lazy[node];
            }
            lazy[node] = 0;
        }

        if (r < l || l > qr || r < ql) return;

        if (l >= ql and r <= qr) {
            seg[node] = val;
            if (l != r) {
                lazy[node * 2] = val;
                lazy[node * 2 + 1] = val;
            }
            return;
        }

        int mid = (l + r) / 2;
        rangeUpdate(node * 2, l, mid, ql, qr, val);
        rangeUpdate(node * 2 + 1, mid + 1, r, ql, qr, val);
        seg[node] = (seg[node * 2] | seg[node * 2 + 1]);
    }


    ll queryLazy(int node, int l, int r, int ql, int qr) {
        // lazy propagation
        if (lazy[node] != 0) {
            seg[node] = lazy[node];
            if (l != r) {
                lazy[node * 2] = lazy[node];
                lazy[node * 2 + 1] = lazy[node];
            }
            lazy[node] = 0;
        }

        if (r < l || l > qr || r < ql) return 0;

        if (l >= ql and r <= qr) return seg[node];

        int mid = (l + r) / 2;
        ll left = queryLazy(node * 2, l, mid, ql, qr);
        ll right = queryLazy(node * 2 + 1, mid + 1, r, ql, qr);
        return (left | right);
    }

    void updateSubtree(int node, ll val) {
        segtreeTool.rangeUpdate(1, 1, n, in[node], out[node], val);
    }

    ll querySubtree(int node) {
        return segtreeTool.queryLazy(1, 1, n, in[node], out[node]);
    }

} segtreeTool;
