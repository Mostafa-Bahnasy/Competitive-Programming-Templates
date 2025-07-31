// SPFA (Shortest Path Faster Algorithm)
// Solves single-source shortest paths on graphs with negative edge weights (but no negative cycles)
// Detects negative cycles and supports path reconstruction

const int INF = 1e18;
int n; // number of nodes
vector<vector<pair<int, int>>> adj; // adj[u] = {v, weight}
vector<int> dist, par, cnt;
vector<bool> inq;

bool spfa(int src) {
    dist.assign(n, INF);
    par.assign(n, -1);
    cnt.assign(n, 0);
    inq.assign(n, false);

    queue<int> q;
    dist[src] = 0;
    q.push(src);
    inq[src] = true;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        inq[u] = false;

        for (auto [v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                par[v] = u;
                if (!inq[v]) {
                    q.push(v);
                    inq[v] = true;
                    cnt[v]++;
                    if (cnt[v] > n) return false; // negative cycle detected
                }
            }
        }
    }
    return true; // no negative cycles
}

// Use par[] to reconstruct shortest path from src to any node:
// vector<int> path;
// for (int v = dest; v != -1; v = par[v]) path.push_back(v);
// reverse(path.begin(), path.end());
