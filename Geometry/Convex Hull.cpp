#include <bits/stdc++.h>
using namespace std;
#define int long long
 
struct Point {
    int x, y;
 
    bool operator<(const Point& p) const {
        return x < p.x || (x == p.x && y < p.y);
    }
};
 
int cross(const Point& a, const Point& b, const Point& c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}
 
bool isRightTurn(const Point& a, const Point& b, const Point& c) {
    return cross(a, b, c) < 0;
}
 
bool isLeftTurnOrColinear(const Point& a, const Point& b, const Point& c) {
    return cross(a, b, c) >= 0;
}
 
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int n;
    cin >> n;
    vector<Point> pts(n);
    for (auto& p : pts)
        cin >> p.x >> p.y;
 
    // Sort by x then y to ensure deterministic order
    sort(pts.begin(), pts.end());
 
    // Hull will be built incrementally
    vector<Point> hull;
 
    for (int i = 0; i < n; ++i) {
        // Lower hull
        while (hull.size() >= 2 && !isLeftTurnOrColinear(hull[hull.size() - 2], hull.back(), pts[i])) {
            hull.pop_back();
        }
        hull.push_back(pts[i]);
    }
 
    // Upper hull (add in reverse)
    int lower_size = hull.size();
    for (int i = n - 2; i >= 0; --i) {
        while (hull.size() > lower_size && !isLeftTurnOrColinear(hull[hull.size() - 2], hull.back(), pts[i])) {
            hull.pop_back();
        }
        hull.push_back(pts[i]);
    }
 
    // Remove the duplicate start/end point
    if (hull.size() > 1 && hull.front().x == hull.back().x && hull.front().y == hull.back().y)
        hull.pop_back();
 
    // Output the convex hull
    cout << hull.size() << "\n";
    for (auto& p : hull) {
        cout << p.x << " " << p.y << "\n";
    }
 
    return 0