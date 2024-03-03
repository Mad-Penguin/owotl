/**
 * Author: Diego Garcia
 * Date: 2024-03-03
 * License: ???
 * Source: ???
 * Description: Add and remove intervals from a set of disjoint intervals,
   mantaining some info. for them. To add [l, r] first it removes
   intersections with it, then it adds it as its own interval. If 'maximal'
   is on and endpoint touches other interval of same info, they will merge.
 * Status: Somewhat tested
 * Time: $O(\log N)$ amortized
 */
template <class T = int, class Info = int>
struct IntervalContainer {
    bool maximal;
    IntervalContainer(bool f = false) : maximal(f) {}
    struct Inter {
        T l, r;
        Info u;
        Inter(T r_ = 0) : r(r_) {}
        Inter(T l_, T r_, Info u_) : l(l_), r(r_), u(u_) {}
        bool operator < (const Inter &o) const { return r < o.r; }
    };
    set <Inter> S;
    //returns deleted intervals
    vector<Inter> del(T l, T r) { if(l > r) return {};
        vector <Inter> updated;
        for(T pos : {l, r}) {
            auto it = S.lower_bound(pos);
            if(it != S.end() && it->l <= pos) {
                auto old = *it;
                S.erase(it);
                if(old.l != pos) S.insert(Inter(old.l, pos - 1, old.u));
                if(old.r != pos) S.insert(Inter(pos + 1, old.r, old.u));
            }
        }
        for(auto it = S.lower_bound(l); it != S.upper_bound(r); it++) {
            updated.pb(*it);
        }
        S.erase(S.lower_bound(l), S.upper_bound(r));
        return updated;
    }
    //adds [l, r] with info u
    vector <Inter> upd(T l, T r, Info u) { if(l > r) return {};
        auto updated = del(l, r);
        if(maximal) {
            auto it_l = S.lower_bound(l);
            if(it_l != S.begin()) {
                it_l--;
                if(it_l->u == u && it_l->r == l - 1) {
                    l = it_l->l;
                    S.erase(it_l);
                }
            }
            auto it_r = S.lower_bound(r);
            if(it_r != S.end() && it_r->u == u && it_r->l == r + 1) {
                r = it_r->r;
                S.erase(it_r);
            }
        }
        S.insert(Inter(l, r, u));
        return updated;
    }
    bool elem(T pos) {
        auto it = S.lower_bound(pos);
        return it != S.end() && it->l <= pos;
    }
    Inter cover(T pos) { //assert(elem(pos));
        return *S.lower_bound(pos);
    }
};
