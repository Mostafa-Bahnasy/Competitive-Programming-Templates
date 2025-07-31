/// Extended Euclidean Algorithm
/// Solves: a * x + b * y = gcd(a, b)
/// Returns gcd(a, b) and computes x, y such that the equation holds
/// Use case: Modular inverse when gcd(a, m) == 1 → x = a⁻¹ mod m
ll extended_euclid(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    ll x1, y1;
    ll g = extended_euclid(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}
