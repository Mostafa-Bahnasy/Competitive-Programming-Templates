#include <bits/stdc++.h>
using namespace std;

const int VALMAX = 1e7;

int mobius[VALMAX];  // Möbius function values

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_num;
    cin >> test_num;

    // --- Möbius Function Sieve ---
    // mobius[1] is initialized to -1 due to inversion logic used here (it's usually 1 by definition)
    mobius[1] = -1;

    // Compute Möbius function using a sieve-like approach
    // This approach uses the inversion principle:
    // If mobius[i] ≠ 0, then flip its sign (alternating pattern of Möbius)
    // and update all multiples j of i by adding mobius[i] to mobius[j]
    for (int i = 1; i < VALMAX; i++) {
        if (mobius[i]) {
            mobius[i] = -mobius[i]; // Flip sign
            for (int j = 2 * i; j < VALMAX; j += i) {
                mobius[j] += mobius[i];
            }
        }
    }

    // --- Answer Queries ---
    // The key formula is:
    // Number of square-free integers ≤ n = ∑ (μ(i) × ⌊n / i²⌋), where i² ≤ n
    // This is based on Möbius inversion applied to the characteristic function of square-free numbers
    while (test_num--) {
        long long n;
        cin >> n;

        long long ans = 0;
        for (int i = 1; 1LL * i * i <= n; i++) {
            ans += mobius[i] * (n / (1LL * i * i));
        }

        cout << ans << '\n';
    }

    return 0;
}
