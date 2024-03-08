/**
 * Author: Jose Soto
 * Date: 2024-04-03
 * License: ???
 * Description: 1-indexed. vT is the adjacency list of the virtual tree, vT\_nodes its nodes with root vT\_root. Uses the same labels as the original tree.
 * Usage: 
 * build(). Is not necessary to manually call clearVT.
 * Time: $O(k \log N)$ to build VT of $k$ nodes
 * Status: Tested
 */
constexpr int LOG = 19; // n <= 2e5

struct VirtualTree{
    int n, root, dfs_t = 0, vT_root;
    vvi T, vT, parent;
    vi vT_nodes, dfs_start, dfs_end, depth;
    vb active_nodes;

    VirtualTree(vvi &T, int root) : n(sz(T) - 1), root(root), T(T){
        vT.resize(n + 1);
        parent.assign(n + 1, vi(LOG));
        dfs_start.resize(n + 1);
        dfs_end.resize(n + 1);
        depth.resize(n + 1);
        active_nodes.assign(n + 1, false);
        __dfs(root, root);
        __lca();
    }
    int lca(int a, int b){
        if(depth[a] < depth[b]) swap(a, b);
        for(int i=LOG-1; i>=0; i--)
            if(depth[ parent[a][i] ] >= depth[b]) a = parent[a][i];
        if(a == b) return a;
        for(int i=LOG-1; i>=0; i--)
            if(parent[a][i] != parent[b][i])
                a = parent[a][i], b = parent[b][i];
        return parent[a][0];
    }
    void build(vi &arr){
        auto cmp = [&](const int &a, const int &b){
            return dfs_start[a] < dfs_start[b];
        };
        clearVT();
        sort(all(arr), cmp);
        vT_nodes = arr;
        for(auto u: arr) active_nodes[u] = true;
        int temp;
        for(int i=0; i+1<sz(arr); i++){
            temp = lca(arr[i], arr[i+1]);
            if(!active_nodes[temp]) vT_nodes.pb(temp);
            active_nodes[temp] = true;
        }
        sort(all(vT_nodes), cmp);
        vT_root = vT_nodes[0];
        stack<int> s;
        s.push(vT_root);
        for(auto nd:vT_nodes){
            if(nd == vT_root) continue;
            while(dfs_start[nd] > dfs_end[s.top()]) s.pop();
            vT[ s.top() ].pb(nd);
            vT[ nd ].pb(s.top());
            s.push(nd);
        }
    }
    void clearVT(){
        for(auto u: vT_nodes)
            vT[u].clear(), active_nodes[u] = false;
    }
    void __dfs(int u, int pu){
        dfs_start[u] = dfs_t++;
        parent[u][0] = pu;
        for(auto nxt:T[u]){
            if(nxt == pu) continue;
            depth[nxt] = 1 + depth[u];
            __dfs(nxt, u);
        }
        dfs_end[u] = dfs_t++;
    }
    void __lca(){
        for(int bit=1; bit<LOG; bit++)
            for(int i=1; i<=n; i++)
                parent[i][bit] = parent[ parent[i][bit-1] ][bit-1];
    }
};
