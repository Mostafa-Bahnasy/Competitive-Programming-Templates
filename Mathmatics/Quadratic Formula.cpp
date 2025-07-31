// Solves the quadratic equation ax^2 + bx + c = 0
// Returns a pair of real roots (as doubles) if they exist
// If no real roots, returns an empty optional
#include <optional>
#include <cmath>
using namespace std;

optional<pair<double, double>> Quadratic_Formula(long long a, long long b, long long c) {
    // Not a quadratic equation if a == 0
    if (a == 0) return nullopt;

    // Calculate the discriminant
    long long d = b * b - 4 * a * c;

    // No real roots if discriminant is negative
    if (d < 0) return nullopt;

    // Calculate roots using quadratic formula with real square root
    double sqrt_d = sqrt(d);
    double root1 = (-b + sqrt_d) / (2.0 * a);
    double root2 = (-b - sqrt_d) / (2.0 * a);

    return make_pair(root1, root2);
}


// USE CASE:
auto result = Quadratic_Formula(1, -3, 2); // Solves x^2 - 3x + 2 = 0
if (result) {
    auto [x1, x2] = result.value();
    cout << "Roots: " << x1 << " and " << x2 << '\n';
} else {
    cout << "No real roots.\n";
}
