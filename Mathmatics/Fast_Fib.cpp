int Fib(int n) { // 0, 1, 1, 2, 3, 5 | call it with(n+1) to start with 1
    ll i = 1, h = 1, j = 0, k = 0, t;
    while (n > 0) {
        if (n % 2 == 1) {
            t = (j * h) % MOD;
            j = (i * h + j * k + t) % MOD;
            i = (i * k + t) % MOD;
        }
        t = (h * h) % MOD;
        h = (2 * k * h + t) % MOD;
        k = (k * k + t) % MOD;
        n = n / 2;
    }
    return j;
}
