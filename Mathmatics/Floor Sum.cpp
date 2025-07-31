// Computes the sum of floor((a * i + b) / c) for i in [0, n]
// That is: ∑_{i=0}^{n} ⌊(a*i + b)/c⌋
// Valid for all non-negative integers a, b, c, n
// Based on recursive transformation (known as [Hermite’s reduction])
// Time Complexity: O(log(a + b + c + n))

long long FloorSumAP(long long a, long long b, long long c, long long n) {
    // Base case: when a = 0 ⇒ expression reduces to ⌊b / c⌋ for each i in [0, n]
    if (a == 0)
        return (b / c) * (n + 1);

    // If a or b ≥ c, reduce the problem using integer division
    // Use linearity: floor((a*i + b)/c) = floor(a/c * i + b/c + (a%c * i + b%c)/c)
    if (a >= c || b >= c)
        return ((n * (n + 1)) / 2) * (a / c)           // ∑ i * floor(a/c)
             + (n + 1) * (b / c)                       // ∑ floor(b/c)
             + FloorSumAP(a % c, b % c, c, n);         // recurse on the remainder

    // General case: when a < c and b < c, apply transformation
    // We compute m = floor((a*n + b) / c)
    // Then use identity: 
    // ∑ floor((a*i + b)/c) = n*m - ∑ floor((c*i + (c - b - 1))/a) for i in [0, m-1]
    long long m = (a * n + b) / c;
    return m * n - FloorSumAP(c, c - b - 1, a, m - 1);
}
