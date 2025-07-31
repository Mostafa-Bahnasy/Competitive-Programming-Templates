#include <bits/stdc++.h>
using namespace std;

#define int long long

const int MAX = 1e6 + 5;

int sp[MAX];        // Smallest Prime Factor for each number
int cnt[MAX];       // Count of numbers divisible by a certain product of primes
int sz[MAX];        // Number of prime factors in each product (bitmask subset size)

// Precomputes the smallest prime factor for all numbers up to MAX using sieve
void Sieve() {
    for (int i = 2; i < MAX; i += 2)
        sp[i] = 2; // even numbers have smallest prime factor 2
    for (int i = 3; i < MAX; i += 2) {
        if (!sp[i]) {
            sp[i] = i;
            for (int j = i * i; j < MAX; j += 2 * i) {
                if (!sp[j]) sp[j] = i;
            }
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Sieve();

    int n;
    cin >> n;

    vector<int> a(n);
    for (int &x : a) cin >> x;

    // Total number of unordered pairs is n * (n - 1) / 2
    int total_pairs = n * (n - 1) / 2;

    // Count how many numbers share any common prime factor
    for (int x : a) {
        vector<int> primes;
        // Factor x using smallest prime factor sieve
        while (x > 1) {
            int p = sp[x];
            primes.push_back(p);
            while (x % p == 0) x /= p;
        }

        int m = primes.size();
        int mask_limit = (1 << m);

        // For every non-empty subset of prime factors (inclusion-exclusion)
        for (int mask = 1; mask < mask_limit; ++mask) {
            int prod = 1, bits = 0;
            for (int i = 0; i < m; ++i) {
                if (mask & (1 << i)) {
                    prod *= primes[i];
                    ++bits;
                }
            }
            ++cnt[prod];
            sz[prod] = bits;
        }
    }

    // Apply inclusion-exclusion to subtract pairs with GCD > 1
    for (int i = 2; i < MAX; ++i) {
        if (cnt[i] == 0) continue;

        // cnt[i] choose 2 = number of unordered pairs sharing this common product
        int add = cnt[i] * (cnt[i] - 1) / 2;

        if (sz[i] % 2 == 1)
            total_pairs -= add; // subtract if odd number of prime factors
        else
            total_pairs += add; // add if even number of prime factors
    }

    cout << total_pairs << '\n';
    return 0;
}
