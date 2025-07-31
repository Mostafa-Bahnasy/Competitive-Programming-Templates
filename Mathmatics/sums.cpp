/// Returns sum of integers in range [l, r]
/// sum = r*(r+1)/2 - (l-1)*l/2
ll sum(ll l, ll r) {
    assert(l <= r);
    return (r * (r + 1) / 2) - (l * (l - 1) / 2);
}


/// Returns sum of all odd numbers in [l, r]
/// Sum of first k odd numbers = k^2
ll sumOdd(ll l, ll r) {
    assert(l <= r);
    r++;
    ll x = r / 2;  // number of odd numbers ≤ r
    ll y = l / 2;  // number of odd numbers < l
    return x * x - y * y;
}
/// Returns sum of all even numbers in [l, r]
ll sumEven(ll l, ll r) {
    return sum(l, r) - sumOdd(l, r);
}
