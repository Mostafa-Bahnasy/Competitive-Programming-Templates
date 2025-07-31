struct Point {
    int x, y;
};
 
// To find the orientation of ordered triplet (p, q, r).
// 0 --> colinear, 1 --> clockwise, 2 --> counterclockwise
int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) -
        (q.x - p.x) * (r.y - q.y);
 
    if (val == 0) return 0;            // colinear
    return (val > 0) ? 1 : 2;          // clock or counterclock wise
}
 
// Check if point r lies on segment pq (used for colinear case)
bool onSegment(Point p, Point q, Point r) {
    return r.x <= max(p.x, q.x) && r.x >= min(p.x, q.x) &&
        r.y <= max(p.y, q.y) && r.y >= min(p.y, q.y);
}
 
 
bool doIntersect(Point p1, Point p2, Point q1, Point q2) {
    int o1 = orientation(p1, p2, q1);
    int o2 = orientation(p1, p2, q2);
    int o3 = orientation(q1, q2, p1);
    int o4 = orientation(q1, q2, p2);
 
    // General case
    if (o1 != o2 && o3 != o4)
        return true;
 
    // Special Cases
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    if (o2 == 0 && onSegment(p1, p2, q2)) return true;
    if (o3 == 0 && onSegment(q1, q2, p1)) return true;
    if (o4 == 0 && onSegment(q1, q2, p2)) return true;
 
    return false;
}