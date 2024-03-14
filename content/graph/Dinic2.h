/**
 * Author: Diego Garcia
 * Date: ????
 * License: ???
 * Source: many places :p
 * Description: Flow algorithm with complexity $O(VE\log U)$ where $U = \max |\text{cap}|$
 if using potentials, else O(V^2 E).
    Other complexities:
 * $O(\min(E^{1/2}, V^{2/3})E)$ if $U = 1$; $O(\sqrt{V}E)$ for bipartite matching.
 * Status: Tested
 */

template <class T = int>
struct Dinic {
    struct Edge {
        int u, v;
        T cap;
        Edge(int u, int v, T c) : u(u), v(v), cap(c) {}
    };
    int n, lim;
    bool scaling;
    vi pt, dist;
    vector <Edge> edges;
    vector <vi> adj;
    Dinic(int n, bool sc = true) : n(n), scaling(sc), pt(n), dist(n), adj(n) {}
    void add_edge(int u, int v, T cap) {
        edges.pb(Edge(u, v, cap));
        edges.pb(Edge(v, u, T(0)));
        adj[u].pb(sz(edges) - 2);
        adj[v].pb(sz(edges) - 1);
    }
    bool bfs(int s, int t) {
        fill(all(dist), n);
        queue <int> q;
        dist[s] = 0;
        q.push(s);
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            for(auto e : adj[u]) {
                if(!edges[e].cap) continue;
                int v = edges[e].v;
                if(dist[v] == n) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
        return dist[t] != n;
    }
    T dfs(int u, int t, T flow) {
        if(u == t) return flow;
        for(; pt[u] < sz(adj[u]); pt[u]++) {
            int i = adj[u][pt[u]];
            int v = edges[i].v;
            T c = edges[i].cap;
            if(!c || dist[v] != dist[u] + 1) continue;
            T can_push = dfs(v, t, min(flow, c));
            if(can_push > 0) {
                edges[i].cap -= can_push;
                edges[i ^ 1].cap += can_push;
                return can_push;
            }
        }
        return T(0);
    }
    T max_flow(int s, int t) {
        T ans(0);
        for(lim = scaling ? (1 << 30) : 1; lim; lim /= 2)
            while(bfs(s, t)) {
                fill(all(pt), 0);
                while(true) {
                    T flow = dfs(s, t, T(1e9));
                    if(flow > 0) ans += flow;
                    else break;
                }
            }
        return ans;
    }
};
