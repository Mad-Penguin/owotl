/**
 * Author: Jose Soto
 * Date: ???
 * License: ???
 * Description: Computes Aho Corasick for a set of strings which should be added one by one. Use functions go(), link() and exitLink() instead of variables.
 * Time: $O(N \alpha)$ time and memory.
 * Status: Tested
 */
struct state{
    int p,link,exit_link;
    int idx;
    short ch;
    bool is_word;
    array<int,27> go;
    state(){
        ch = 0;
        link = exit_link = idx = -1;
        go.fill(0);
        is_word = false;
    }
};

struct AhoCorasick{
    vector<state> ac;
    int last;
    int idx = 0;
    AhoCorasick(int sum_sz){
        ac.resize(sum_sz + 1);
        last = 1;
    }
    void add(string &s){
        int nd = 0, n = sz(s);
        for(int i=0; i<n; i++){
            if(!ac[nd].go[s[i]-'a'+1]) ac[nd].go[s[i]-'a'+1] = last++;
            ac[ ac[nd].go[s[i]-'a'+1] ].p = nd;
            nd = ac[nd].go[s[i]-'a'+1];
            ac[nd].ch = s[i]-'a'+1;
        }
        ac[nd].is_word = true;
        ac[nd].idx = idx++;
    }
    int go(int nd, short ch){
        if(ac[nd].go[ch]) return ac[nd].go[ch];
        return ac[nd].go[ch] = nd ? go(link(nd), ch) : 0;
    }
    int link(int nd){
        if(ac[nd].link!=-1) return ac[nd].link;
        if(!nd || !ac[nd].p) return 0;
        return ac[nd].link = go(link(ac[nd].p), ac[nd].ch);
    }
    // Returns index of first word found following links
    int exitLink(int nd){
        if(ac[nd].exit_link!=-1) return ac[nd].exit_link;
        if(!nd) return 0;
        if(ac[link(nd)].is_word) return ac[nd].exit_link = link(nd);
        return ac[nd].exit_link = exitLink(link(nd));
    }
};
