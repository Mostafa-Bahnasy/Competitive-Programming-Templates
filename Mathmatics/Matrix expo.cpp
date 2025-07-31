// Matrix Exponentiation Structure
// Useful for solving linear recurrence relations in O(k^3 * log n),
// where k is the size of the transformation matrix.
// Applications: Fibonacci nth term, DP optimizations, Path counts, etc.

struct Matrix {
    int n, m, mod; // Dimensions of the matrix and modulus for operations
    vector<vector<int>> a; // 2D matrix data

    Matrix() {}

    // Constructor: Initialize n x m matrix with all values = val
    Matrix(int n, int m, int mod, int val) : n(n), m(m), mod(mod), a(n, vector<int>(m, val)) {}

    // Matrix multiplication (modular)
    Matrix operator*(const Matrix& b) {
        Matrix res(n, b.m, mod, 0);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < b.m; ++j)
                for (int k = 0; k < m; ++k)
                    res.a[i][j] = (res.a[i][j] + 1LL * a[i][k] * b.a[k][j]) % mod;
        return res;
    }

    // Matrix exponentiation (A^e), assumes square matrix (n == m)
    // Used when applying the same transformation matrix multiple times
    Matrix operator^(int e) {
        Matrix res(n, n, mod, 0), b = *this;
        for (int i = 0; i < n; ++i)
            res.a[i][i] = 1; // Initialize res as identity matrix

        // Exponentiation by squaring
        for (; e > 0; e /= 2, b = b * b)
            if (e % 2) res = res * b;

        return res;
    }

    // Matrix addition (modular)
    // Used less often in CP, but may be useful in some DP transitions
    Matrix operator+(const Matrix& b) {
        Matrix res(n, b.m, mod, 0);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < b.m; ++j)
                for (int k = 0; k < m; ++k)
                    res.a[i][j] = (res.a[i][j] + 1LL * a[i][k] + b.a[k][j]) % mod;
        return res;
    }

    // Helper to turn matrix into diagonal matrix with 1s from position (i,j)
    // Mainly used to create identity or transition patterns
    void IdentifyD(int i, int j) {
        while (i < n && j < m) {
            a[i][j] = 1;
            i++, j++;
        }
    }

    // Utility function to print the matrix (debugging)
    void print() {
        for (auto& row : a) {
            for (auto& val : row) {
                cout << val << " ";
            }
            cout << "\n";
        }
    }
};
