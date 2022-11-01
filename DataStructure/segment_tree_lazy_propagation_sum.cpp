#include <bits/stdc++.h>
using namespace std;

template<class T>
class LazySegtree {
private:
    const int N;
    vector<T> tree;
    vector<T> lazy;
    
    void propagate(int n, int s, int e) {
        if (lazy[n] == 0) return;
        tree[n] += (e - s + 1) * lazy[n];
        if (s != e) {
            lazy[n << 1] += lazy[n];
            lazy[n << 1 | 1] += lazy[n];
        }
        lazy[n] = 0;
    }

    void update(int qs, int qe, T diff, int n, int s, int e) {
        propagate(n, s, e);
        if (e < qs || s > qe) return;
        if (qs <= s && e <= qe) {
            lazy[n] = diff;
            propagate(n, s, e);
            return;
        }
        int mid = s + e >> 1;
        update(qs, qe, diff, n << 1, s, mid);
        update(qs, qe, diff, n << 1 | 1, mid + 1, e);
        tree[n] = tree[n << 1] + tree[n << 1 | 1];
    }

    T query(int qs, int qe, int n, int s, int e) {
        propagate(n, s, e);
        if (e < qs || s > qe) return 0;
        if (qs <= s && e <= qe) return tree[n];
        int mid = s + e >> 1;
        return query(qs, qe, n << 1, s, mid) + query(qs, qe, n << 1 | 1, mid + 1, e);
    }

public:
    LazySegtree(int N) : N(N) {
        tree.resize(N << 2);
        lazy.resize(N << 2);
    }
    void update(int qs, int qe, T diff) { update(qs, qe, diff, 1, 0, N); }
    T query(int qs, int qe) { return query(qs, qe, 1, 0, N); }
};

int main() {
    // This is example of Usage
    // problem link : icpc.me/10999
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m, k; cin >> n >> m >> k; 
    LazySegtree<long long> seg(1.01e6);
    for (int i = 1; i <= n; i++) {
        long long x; cin >> x;
        seg.update(i, i, x);
    }
    for (int i = 0; i < m + k; i++) {
        int q; cin >> q;
        if (q == 1) {
            int qs, qe; long long diff; cin >> qs >> qe >> diff;
            seg.update(qs, qe, diff);
        }
        if (q == 2) {
            int qs, qe; cin >> qs >> qe;
            cout << seg.query(qs, qe) << "\n";
        } 
    }
}