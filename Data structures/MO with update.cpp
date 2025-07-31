// ==========================================
//   Mo's Algorithm with Updates (Offline)
// ==========================================
// ➤ Supports answering range queries (e.g., frequency/count/sum queries) with intermediate point updates.
// ➤ Time Complexity: O(Q * n^(2/3)) — Efficient when updates and queries are mixed.
// ➤ Best Use Cases: 
//   - Static array with interleaved point updates and queries.
//   - Requires all queries known in advance (offline).
// ==========================================

#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 1e5 + 5;
const int M = 2 * N;       // Upper bound on values after compression
const int blk = 2155;      // Block size ~ N^(2/3)
const int mod = 1e9 + 7;

int a[N], b[N];            // a: working array, b: snapshot array
int cnt1[M];               // Frequency of each value
int cnt2[N];               // How many numbers have a given frequency

int L = 0, R = -1, K = -1; // Pointers for Mo’s algorithm

// ==========================
//      Query Definition
// ==========================
struct Query {
    int l, r, t, idx;
    Query(int a = 0, int b = 0, int c = 0, int d = 0) : l(a), r(b), t(c), idx(d) {}
    
    // Mo's comparator with time dimension
    bool operator < (const Query &o) const {
        if (r / blk != o.r / blk) return r < o.r;
        if (l / blk != o.l / blk) return l < o.l;
        return t < o.t;
    }
} Q[N];

map<int, int> id;          // Coordinate compression
int cnt = 0;               // Compressed value count
int ans[N];                // Answer array

int p[N], nxt[N], prv[N];  // Update history: index, new value, old value

// ==========================
//     Frequency Handlers
// ==========================
void add(int x) {
    cnt2[cnt1[x]]--;
    cnt1[x]++;
    cnt2[cnt1[x]]++;
}

void del(int x) {
    cnt2[cnt1[x]]--;
    cnt1[x]--;
    cnt2[cnt1[x]]++;
}

// ==========================
//     Apply/Undo Update
// ==========================
void apply_update(int idx) {
    if (p[idx] >= L && p[idx] <= R)
        del(a[p[idx]]), add(nxt[idx]);
    a[p[idx]] = nxt[idx];
}

void undo_update(int idx) {
    if (p[idx] >= L && p[idx] <= R)
        del(a[p[idx]]), add(prv[idx]);
    a[p[idx]] = prv[idx];
}

int main() {
    int n, q;
    scanf("%d%d", &n, &q);

    // ========== Input & Compression ==========
    for (int i = 0; i < n; i++) {
        scanf("%d", a + i);
        if (!id.count(a[i]))
            id[a[i]] = cnt++;
        a[i] = id[a[i]];
        b[i] = a[i];
    }

    int qIdx = 0; // number of queries
    int ord = 0;  // number of updates

    // ========== Read Queries & Updates ==========
    while (q--) {
        int tp, l, r;
        scanf("%d", &tp);
        if (tp == 1) {
            // Query: range [l, r]
            scanf("%d%d", &l, &r);
            --l, --r;
            Q[qIdx] = Query(l, r, ord - 1, qIdx);
            qIdx++;
        } else {
            // Update: change p -> nxt
            scanf("%d%d", &p[ord], &nxt[ord]);
            --p[ord];
            if (!id.count(nxt[ord]))
                id[nxt[ord]] = cnt++;
            nxt[ord] = id[nxt[ord]];
            prv[ord] = b[p[ord]];
            b[p[ord]] = nxt[ord];
            ++ord;
        }
    }

    // ========== Process Queries ==========
    sort(Q, Q + qIdx);

    for (int i = 0; i < qIdx; i++) {
        while (L < Q[i].l) del(a[L++]);
        while (L > Q[i].l) add(a[--L]);
        while (R < Q[i].r) add(a[++R]);
        while (R > Q[i].r) del(a[R--]);

        while (K < Q[i].t) apply_update(++K);
        while (K > Q[i].t) undo_update(K--);

        // Example: answer = max frequency
        int res = 0;
        while (cnt2[res + 1] > 0) ++res;
        ans[Q[i].idx] = res;
    }

    // ========== Output Answers ==========
    for (int i = 0; i < qIdx; i++)
        printf("%d\n", ans[i]);

    return 0;
}
