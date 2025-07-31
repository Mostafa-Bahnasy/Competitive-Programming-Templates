#include <bits/stdc++.h>
using namespace std;

/*
    Aho-Corasick Automaton
    Builds a trie with failure links for multiple pattern matching in O(n + m + z)
    n = sum of pattern lengths, m = text length, z = total matches found
    Used for: searching multiple patterns in text efficiently, spam filters, virus scanners
    Known problems: multi-pattern string search, counting overlapping matches
*/

const int N = 1005;  // Maximum total nodes in trie (patterns * average length)
const int M = 26;    // Alphabet size ('a' to 'z')

int trie[N][M];      // Trie transitions
int go[N][M];        // Go function with fallback (automaton)
int mrk[N];          // Mark endpoint of inserted patterns
int f[N];            // Failure function (suffix link)
int ptr = 1;         // Next unused trie node index

void BFS() {
    // Builds failure links and go transitions
    queue<int> q;
    for (int i = 0; i < M; i++) {
        if (trie[0][i]) {
            q.push(trie[0][i]);
            f[trie[0][i]] = 0;
        }
        go[0][i] = trie[0][i]; // go[0][i] initialized
    }

    while (!q.empty()) {
        int x = q.front(); q.pop();
        for (int i = 0; i < M; i++) {
            if (trie[x][i]) {
                int y = trie[x][i];
                f[y] = f[x];
                while (f[y] && !trie[f[y]][i])
                    f[y] = f[f[y]];
                if (trie[f[y]][i])
                    f[y] = trie[f[y]][i];

                mrk[y] += mrk[f[y]]; // Accumulate matches from fail links
                q.push(y);
                go[x][i] = y;
            } else {
                go[x][i] = go[f[x]][i];
            }
        }
    }
}

void ins(string x) {
    // Inserts pattern string x with value v
    int v; cin >> v;
    int cur = 0;
    for (char ch : x) {
        int c = ch - 'a';
        if (!trie[cur][c])
            trie[cur][c] = ptr++;
        cur = trie[cur][c];
    }
    mrk[cur] += v; // Mark this node as terminal with count
}
