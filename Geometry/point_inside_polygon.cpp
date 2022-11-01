#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Point = pair<ll, ll>;
#define x first
#define y second

int ccw(const Point &a, const Point &b, const Point &c) {
    ll ret = a.x*b.y + b.x*c.y + c.x*a.y;
    ret -= a.y*b.x + b.y*c.x + c.y*a.x;
    return (ret > 0) - (ret < 0);
}

bool isCross(Point a, Point b, Point c, Point d) {
    int ab = ccw(a, b, c) * ccw(a, b, d);
    int cd = ccw(c, d, a) * ccw(c, d, b);
    if (ab == 0 && cd == 0) {
        if (a > b) swap(a, b);
        if (c > d) swap(c, d);
        return !(b < c || d < a);
    }
    return ab <= 0 && cd <= 0;
}

bool isInside(const vector<Point> &p, const Point &p1) {
    int cnt = 0, n = p.size();
    Point p2 = {int(1e9) + 1, p1.y + 1};
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        /* 다각형 경계위에 있는 경우 inside로 판별 */
        int c = ccw(p[i], p[j], p1);
        if (c == 0) {
            Point a = p[i], b = p[j];
            if (a > b) swap(a, b);
            if (a <= p1 && p1 <= b) return true;
        }
        cnt += isCross(p1, p2, p[i], p[j]); 
    }
    return cnt & 1;
}