using ll = long long;
template<ll C, ll M> struct Hashing {
    vector<ll> h, pw;
    void build(const string &s) {
        h.resize(s.size()+1);
        pw.resize(s.size()+1);
        pw[0] = 1;
        for (int i = 1; i <= s.size(); i++) {
            h[i] = (h[i-1] * C + s[i]) % M;
            pw[i] = (pw[i-1] * C) % M;
        }
    }
    ll get(int l, int r) {
        ll ret = (h[r] - h[l-1] * pw[r-l+1]) % M;
        return ret >= 0 ? ret : ret + M;
    }
};
