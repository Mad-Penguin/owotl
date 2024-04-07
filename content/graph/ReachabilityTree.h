/**
 * Author: Jose Soto
 * Date: 2023-02-18
 * License: ???
 * Description: Computes the Reachability/KruskalReconstruction tree $T$ of a graph $G$ when inserting the edges in the given order. Nodes of $G$ correspond to leaves of $T$ and internal nodes of $T$ corresponds to edges that connects the set of leaves of its subtrees. Nodes of $G$ should be $1$-indexed. edges should be $\{u, v, w\}$ (endpoints and weight), this vector should be $0$-indexed. $T$ has at most $2N - 1$ vertices. If $u$ is an internal node of $T$ then $w[u]$ corresponds to weight of the associated edge.
* Time: $O(N \log N)$ but can be improved to $O(N)$, $\log N$ comes from DSU.
 * Status: Tested
 */
struct DSU{
    int n, comp;
    vi dsu;
    DSU(int n) : n(n), dsu(n + 1), comp(n) { iota(all(dsu), 0); }
    int getF(int u){
        if(dsu[u] == u) return u;
        return dsu[u] = getF( dsu[u] );
    }
    bool join(int u, int v){
        int Fu = getF(u), Fv = getF(v);
        if(Fu == Fv) return false;
        comp--;
        dsu[ Fu ] = Fv;
        return true;
    }
};
struct ReachabilityTree{
    int n, idx, root;
    DSU dsu = DSU(0);
    vvi T, p;
    vi parent, depth, sz_subtree, sz_leaves, w;
    vector< array<int, 3> > edges;
    ReachabilityTree(int n, vector< array<int, 3> > edges){
        this->n = n;
        this->idx = n+1;
        this->edges = edges;

        T.resize(n + n);
        parent.resize(n + n);
        dsu = DSU(n + n - 1); // DSU indexa en 1 solito
        depth.resize(n + n);
        sz_subtree.resize(n + n);
        sz_leaves.resize(n + n);
        w.resize(n + n);

        __build();
        __dfs(root, 0);
    }
    void __build(){
        int u, v;
        for(auto e:edges){
            u = dsu.getF(e[0]);
            v = dsu.getF(e[1]);
            if(u != v){
                T[idx].pb(u);
                T[idx].pb(v);
                parent[u] = idx;
                parent[v] = idx;
                // Warning: Join debe asignar como nuevo representante a idx
                dsu.join(u, idx);
                dsu.join(v, idx);
                w[idx] = e[2];
                if(dsu.comp == 1) root = idx;
                idx++;
                continue;
            }
        }
        return;
    }
    void __dfs(int u, int d){
        depth[u] = d;
        sz_subtree[u] = 1;
        sz_leaves[u] = !T[u].size();
        for(auto v:T[u]){
            __dfs(v, d+1);
            sz_subtree[u] += sz_subtree[v];
            sz_leaves[u] += sz_leaves[v];
        }
        return;
    }
};
