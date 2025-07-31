// Closest Pair of Points in 2D Plane — O(n log n)
// Returns the **squared distance** between the closest pair (to avoid floating point errors)
// Input: Vector of points as pairs (x, y)
// Assumes: All points are unique

long long ClosestPair(vector<pair<int, int>> pts) {
    int n = pts.size();
    sort(pts.begin(), pts.end());  // Sort by x-coordinate

    set<pair<int, int>> s;  // Balanced BST ordered by y-coordinate, stores (y, x)

    long long best_dist = LLONG_MAX;
    int j = 0;

    for (int i = 0; i < n; ++i) {
        int d = ceil(sqrt(best_dist));  // Max x-distance for current best

        // Remove points too far in x from current point
        while (j < n && pts[i].first - pts[j].first >= d) {
            s.erase({ pts[j].second, pts[j].first });
            j++;
        }

        // Find points in set with y within [y-d, y+d]
        auto it1 = s.lower_bound({ pts[i].second - d, -1e9 });
        auto it2 = s.upper_bound({ pts[i].second + d, +1e9 });

        // Check only relevant candidates (in y-range)
        for (auto it = it1; it != it2; ++it) {
            int dx = pts[i].first - it->second;
            int dy = pts[i].second - it->first;
            best_dist = min(best_dist, 1LL * dx * dx + 1LL * dy * dy);
        }

        // Insert current point into set for future comparisons
        s.insert({ pts[i].second, pts[i].first });
    }

    return best_dist;  // Returns the squared minimum distance
}
