vector<int> F, invF;

void pre(int n) {
    F.resize(n + 1);
    invF.resize(n + 1);

    F[0] = 1;
    for (int i = 1; i <= n; i++)
        F[i] = mul(F[i - 1], i, Mod);

    invF[n] = inv(F[n]);
    invF[0] = 1;
    for (int i = n - 1; i; --i)
        invF[i] = mul(invF[i + 1], i + 1);
}

int nCr(int n, int r) {
    if (n < r) return 0;
    return mul(F[n], mul(invF[r], invF[n - r]));
}

int nPr(int n, int r) {
    if (n < r) return 0;
    return mul(F[n], invF[n - r]);
}
