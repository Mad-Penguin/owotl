/**
 * Author: Jashinchan https://judge.yosupo.jp/submission/106185
 * Date: ???
 * License: ???
 * Description: 0-indexed. Computes dominator tree of a directed graph. run($s$) returns a vector $p$. $p[i] = -1$ if $i = s$ or if $i$ is not reachable from $s$, otherwise is equal to the parent. $s$ is the root. $u$ is ancestor of $v$ if $u$ appears in every path from $s$ to $v$.
 * Usage: 
 * add_edge($u$, $v$) - run($s$)
 * Time: $O(|E| \log |V|)$
 * Status: Tested
 */
struct DominatorTree{
    vector< basic_string<int> > g, rg, bucket;
    basic_string<int> arr, par, rev, sdom, dom, dsu, label;
    int n, t;

    explicit DominatorTree(int n) : g(n), rg(n), bucket(n), arr(n, -1), par(n, -1), rev(n, -1), sdom(n, -1), dom(n, -1), dsu(n, 0), label(n, 0), n(n), t(0) {}
    void add_edge(int u, int v){
        g[u] += v;
    }
    void dfs(int u){
        arr[u] = t;
        rev[t] = u;
        label[t] = sdom[t] = dsu[t] = t;
        t++;
        for(int w : g[u]){
            if(arr[w] == -1){
                dfs(w);
                par[arr[w]] = arr[u];
            }
            rg[arr[w]] += arr[u];
        }
    }
    int find(int u, int x=0){
        if(u == dsu[u]) return x ? -1 : u;
        int v = find(dsu[u], x + 1);
        if(v < 0) return u;
        if(sdom[label[dsu[u]]] < sdom[label[u]])
            label[u] = label[dsu[u]];
        dsu[u] = v;
        return x ? v : label[u];
    }
    vi run(int root){
        dfs(root);
        iota(all(dom), 0);
        for(int i=t-1; i>=0; i--){
            for(int w : rg[i]) sdom[i] = std::min(sdom[i], sdom[find(w)]);
            if(i) bucket[sdom[i]] += i;
            for(int w : bucket[i]){
                int v = find(w);
                if (sdom[v] == sdom[w]) dom[w] = sdom[w];
                else dom[w] = v;
            }
            if(i > 1) dsu[i] = par[i];
        }
        for(int i=1; i<t; i++) if(dom[i] != sdom[i]) dom[i] = dom[dom[i]];
        vi outside_dom(n, -1);
        for(int i=1; i<t; i++) outside_dom[rev[i]] = rev[dom[i]];
        return outside_dom;
    }
};
