#include <bits/stdc++.h>
using namespace std;

class MCMF {
private:
    struct Edge { 
        int cap, flow, to, rev, d; 
        int spare() { return cap - flow; }
    };
    const int N;
    vector<int> par, dist, inq;
    vector<vector<int>> d;
    vector<Edge*> epar;
    vector<vector<Edge>> adj;
public:
    MCMF(int N) : N(N) {
        inq.resize(N);
        dist.resize(N);
        par.resize(N);
        epar.resize(N);
        adj.resize(N);
    }

    bool spfa(int src, int sink) {
        fill(dist.begin(), dist.end(), 1e8);
        fill(par.begin(), par.end(), -1);
        queue<int> q;
        q.push(src);
        inq[src] = true;
        dist[src] = 0;

        while (!q.empty()) {
            int cur = q.front(); q.pop();
            inq[cur] = false;
            for (auto &e : adj[cur]) {
                int nxt = e.to;
                if (e.spare() > 0 && dist[nxt] > dist[cur] + e.d) {
                    dist[nxt] = dist[cur] + e.d;
                    par[nxt] = cur;
                    epar[nxt] = &e;
                    if (!inq[nxt]) q.push(nxt), inq[nxt] = true;
                }
            }
        }
        return par[sink] != -1;
    }

    pair<int, int> mcmf(int src, int sink) {
        int max_flow = 0, min_cost = 0;
        while (spfa(src, sink)) {
            int mn = 1e8;
            for (int i = sink; i != src; i = par[i]) {
                mn = min(mn, epar[i]->spare());
            }
            for (int i = sink; i != src; i = par[i]) {
                Edge *e = epar[i];
                e->flow += mn;
                adj[e->to][e->rev].flow -= mn;
                min_cost += mn * e->d;
            }
            max_flow += mn;
        }
        return {max_flow, min_cost};
    }

    void add_edge(int u, int v, int c, int d) {
        adj[u].push_back({c, 0, v, (int)adj[v].size(), d});
        adj[v].push_back({0, 0, u, (int)adj[u].size() - 1, -d});
    }
};

int main() {
    MCMF net(100);
}