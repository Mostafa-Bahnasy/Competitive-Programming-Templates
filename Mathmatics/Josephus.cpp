/// Josephus Problem (Optimized Recursive Solution)
/// f(n, k): returns the position (1-based) of the survivor when every k-th person is eliminated in a circle of n people
///
/// This specific version works efficiently for the special case when `k = 2`
/// The recurrence relation and pattern of elimination allow for an optimized O(log n) solution

/// Use Cases:
/// - Game theory problems (last person standing)
/// - Problems involving circular elimination
/// - Classic recursion/dynamic programming problems
/// - System design for scheduling/elimination

/// Time Complexity: O(log n)
/// Space Complexity: O(log n) due to recursion depth

ll josephus(ll n, ll k) {
    if (n == 1) return 1;  // Base case: only one person remains

    // Case 1: If k is in the first half of people to be eliminated
    if (k <= (n + 1) / 2) {
        // If 2*k exceeds n, it wraps around the circle
        if (2 * k > n) return (2 * k) % n;
        else return 2 * k;
    }

    // Case 2: k is in the second half
    // We reduce the problem by half and recurse
    ll temp = josephus(n / 2, k - (n + 1) / 2);

    // Reconstruct position in original problem
    if (n % 2 == 1)
        return 2
