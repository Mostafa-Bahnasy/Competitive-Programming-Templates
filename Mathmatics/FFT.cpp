#include <bits/stdc++.h>
using namespace std;

// Fast Fourier Transform for polynomial multiplication
#define int long long // 64-bit integers for handling large coefficients
using cd = complex<double>; // Complex numbers for FFT
const double PI = acos(-1); // Pi constant for angle calculations

// Performs the FFT or inverse FFT on array `a`
void fft(vector<cd> & a, bool invert) {
    int n = a.size();

    // Bit-reversal permutation to order elements before FFT
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;
        if (i < j)
            swap(a[i], a[j]);
    }

    // Cooley-Tukey FFT algorithm
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang)); // root of unity
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }

    // Divide all values by `n` if doing inverse FFT
    if (invert) {
        for (cd & x : a)
            x /= n;
    }
}

// Multiplies two integer polynomials `a` and `b` using FFT
// Returns a new vector with the result of the multiplication
vector<int> multiply(vector<int> const& a, vector<int> const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    // Find power of 2 size large enough to hold the result
    while (n < a.size() + b.size())
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    // Forward FFT
    fft(fa, false);
    fft(fb, false);

    // Point-wise multiplication of transformed values
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];

    // Inverse FFT to get the result back in time domain
    fft(fa, true);

    // Round real part to get integer coefficients
    vector<int> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real());
    return result;
}
