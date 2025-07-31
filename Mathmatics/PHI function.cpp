/// Computes Euler's Totient Function φ(n)
/// φ(n) = number of integers ≤ n that are coprime with n
/// Time Complexity: O(√n)
ll phi(ll n) {
    ll res = n;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;
            res -= res / i;
        }
    }
    if (n > 1)
        res -= res / n;  // For any remaining prime factor > sqrt(n)
    return res;
}



const int N = 1e5 + 5;
int phi[N];

/// Precomputes φ(1...N) using a sieve
/// Time Complexity: O(N log log N)
void computeTotients() {
    for (int i = 0; i < N; i++) phi[i] = i;
    for (int i = 2; i < N; i++) {
        if (phi[i] == i) {  // i is prime
            for (int j = i; j < N; j += i)
                phi[j] -= phi[j] / i;
        }
    }
}
