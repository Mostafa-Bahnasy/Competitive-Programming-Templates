/// Catalan Numbers
/// The nth Catalan number Cn is the solution for:
/// 1. Balanced Parentheses: The number of correct bracket sequences with `n` opening and `n` closing brackets.
/// 2. Word Problems: Counting valid sequences of balanced words in formal language theory.
/// 3. Bracketing Problems: The number of ways to fully parenthesize an expression with `n` pairs of operands/operators.
/// 4. Binary Search Trees: The number of BSTs that can be formed with `n` distinct nodes.
/// 5. Sorted Trees: Ways to insert `n` elements into an empty BST to maintain order.
/// 6. Full Binary Trees: Number of full binary trees with `n+1` leaves.
/// 7. Triangulations of a Polygon: Ways to triangulate a convex polygon with `n+2` sides.
/// 8. Non-Crossing Handshakes: Ways `n` pairs can shake hands without crossing.
/// 9. Dyck Paths: Grid paths that never go above the diagonal.
/// 10. Stack Permutations: Valid permutations of {1...n} using a stack.
/// 11. Valid Sequences: Valid stack operation sequences for given permutation.
/// 12. Mountain Ranges: Ways to draw mountain ranges with `n` upstrokes and `n` downstrokes never going below start.
/// 13. Schroeder's Second Problem: Valid insertion of `n` pairs of parentheses maintaining balance.
/// 14. Planar Graphs: Non-crossing partitions of planar points.
/// 15. Matrix Chain Multiplication: Ways to fully parenthesize multiplication of `n+1` matrices.
/// 16. Catalan Paths: Grid paths that stay on or below the line y = x.

const int MAXN = 1e5 + 5;
const int MOD = 1e9 + 7;

/// Function to compute modular inverse using Fermat's little theorem (MOD must be prime)
ll modinv(ll a, ll mod) {
    ll res = 1;
    ll p = mod - 2;
    while (p > 0) {
        if (p & 1) res = res * a % mod;
        a = a * a % mod;
        p >>= 1;
    }
    return res;
}

/// Precompute factorials and inverse factorials for efficient Catalan number calculation
ll fact[MAXN], invfact[MAXN];

void precompute_factorials(int n) {
    fact[0] = invfact[0] = 1;
    for (int i = 1; i <= n; i++)
        fact[i] = fact[i - 1] * i % MOD;
    invfact[n] = modinv(fact[n], MOD);
    for (int i = n - 1; i >= 1; i--)
        invfact[i] = invfact[i + 1] * (i + 1) % MOD;
}

/// Returns the nth Catalan number modulo MOD
ll catalan(int n) {
    if (n == 0) return 1;
    // Cn = (2n)! / (n! * (n + 1)!)
    return fact[2 * n] * invfact[n] % MOD * invfact[n + 1] % MOD;
}
