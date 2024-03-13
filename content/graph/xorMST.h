/**
 * Author: Jose Soto
 * Date: 2024-12-03
 * License: ???
 * Description: 1-indexed (a and T). Given an array $a$ of $n$ integers computes a spanning tree of the complete graph where the weight between two different nodes $1 \leq i, j \leq n$ is $a_i \oplus a_j$. xor\_sum stores the weight of the MST. T is the tree.
 * Time: $O(N \log^2 N)$
 * Status: Tested
 */
using dtype = int;
constexpr int LOG = 30;

struct XORMST{
    vvi T;
    int n;
    vector< pair<dtype, int> > a;
    ll xor_sum = 0;

    XORMST(vector<dtype> &a){
        this->n = a.size() - 1;
        this->a.resize(n + 1);
        for(int i=1; i<=n; i++) this->a[i] = {a[i], i};
        sort(1 + all(this->a));
        T.resize(n + 1);
        buildMST(1, n, LOG);
        return;
    }

    void getMinEdge(int L1, int R1, int L2, int R2, int bit, int &u, int &v){
        vector< array<int,3> > trie;
        trie.pb({0, 0, 0});
        int cnt = 0;

        auto add = [&](dtype x, int idx){
            int curr = 0, b;
            for(int i=bit; i>=0; i--){
                b = !!(x&((dtype)(1)<<i));
                if(!trie[curr][b]) trie[curr][b] = ++cnt, trie.pb({0, 0, 0});
                curr = trie[curr][b];
            }
            trie[curr][2] = idx;
            return;
        };

        auto qry = [&](dtype x){
            int curr = 0, b;
            for(int i=bit; i>=0; i--){
                b = !!(x&((dtype)(1)<<i));
                if(trie[curr][b]) curr = trie[curr][b];
                else curr = trie[curr][!b];
            }
            return trie[curr][2];
        };

        for(int i=L1; i<=R1; i++) add(a[i].fi, i);

        int j;
        dtype min_xor = -1;

        for(int i=L2; i<=R2; i++){
            j = qry(a[i].fi);
            if(min_xor == -1) u = j, v = i, min_xor = a[j].fi^a[i].fi;
            if((a[j].fi^a[i].fi)<min_xor) u = j, v = i, min_xor = a[j].fi^a[i].fi;
        }

        return;
    }

    void buildMST(int L, int R, int bit){
        if(L == R) return;
        if(bit < 0){
            for(int i=L+1; i<=R; i++) T[ a[L].se ].pb( a[i].se ), T[ a[i].se ].pb( a[L].se );
            return;
        }
        dtype pot = ((dtype)(1)<<bit);
        if(a[L].fi&pot || !(a[R].fi&pot)) return buildMST(L, R, bit-1);
        int mid = L;
        while(!(a[mid+1].fi&pot)) mid++;

        buildMST(L, mid, bit-1);
        buildMST(mid+1, R, bit-1);

        int u,v;
        getMinEdge(L, mid, mid+1, R, bit-1, u, v);
        xor_sum += (ll)(a[u].fi^a[v].fi);

        T[ a[v].se ].pb( a[u].se );
        T[ a[u].se ].pb( a[v].se );
        return;
    }
};
