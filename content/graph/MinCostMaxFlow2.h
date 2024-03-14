/**
 * Author: Diego Garcia
 * Date: 2023-05-05
 * License: ???
 * Source: Some CF blog
 * Description: MCMF using Dijkstra and Potentials. O(nm) in potentials calc.
 + O(F m log m) where F = max flow (faster in practice).
 * Status: Tested
 */
template <class T = int>
struct MCF {
    int n, s, t;
    static constexpr T T_inf = numeric_limits<T>::max();
    T bound;
    struct Edge {
        int u, v;
        T cap, cost;
        Edge(int u_, int v_, T c, T w) : u(u_), v(v_), cap(c), cost(w) {}
    };
    vector <Edge> edges;
    vector <vi> adj;
    vector <T> pot, dist;
    bool any_flow;
    MCF(int n_, int s_, int t_, T b = T_inf, bool af = false)
     : n(n_), s(s_), t(t_), bound(b), adj(n + 1), pot(n + 1), dist(n + 1), any_flow(af) {}
    void add_edge(int u, int v, T c, T w) {
        edges.pb(Edge(u, v, c, w));
        edges.pb(Edge(v, u, 0, -w));
        adj[u].pb(sz(edges) - 2);
        adj[v].pb(sz(edges) - 1);
    }
    pair <T, T> mincost_flow() {
        //call get potentials if needed!
        T flow = 0;
        T cost = 0;
        vector <bool> vis(n + 1, false);
        vi comes_from(n + 1);
        while(bound) {
            fill(all(vis), false);
            fill(all(dist), T_inf);
            priority_queue <pair<T, int>, vector<pair<T, int>>, greater<>> pq;
            pq.push({0, s});
            dist[s] = 0;
            while(!pq.empty()) {
                auto [d, u] = pq.top();
                pq.pop();
                if(vis[u]) continue;
                vis[u] = true;
                for(int i : adj[u]) {
                    int v = edges[i].v;
                    T c = edges[i].cap;
                    T d = dist[u] + edges[i].cost + pot[u] - pot[v];
                    if(c > 0 && !vis[v] && d < dist[v]) {
                        dist[v] = d;
                        comes_from[v] = i;
                        pq.push({dist[v], v});
                    }
                }
            }
            if(!vis[t]) break;
            T path_cost = 0;
            T path_flow = bound;
            for(int v = t; v != s; v = edges[comes_from[v]].u) {
                path_flow = min(path_flow, edges[comes_from[v]].cap);
                path_cost += edges[comes_from[v]].cost;

            }
            path_cost *= path_flow;
            if(any_flow && path_cost >= 0) break;
            bound -= path_flow;
            for(int v = t; v != s; v = edges[comes_from[v]].u) {
                int i = comes_from[v];
                edges[i].cap -= path_flow;
                edges[i ^ 1].cap += path_flow;
            }
            flow += path_flow;
            cost += path_cost;
            for(int i = 1; i <= n; i++) {
                dist[i] += pot[i] - pot[s];
            }
            pot = dist;
        }
        return {flow, cost};
    }
    void get_potentials() {
        for(int i = 1; i <= n; i++) {
            for(auto e : edges) {
                if(e.cap == 0) continue;
                if(pot[e.u] + e.cost < pot[e.v]) {
                    pot[e.v] = pot[e.u] + e.cost;
                    assert(i != n);
                }
            }
        }
    }
};
