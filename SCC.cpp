#include <bits/stdc++.h>
using namespace std;

namespace tarzan {
    constexpr int N = 3003;
    int visited[N], scc_id[N], scc_cnt, v_cnt, n;
    vector<int> adj[N];
    stack<int> st;
    int dfs(int cur) {
        int ret = visited[cur] = scc_cnt++;
        st.push(cur);

        for (auto nxt : adj[cur]) {
            if (visited[nxt] == -1) ret = min(ret, dfs(nxt));
            else if (scc_id[nxt] == -1) ret = min(ret, visited[nxt]);   
        }

        if (ret == visited[cur]) {
            while (true) {
                int t = st.top(); st.pop();
                scc_id[t] = scc_cnt;
                if (t == cur) break;
            }
            scc_cnt++;
        }
        return ret;
    }

    void scc() {
        memset(scc_id, -1, sizeof(scc_id));
        memset(visited, -1, sizeof(visited));
        for (int i = 0; i < n; i++) {
            if (visited[i] == -1) dfs(i);
        }
    }
}

int main() {
    cin >> tarzan::n;
    tarzan::scc();
}