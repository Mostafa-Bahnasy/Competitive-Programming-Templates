

vector<int> prefix_function(const string& s) {
    // KMP Prefix Function
    // Computes the length of the longest proper prefix which is also a suffix for each prefix of the string
    // Time complexity: O(n), where n = s.size()
    // Used for: pattern matching, counting occurrences of a pattern, string periodicity
    // Known problems: find all occurrences of a pattern in text, border detection, string compression

    int n = s.size();
    vector<int> pi(n);
    for (int i = 1; i < n; ++i) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            ++j;
        pi[i] = j;
    }
    return pi;
}
