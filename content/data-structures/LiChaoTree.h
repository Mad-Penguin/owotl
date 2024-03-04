/**
 * Author: Diego Garcia
 * Date: 2024-03-03
 * License: ???
 * Source: ???
 * Description: min Li Chao Tree for linear functions.
 * Usage: Functions can be changed, just make sure they cross at most once.
 * Status: Not tested
 */

struct func {
    ll m, b;
    func(ll m = 0, ll b = 1e18) : m(m), b(b) {}
    ll eval(int x) { return m * x + b; }
} st[4 * N];
void add(int u, int l, int r, func f) {
    int m = (l + r) / 2;
    bool lef = f.eval(l) < st[u].eval(l);
    bool mid = f.eval(m) < st[u].eval(m);
    if(mid) swap(f, st[u]);
    if(l == r) return;
    if(lef != mid) add(2*u+1, l, m, f);
    else add(2*u+2, m+1, r, f);
}
ll get(int u, int l, int r, int x) {
    if(l == r) return st[u].eval(x);
    int m = (l + r) / 2;
    if(x <= m) return min(st[u].eval(x), get(2*u+1, l, m, x));
    return min(st[u].eval(x), get(2*u+2, m+1, r, x));
}
