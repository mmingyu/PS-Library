#include <bits/stdc++.h>
using namespace std;

template<class T>
class SegTree {
private:
    const int N;
    const T INF;
    vector<T> tree;
public:
    SegTree(int N, T INF = 2.1e9) : N(N), INF(INF) { tree.resize(4 * N); }

    void update(int idx, T val, int node, int s, int e) {
        if (idx < s || idx > e) return;
        if (s == e) { tree[node] = val; return; }
        int mid = s + e >> 1;
        update(idx, val, node << 1, s, mid);
        update(idx, val, node << 1 | 1, mid + 1, e);
        
        tree[node] = min(tree[node << 1], tree[node << 1 | 1]);
    }
    void update(int idx, T val) { update(idx, val, 1, 0, N); }


    T query(int l, int r, int node, int s, int e) {
        if (l <= s && e <= r) return tree[node];
        if (r < s || e < l) return INF;
        int mid = s + e >> 1;
        return min(query(l, r, node << 1, s, mid), query(l, r, node << 1 | 1, mid + 1, e));
    }
    T query(int l, int r) { return query(l, r, 1, 0, N); }
};


int main() {
    // This is example of Usage
    // problem link : icpc.me/14438
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    SegTree<int> seg(n + 1); // == SegTree<int> seg(n + 1, 2.1e9);
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        seg.update(i, x);
    }
    int q; cin >> q;
    while (q--) {
        int x, a, b; cin >> x >> a >> b;
        if (x == 1) seg.update(a, b);
        if (x == 2) cout << seg.query(a, b) << "\n";
    }
}