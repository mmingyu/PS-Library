// https://github.com/justiceHui/SSU-SCCC-Study/blob/master/2022-autumn-adv/slide/02.pdf

#include <bits/stdc++.h>
using namespace std;

// O(Nlog^2N) suffixArray
vector<int> suffixArray(const string &s) {
    int n = s.size();
    // sa[i]: 앞 k글자만 이용하여 정렬했을 때, i번째로 오는 접미사 번호
    // pos[i]: sa 배열에서 i번째 접미사의 위치 -> sa의 역함수
    vector<int> sa(n), pos(n), tmp(n);
    for (int i = 0; i < n; i++) sa[i] = i, pos[i] = s[i];
    for (int k = 1; ; k <<= 1) {
        auto cmp = [&](int a, int b) -> bool {
            // a~a+k, b~b+k 비교
            if (pos[a] != pos[b]) return pos[a] < pos[b];
            if (a + k < n && b + k < n) return pos[a + k] < pos[b + k];
            return a < b; // 짧은게 먼저 옴
        };
        sort(sa.begin(), sa.end(), cmp);
        // 그룹 번호 다시 매겨줌: cmp(sa[i-1], sa[i]) -> 그룹 다르면 +1
        for (int i = 1; i < n; i++) tmp[i] = tmp[i-1] + cmp(sa[i-1], sa[i]);
        for (int i = 0; i < n; i++) pos[sa[i]] = tmp[i];
        if (tmp.back() + 1 == n) break;
    }
    return sa;
}
