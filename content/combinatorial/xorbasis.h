/**
 * Author: Diego Garcia
 * Date: 2024-13-03
 * License: ???
 * Description: Computes de basis for a set of elements in [0, 2^D).
Every element in the basis has a different most significant bit.
The element with i-th bit on is saved on basis[i] (if it exists).
 * Time: $O(D)$
 * Status: Tested
 */

const int D = 60;
ll basis[D];
int dim;

//To check if an element is in the span, do the same
//but, if !basis[i] return false, otherwise true.
void insert_vector(ll k) {
    for(int i = D-1; i >= 0; i--) {
        if(!(k >> i & 1)) continue;
        if(!basis[i]) {
            basis[i] = k;
            dim++;
            return;
        }
        k ^= basis[i];
    }
}

//k-th smallest in linspace
ll get_kth(ll k) {
    ll x = 0;
    int pref = dim;
    for(ll i = D-1; i >= 0; i--) {
        if(!basis[i]) continue;
        ll p2 = 1ll << (pref - 1);
        ll mini_leq = 1;
        ll maxi_leq = p2;
        if(!(x >> i & 1))
            mini_leq += p2, maxi_leq += p2;
        if(mini_leq <= k && maxi_leq >= k) {
            if(!(x >> i & 1)) k -= p2;
            x ^= basis[i];
        }
        else if(x >> i & 1) k -= p2;
        pref--;
    }
    return x;
}
