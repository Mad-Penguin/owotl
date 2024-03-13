/**
 * Author: Jose Soto
 * Date: 2023-07-08
 * Source: folklore
 * Description: Treap. Binary search tree over values. Split stores in $L$ the nodes with value strictly smaller than the specified.
 * Usage:
 * uniform_int_distribution<int> priorities(0, 500000000);
 * mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
 * pnode root = nullptr , L , R;
 * insertNode(root, createNode(value, priorities(rng), some_dp));  
 * Time: Expected $O(\log N)$ each operation
 * Status: Tested
 */
constexpr ll inf = 1e18;

struct node_{
    node_ *l , *r ;
    ll value, priority, dp, max_dp_subtree, min_dp_subtree;
    int sz_subtree;
    node_(ll v, ll p, ll my_dp){
        value = v;
        priority = p;
        sz_subtree = 0;
        dp = max_dp_subtree = min_dp_subtree = my_dp;
        l = r = nullptr;
    }
};
typedef node_ * pnode;

pnode createNode(ll v, ll p, ll dp = 0){
    pnode x = new node_(v, p, dp);
    return x;
}
int getSzSubtree(pnode u){
    return u ? u->sz_subtree : 0LL;
}
ll getMaxDPSubtree(pnode u){
    return u ? u->max_dp_subtree : -inf;
}
ll getMinDPSubtree(pnode u){
    return u ? u->min_dp_subtree : inf;
}
void upd(pnode u){
    if(!u) return;
    u->sz_subtree = getSzSubtree(u->l) + getSzSubtree(u->r) + 1;
    u->max_dp_subtree = max(u->dp , max(getMaxDPSubtree(u->l), getMaxDPSubtree(u->r)));
    u->min_dp_subtree = min(u->dp , min(getMinDPSubtree(u->l), getMinDPSubtree(u->r)));
    return;
}

void split(pnode t, ll value, pnode &L, pnode &R){
    if(!t){
        L = R = nullptr;
        return;
    }
    if(t->value < value){
        split( t->r , value , t->r , R );
        L = t;
    }else{
        split( t->l , value , L , t->l );
        R = t;
    }
    upd( t );
    return;
}

void mergeTreaps(pnode &t, pnode L, pnode R){
    if(!L || !R){
        t = L ? L : R;
        return;
    }
    if( L->priority > R->priority ){
        mergeTreaps( L->r , L->r , R );
        t = L;
    }else{
        mergeTreaps( R->l , L , R->l );
        t = R;
    }
    upd( t );
    return;
}

void eraseNode(pnode &t, ll value){
    if(!t) return;
    if(t->value == value){
        mergeTreaps( t , t->l , t->r );
    }else{
        eraseNode( t->value >= value ? t->l : t->r , value );
    }
    upd( t );
    return;
}

void insertNode(pnode &t, pnode nd){
    if( !t ){ t = nd; upd( t ); return; }
    if( t->priority >= nd->priority ){
        insertNode( t->value >= nd->value ? t->l : t->r , nd );
    }else{
        split( t , nd->value , nd->l , nd->r );
        t = nd;
    }
    upd( t );
    return;
}
