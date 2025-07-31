// Point Struct + Polygon Area + Boundary Integer Points using GCD
// Interior points = (Area + 2 - Boundary) / 2   [Pick's Theorem]
// Area is 2×actual area (unscaled), so result is still integer

struct Point {
    int x, y;
    
    void read() { cin >> x >> y; }

    Point operator +(const Point& b) const { return { x + b.x, y + b.y }; }
    Point operator -(const Point& b) const { return { x - b.x, y - b.y }; }

    ll operator *(const Point& b) const {  // Cross product
        return (ll)x * b.y - (ll)y * b.x;
    }

    void operator +=(const Point& b) { x += b.x; y += b.y; }
    void operator -=(const Point& b) { x -= b.x; y -= b.y; }
    void operator *=(const int k) { x *= k; y *= k; }

    // Cross product of (b - a) × (c - a)
    ll cross(const Point& b, const Point& c) const {
        return (b - *this) * (c - *this);
    }
};

// Cross product for signed area
int cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

// Twice the area of polygon using shoelace formula (always positive)
int polygonArea(const vector<Point>& points) {
    int n = points.size();
    int total = 0;
    for (int i = 0; i < n; ++i) {
        const Point& a = points[i];
        const Point& b = points[(i + 1) % n];
        total += cross(a, b);
    }
    return abs(total);
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Point> p(n);
    for (auto& pt : p) pt.read();

    int area = polygonArea(p);  // 2 × actual area

    int boundary = 0;
    for (int i = 0; i < n; i++) {
        auto a = p[i];
        auto b = p[(i + 1) % n];
        int dx = abs(a.x - b.x);
        int dy = abs(a.y - b.y);
        boundary += gcd(dx, dy);  // # of integer points on edge
    }

    int interior = (area + 2 - boundary) / 2;
    cout << interior << " " << boundary << "\n";
}
