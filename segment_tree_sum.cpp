#include <bits/stdc++.h>
using namespace std;

template<class T>
class SegTree {
private:
    const int N;
    vector<T> tree;
public:
    SegTree(int N) : N(N) { tree.resize(4 * N); }

    void update(int idx, T diff, int node, int s, int e) {
        if (idx < s || idx > e) return;
        tree[node] += diff;
        if (s == e) return;
        int mid = s + e >> 1;
        update(idx, diff, node << 1, s, mid);
        update(idx, diff, node << 1 | 1, mid + 1, e);
    }
    void update(int idx, T diff) { update(idx, diff, 1, 0, N); }


    T query(int l, int r, int node, int s, int e) {
        if (l <= s && e <= r) return tree[node];
        if (r < s || e < l) return 0;
        int mid = s + e >> 1;
        return query(l, r, node << 1, s, mid) + query(l, r, node << 1 | 1, mid + 1, e);
    }
    T query(int l, int r) { return query(l, r, 1, 0, N); }
};

using ll = long long;
ll arr[1000006];

int main() {
    // This is example of Usage
    // problem link : icpc.me/2042
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m, k; cin >> n >> m >> k;
    SegTree<ll> seg(1e6);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        seg.update(i, arr[i]);
    }
    for (int i = 0; i < m + k; i++) {
        ll x, a, b; cin >> x >> a >> b;
        if (x == 1) {
            seg.update(a, b - arr[a]);
            arr[a] = b;
        } else {
            cout << seg.query(a, b) << "\n";
        }
    }
}
