#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define FIO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
using namespace std;
const int N = 5e2 + 1, INF = 1e9, mod = 1e9 + 7, LOG = 18;
int dp[2][N][N];
int Weight[N], value[N];
int pieces, capacity1, capacity2, n, m, ans;
int depe(int idx, int w1, int w2) {
    if (idx == pieces) return 0;
    int& ret = dp[idx][w1][w2];
    if (ret != -1) return ret;

    // leave
    ret = depe(idx + 1, w1, w2);

    //stock 1
    int we1 = Weight[idx] + w1 + n;
    if (we1 <= capacity1) {
        ret = max(ret, depe(idx + 1, we1, w2) + value[idx]);
    }

    //stock 2
    int we2 = Weight[idx] + w2 + m;
    if (we2 <= capacity2) {
        ret = max(ret, depe(idx + 1, w1, we2) + value[idx]);
    }

    return ret;
}

int iterative_dp() {
    for (int i = pieces - 1; i >= 0; i--) {
        int idx = i % 2;
        for (int w1 = 0; w1 <= capacity1; w1++) {
            for (int w2 = 0; w2 <= capacity2; w2++) {
                dp[idx][w1][w2] = dp[!idx][w1][w2];
                // stock 1
                int we1 = Weight[i] + w1 + n;
                if (we1 <= capacity1) {
                    dp[idx][w1][w2] = max(dp[idx][w1][w2], dp[!idx][we1][w2] + value[i]);
                }

                // stock 2
                int we2 = Weight[i] + w2 + m;
                if (we2 <= capacity2) {
                    dp[idx][w1][w2] = max(dp[idx][w1][w2], dp[!idx][w1][we2] + value[i]);
                }
                ans = max(ans, dp[idx][w1][w2]);
            }
        }
    }
    return ans;
}


