// ------------------------- Nth Root Finder -----------------------------

// Helper function to detect multiplication overflow
// Returns true if a * b would cause overflow
bool overflow(long long a, long long b) {
    long double res = static_cast<long double>(a) * b;
    if (a == 0 || b == 0 || res / b == a)
        return false;
    return true;
}

// Returns the integer `n`-th root of `x` if it exists (i.e., some integer `r` such that r^n == x)
// Otherwise returns -1
long long nth_root(long long x, int n) {
    long long l = 1, r = x, theOne = -1;

    // Binary search for the nth root
    while (l <= r) {
        long long mid = (l + r) / 2;
        long long ans = 1;
        bool ovf = false;

        // Try to compute mid^n while checking for overflow
        for (int i = 0; i < n; i++) {
            ovf |= overflow(ans, mid);
            ans *= mid;
        }

        // If exact match, we found the root
        if (ans == x) {
            theOne = mid;
            break;
        }

        // If overflow or overshoot, search left
        if (ovf || ans > x)
            r = mid - 1;
        else // else search right
            l = mid + 1;
    }

    return theOne;
}

/*
🟢 When to use:
- When you need to find an **exact** nth root of a number (e.g. cube root of 64).
- Common in number theory problems, binary search optimizations, and perfect power detection.

🔴 Limitations:
- Only finds integer roots. If the root is irrational or not exact, returns -1.
- Slower for very large x or high n due to repeated multiplication.

✅ Handles overflow safely using a helper function and long double casting.
*/
