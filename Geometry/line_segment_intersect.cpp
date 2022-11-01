#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Point = pair<ll, ll>;
#define x first
#define y second

istream& operator>>(istream &in, Point &p) { 
    in >> p.first >> p.second; 
    return in;
}

int ccw(const Point &a, const Point &b, const Point &c) {
    ll ret = a.x*b.y + b.x*c.y + c.x*a.y;
    ret -= a.y*b.x + b.y*c.x + c.y*a.x;
    return (ret > 0) - (ret < 0);
}

bool cross(Point a, Point b, Point c, Point d) {
    int ab = ccw(a, b, c) * ccw(a, b, d);
    int cd = ccw(c, d, a) * ccw(c, d, b);
    if (ab == 0 && cd == 0) {
        if (a > b) swap(a, b);
        if (c > d) swap(c, d);
        return !(b < c || d < a);
    }
    return ab <= 0 && cd <= 0;
}


int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    Point a, b, c, d; cin >> a >> b >> c >> d;
    cout << cross(a, b, c, d);
}
