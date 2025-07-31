using ll = long long;

ll MOD = 1e9+7;
std::vector<ll> fac, inv, finv;

// Precompute factorials and their inverses up to n
void init_combinatorics(int n, ll mod) {
    MOD = mod;
    fac.resize(n + 1);
    inv.resize(n + 1);
    finv.resize(n + 1);

    fac[0] = finv[0] = 1;
    inv[1] = finv[1] = 1;

    for (int i = 1; i <= n; ++i) fac[i] = fac[i - 1] * i % MOD;
    for (int i = 2; i <= n; ++i) inv[i] = MOD - MOD / i * inv[MOD % i] % MOD;
    for (int i = 2; i <= n; ++i) finv[i] = finv[i - 1] * inv[i] % MOD;
}


// Modular arithmetic utilities
ll mod_add(ll a, ll b) {return (a + b) % MOD;}
ll mod_sub(ll a, ll b) {return (a - b + MOD) % MOD;}
ll mod_mul(ll a, ll b) {return a * b % MOD;}

// Fast modular exponentiation
ll power(ll base, ll exp) {
    ll result = 1;
    base %= MOD;
    while (exp) 
    {
        if (exp & 1) result = mod_mul(result,base);
        base = mod_mul(base,base);
        exp >>= 1;
    }
    return result;
}

// Modular inverse using Fermat's Little Theorem (MOD must be prime)
ll mod_inv(ll x) {return power(x, MOD - 2);}


// Compute C(n, r) = n choose r modulo MOD
ll nCr(ll n, ll r) {
    if (n < 0 || r < 0 || r > n) return 0;
    return fac[n] * finv[r] % MOD * finv[n - r] % MOD;
}

// Compute P(n, r) = n permute r modulo MOD
ll nPr(ll n, ll r) {
    if (n < 0 || r < 0 || r > n) return 0;
    return fac[n] * finv[n - r] % MOD;
}

// Catalan number: Cn = C(2n, n) / (n + 1)
ll catalan(int n) {
    return nCr(2 * n, n) * mod_inv(n + 1) % MOD;
}

// Stars and Bars: number of ways to divide n identical items into k parts
ll stars_and_bars(ll n, ll k) {
    return nCr(n + k - 1, k - 1);
}
