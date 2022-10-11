// https://github.com/justiceHui/SSU-SCCC-Study/blob/master/2022-autumn-adv/slide/02.pdf

#include <bits/stdc++.h>
using namespace std;

// Longest Common Prefix Array
struct LCP {
    vector<int> sa, pos, tmp, lcp;
    string s;
    int n;

    void getSuffixArray() {
        for (int i = 0; i < n; i++) sa[i] = i, pos[i] = s[i];
        for (int k = 1; ; k <<= 1) {
            auto cmp = [&](int a, int b) -> bool {
                if (pos[a] != pos[b]) return pos[a] < pos[b];
                if (a + k < n && b + k < n) return pos[a + k] < pos[b + k];
                return a > b;
            };
            stable_sort(sa.begin(), sa.end(), cmp);
            for (int i = 1; i < n; i++) tmp[i] = tmp[i-1] + cmp(sa[i-1], sa[i]);
            for (int i = 0; i < n; i++) pos[sa[i]] = tmp[i];
            if (tmp.back() + 1 == n) break;
        }
    }

    // O(n)
    void getLCP() {
        for (int i = 0, j = 0; i < n; i++, j = max(j-1, 0)) {
            if (pos[i] == 0) continue;
            while (sa[pos[i]-1] + j && sa[pos[i]] + j < n 
                && s[sa[pos[i]-1] + j] == s[sa[pos[i]] + j]) j++;
            lcp[pos[i]] = j;
        }
    }

    void build(const string &_s) {
        s = _s;
        n = s.size();
        sa.resize(n); pos.resize(n); tmp.resize(n); lcp.resize(n);
        getSuffixArray();
        getLCP();
    }
};
