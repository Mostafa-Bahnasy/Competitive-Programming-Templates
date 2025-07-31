using u128 = __uint128_t;
using ll = long long;

/// Optional: Safe modular multiplication without overflow (unused here due to __uint128_t)
ll mult(ll s, ll m, ll mod) {
    if (!m) return 0;
    ll ret = mult(s, m / 2, mod);
    ret = (ret + ret) % mod;
    if (m & 1) ret = (ret + s) % mod;
    return ret;
}

/// Fast modular exponentiation (b^p mod mod)
ll fp(ll b, ll p, ll mod) {
    ll res = 1;
    b %= mod;
    while (p > 0) {
        if (p & 1)
            res = (u128)res * b % mod;
        b = (u128)b * b % mod;
        p >>= 1;
    }
    return res;
}

/// Miller–Rabin helper: checks if 'a' is a witness to 'n' being composite
bool check(ll n, ll a, ll d, ll s) {
    ll x = fp(a, d, n);  // Compute a^d % n
    if (x == 1 || x == n - 1) return false;
    for (int r = 1; r < s; r++) {
        x = (u128)x * x % n;
        if (x == n - 1) return false;
    }
    return true;
}

/// Miller–Rabin primality test (deterministic for n < 3.3e18)
bool MillerRabin(ll n) {
    if (n < 2) return false;

    // Write n-1 as 2^r * d with d odd
    ll d = n - 1;
    int r = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }

    // Witnesses for deterministic version (up to 2^64 guaranteed)
    for (ll a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (a >= n) break;       // Only use bases < n
        if (check(n, a, d, r))   // If 'a' is a witness → n is composite
            return false;
    }
    return true;  // Probably prime
}
