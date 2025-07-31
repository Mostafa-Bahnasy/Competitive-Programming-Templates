struct XorBasis {
    static const int BITS = 60; // For 64-bit numbers, use 60 to be safe
    ll basis[BITS] = {};
    int size = 0; // Number of vectors in the basis

    // Insert number into basis
    void insert(ll mask) {
        for (int i = BITS - 1; i >= 0; i--) {
            if (!(mask >> i & 1)) continue;
            if (!basis[i]) {
                basis[i] = mask;
                size++;
                return;
            }
            mask ^= basis[i];
        }
    }

    // Check if mask can be represented as XOR of basis elements
    bool canRepresent(ll mask) {
        for (int i = BITS - 1; i >= 0; i--) {
            if ((mask >> i) & 1) {
                if (!basis[i]) return false;
                mask ^= basis[i];
            }
        }
        return true;
    }

    // Get maximum XOR value possible from subset of basis
    ll getMaxXor() {
        ll res = 0;
        for (int i = BITS - 1; i >= 0; i--) {
            if ((res ^ basis[i]) > res) {
                res ^= basis[i];
            }
        }
        return res;
    }

    // Count of distinct XORs from subsets: 2^size
    ll countDistinctXors() {
        return 1LL << size;
    }

    // Rebuild minimal basis (optional, ordered and unique)
    vector<ll> getMinimalBasis() {
        vector<ll> res;
        for (int i = BITS - 1; i >= 0; i--)
            if (basis[i]) res.push_back(basis[i]);
        return res;
    }
};
