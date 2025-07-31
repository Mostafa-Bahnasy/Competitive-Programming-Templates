const int N = 300300;
const int m1 = 1e9 + 7, b1 = 17;
const int m2 = 1e9 + 9, b2 = 31;

int pw1[N], inv1[N];
int pw2[N], inv2[N];

// Double Hashing
// Computes and compares hash values of substrings with two moduli to reduce collision probability
// Time complexity: O(1) per hash query after O(n) preprocessing
// Used for: string matching, palindrome checks, substring uniqueness, hashing 2D grids
// Known problems: check equality of substrings, count distinct substrings, detect repeated substrings

void pre(int n = N) {
    pw1[0] = inv1[0] = 1;
    pw2[0] = inv2[0] = 1;

    int iv1 = inv(b1, m1);
    int iv2 = inv(b2, m2);

    for (int i = 1; i < n; i++) {
        pw1[i] = mul(pw1[i - 1], b1, m1);
        inv1[i] = mul(inv1[i - 1], iv1, m1);
        pw2[i] = mul(pw2[i - 1], b2, m2);
        inv2[i] = mul(inv2[i - 1], iv2, m2);
    }
}

struct Hashing {
    int n;
    string s;
    vector<int> h1, h2;

    Hashing(const string& s_) {
        s = s_;
        n = s.size();
        h1.resize(n), h2.resize(n);
        h1[0] = h2[0] = s[0] - '0' + 1;

        for (int i = 1; i < n; i++) {
            h1[i] = add(h1[i - 1], mul(s[i] - '0' + 1, pw1[i], m1), m1);
            h2[i] = add(h2[i - 1], mul(s[i] - '0' + 1, pw2[i], m2), m2);
        }
    }

    pair<int, int> get(int l, int r) {
        assert(l >= 0 && r < n && l <= r);
        int x = h1[r], y = h2[r];
        if (l) {
            x = mul(sub(x, h1[l - 1], m1), inv1[l], m1);
            y = mul(sub(y, h2[l - 1], m2), inv2[l], m2);
        }
        return { x, y };
    }

    static pair<int, int> concat(pair<int, int> h1, pair<int, int> h2, int h1_sz) {
        h1.first = add(h1.first, mul(h2.first, pw1[h1_sz]));
        h1.second = add(h1.second, mul(h2.second, pw2[h1_sz]));
        return h1;
    }
};
