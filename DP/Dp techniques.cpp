#include <bits/stdc++.h>
#define ll long long
#define FIO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
using namespace std;

const int N = 1e5 + 5;
const int MOD = 1e9 + 7;
const int INF = 1e9;

// ============================
// 1. Memoization (Top-Down)
// ============================
int dp_memo[N];

int fib(int n) {
    if (n <= 1) return n;
    if (dp_memo[n] != -1) return dp_memo[n];
    return dp_memo[n] = (fib(n - 1) + fib(n - 2)) % MOD;
}

// ============================
// 2. Tabulation (Bottom-Up)
// ============================
int dp_tab[N];

void solve_fib(int n) {
    dp_tab[0] = 0;
    dp_tab[1] = 1;
    for (int i = 2; i <= n; i++) {
        dp_tab[i] = (dp_tab[i - 1] + dp_tab[i - 2]) % MOD;
    }
}

// ============================
// 3. Memory Optimization (Rolling Array)
// Use when dp[i] only depends on dp[i-1], dp[i-2], etc.
// ============================
int fib_rolling(int n) {
    int a = 0, b = 1;
    for (int i = 2; i <= n; i++) {
        int c = (a + b) % MOD;
        a = b;
        b = c;
    }
    return b;
}

// ============================
// 4. Knapsack 1D Optimization
// from 2D dp[i][w] → dp[w]
// Use when only previous row is needed
// ============================
int weight[N], value[N];

int knapsack(int n, int W) {
    vector<int> dp(W + 1, 0);
    for (int i = 1; i <= n; i++) {
        for (int w = W; w >= weight[i]; w--) {
            dp[w] = max(dp[w], value[i] + dp[w - weight[i]]);
        }
    }
    return dp[W];
}

// ============================
// 5. Bitmask DP
// ============================
int tsp(int mask, int pos, vector<vector<int>>& dist, int n, vector<vector<int>>& dp) {
    if (mask == (1 << n) - 1) return dist[pos][0];
    if (dp[mask][pos] != -1) return dp[mask][pos];

    int ans = INF;
    for (int city = 0; city < n; city++) {
        if (!(mask & (1 << city))) {
            ans = min(ans, dist[pos][city] + tsp(mask | (1 << city), city, dist, n, dp));
        }
    }
    return dp[mask][pos] = ans;
}

// ============================
// 6. Tree DP (Post-order DFS)
// ============================
vector<int> tree[N];
int dp_tree[N];

int dfs(int u, int p) {
    dp_tree[u] = 1;
    for (int v : tree[u]) {
        if (v == p) continue;
        dp_tree[u] += dfs(v, u);
    }
    return dp_tree[u];
}

// ============================
// 7. State Compression via Parity
// Use dp[i % 2][...] instead of dp[i][...]
// (only two layers kept in memory)
// ============================
int compress_dp_parity(int n, int m) {
    vector<vector<int>> dp(2, vector<int>(m + 1));
    for (int i = 0; i <= m; i++) dp[0][i] = 1; // base case
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i % 2][j] = j == 0 ? 1 : (dp[i % 2][j - 1] + dp[(i - 1) % 2][j]) % MOD;
        }
    }
    return dp[n % 2][m];
}
