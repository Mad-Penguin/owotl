/**
 * Author: Diego Garcia
 * Date: ???
 * License: ???
 * Source: Folklore
 * Description: Tarjan's algorithm for finding bridges and articulation points in undirected
 graph. Can be used for building the bridge tree.
 * Time: construction $O(N log M)$ since briges and points are kept in sets, but easy to make
 $O(N+M)$ keeping some bool vector.
 * Status: Tested
 */
struct Tarjan {
    int t, n;
    vi mt, dt, in_stack; //mt = min time, dt = discovery time
    vector <vi> adj;
    set <pii> bridges;
    set <int> artic_points;
    Tarjan(int n_) : n(n_), t(1), adj(n+1), mt(n+1), dt(n+1), in_stack(n+1) {}
    void add_edge(int u, int v) { adj[u].pb(v); adj[v].pb(u); }
    void tarjan_dfs(int u, int par) {
        if(dt[u]) return;
        int child_cnt = 0;
        dt[u] = mt[u] = t++;
        in_stack[u] = 1;
        for(int v : adj[u]) {
            if(v == par) continue;
            if(!dt[v]) {
                tarjan_dfs(v, u);
                child_cnt++;
                mt[u] = min(mt[u], mt[v]);
                if(mt[v] >= dt[u] && par != -1) {
                    artic_points.insert(u);
                }
                if(mt[v] > dt[u]) {
                    bridges.insert({min(v, u), max(u, v)});
                }
                else {
                    //can connect (u, v) a bridge tree
                }
            }
            else if(in_stack[v]) {
                mt[u] = min(mt[u], dt[v]);
            }
        }
        in_stack[u] = 0;
        if(par == -1 && child_cnt > 1) artic_points.insert(u);
    }
    void find_points_and_bridges() {
        for(int i = 1; i <= n; i++) tarjan_dfs(i, -1);
    }
};
