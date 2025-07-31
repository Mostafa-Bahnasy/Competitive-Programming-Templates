struct Trie {
    // Trie (Prefix Tree)
    // Supports insertion, deletion, and count of prefix/full-word occurrences
    // Time complexity per operation: O(len), where len = length of the string
    // Used for: prefix queries, string frequency counting, autocomplete, dictionary matching
    // Known problems: implement dictionary with insert/count/erase, longest prefix matching

    Trie* child[26];
    int prefCnt, endCnt;

    Trie() {
        memset(child, 0, sizeof child);
        prefCnt = endCnt = 0;
    }

    void insert(const string& s, int cnt = 1, int i = 0) {
        prefCnt += cnt;
        if (i == s.size()) {
            endCnt += cnt;
            return;
        }
        int cur = s[i] - 'a';
        if (!child[cur]) {
            child[cur] = new Trie();
        }
        child[cur]->insert(s, cnt, i + 1);
    }

    int erase(const string& s, int cnt = 1, int i = 0) {
        if (i == s.size()) {
            int minC = min(cnt, endCnt);
            endCnt -= minC;
            prefCnt -= minC;
            return minC;
        }
        int cur = s[i] - 'a';
        int minC = child[cur]->erase(s, cnt, i + 1);
        prefCnt -= minC;

        if (child[cur]->prefCnt == 0) {
            delete child[cur];
            child[cur] = nullptr;
        }
        return minC;
    }

    pair<int, int> count(const string& s, int i = 0) {
        if (i == s.size()) return { prefCnt, endCnt };
        int cur = s[i] - 'a';
        if (!child[cur]) return { 0, 0 };
        return child[cur]->count(s, i + 1);
    }
};
