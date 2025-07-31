vector<int> Z_function(const string& s) {
    // Z-Function
    // Computes an array where Z[i] is the length of the longest substring starting from s[i] that matches the prefix of s
    // Time complexity: O(n), where n = s.size()
    // Used for: pattern matching, number of distinct substrings, string compression, border detection
    // Known problems: find pattern occurrences in text using Z(p + '#' + t), count unique substrings

    int n = s.size();
    vector<int> Z(n);
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r)
            Z[i] = min(Z[i - l], r - i + 1);
        while (i + Z[i] < n && s[Z[i]] == s[i + Z[i]])
            Z[i]++;
        if (i + Z[i] - 1 > r)
            l = i, r = i + Z[i] - 1;
    }
    return Z;
}
