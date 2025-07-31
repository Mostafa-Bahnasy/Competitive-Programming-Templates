#include <bits/stdc++.h>
using namespace std;

/*
    Randomized Rabin-Karp
    Uses random base and random prime mod for rolling hash of strings
    Reduces collision probability significantly compared to fixed-base hashing
    Time: O(1) hash query after O(n) preprocessing
    Used for: comparing substrings, detecting duplicates, pattern matching
*/

long long rng() {
    // Generates a 64-bit random number using Mersenne Twister
    static mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<long long>(0, LLONG_MAX)(gen);
}

int binpower(int base, int pw, int mod) {
    // Fast exponentiation modulo mod (O(log pw))
    int ret = 1;
    while (pw) {
        if (pw & 1)
            ret = (1LL * ret * base) % mod;
        base = (1LL * base * base) % mod;
        pw /= 2;
    }
    return ret;
}

bool probablyPrimeFermat(int n, int iter = 5) {
    // Fermat primality test: probabilistic, fast for large numbers
    if (n < 4)
        return n == 2 || n == 3;

    for (int i = 0; i < iter; i++) {
        int a = 2 + rand() % (n - 3); // random base for test
        if (binpower(a, n - 1, n) != 1)
            return false; // definitely composite
    }
    return true; // probably prime
}

vector<long long> generate_primes(long long l, long long r) {
    // Collects probably-prime numbers in range [l, r]
    vector<long long> ret;
    for (int i = l; i <= r; i++) {
        if (probablyPrimeFermat(i))
            ret.push_back(i);
    }
    return ret;
}

int gen_mod() {
    // Picks a random prime in range [1e9, 1e9 + 5000]
    int l = 1000000000 + rng() % 1000000000;
    vector<long long> primes = generate_primes(l, l + 5000);
    return primes[rng() % primes.size()];
}

int base, mod;
vector<int> pw, h;

void init_hash(const string& s) {
    // Initializes prefix hashes and powers of base
    // base: random in [256, 555], mod: large prime from gen_mod
    int n = s.size();
    base = 256 + rng() % 300;
    mod = gen_mod();

    pw.resize(n + 1);
    h.resize(n + 1);
    pw[0] = 1;
    for (int i = 1; i <= n; i++) {
        pw[i] = 1LL * pw[i - 1] * base % mod;
        h[i] = (1LL * h[i - 1] * base + s[i - 1]) % mod;
    }
}

int get_hash(int l, int r) {
    // Computes hash of substring s[l..r] in O(1)
    // Valid only after calling init_hash
    int res = (h[r + 1] - 1LL * h[l] * pw[r - l + 1]) % mod;
    if (res < 0) res += mod;
    return res;
}
