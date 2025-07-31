pair<vector<int>, vector<int>> manacher(const string& s) {
    // Manacher's Algorithm
    // Finds the length of the longest palindromic substring centered at each position
    // d1[i]: radius of the longest odd-length palindrome centered at i
    // d2[i]: radius of the longest even-length palindrome centered at i
    // Time complexity: O(n), where n = s.size()
    // Used for: finding all palindromic substrings, longest palindromic substring
    // Known problems: count palindromes, find longest palindromic substring in linear time

    int n = s.size();
    vector<int> d1(n); // odd-length
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 1 : min(d1[r - i + l], r - i + 1);
        while (i - k >= 0 && i + k < n && s[i - k] == s[i + k]) k++;
        d1[i] = k--;
        if (i + k > r) l = i - k, r = i + k;
    }

    vector<int> d2(n); // even-length
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 0 : min(d2[r - i + l + 1], r - i + 1);
        while (i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k]) k++;
        d2[i] = k--;
        if (i + k > r) l = i - k - 1, r = i + k;
    }

    return {d1, d2};
}
