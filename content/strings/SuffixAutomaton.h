/**
 * Author: Jose Soto
 * Date: 2024-07-03
 * License: ???
 * Description: Computes suffix automaton for a given string. Letters have to be added one by one from left to right. After adding all the letters maybe call markTerminalNodes().
 * Usage: 
 * For a string s.
 * SuffixAutomaton sa(sz(s));
 * for(auto ch: s) sa.add(ch);
 * sa.markTerminalNodes()
 * Status: Tested
 */
constexpr short alpha = 26;
constexpr char offset = 'a';

struct state{
    int len, link;
    bool is_terminal;
    array<int,alpha> next;
    state(){
        len = 0; link = -1; is_terminal = false;
        next.fill(0);
    }
};
struct SuffixAutomaton{
    int n;
    vector<state> sa;
    int sz = 1, last = 0;

    SuffixAutomaton(int n) : n(n), sa(2*n + 1){}

    void add(char ch_){
        short ch = ch_-offset;
        int curr = sz++;
        sa[curr].len = sa[last].len + 1;
        int p = last;
        while(p!=-1 && !sa[p].next[ch]){
            sa[p].next[ch] = curr;
            p = sa[p].link;
        }
        if(p == -1){
            sa[curr].link = 0;
        }else{
            int q = sa[p].next[ch];
            if(sa[p].len+1 == sa[q].len){
                sa[curr].link = q;
            }else{
                int clone = sz++;
                sa[clone].len = sa[p].len + 1;
                sa[clone].next = sa[q].next;
                sa[clone].link = sa[q].link;
                while(p!=-1 && sa[p].next[ch] == q){
                    sa[p].next[ch] = clone;
                    p = sa[p].link;
                }
                sa[q].link = sa[curr].link = clone;
            }
        }
        last = curr;
        return;
    }
    void markTerminalNodes(){
        int curr = last;
        while(curr){
            sa[curr].is_terminal = true;
            curr = sa[curr].link;
        }
        return;
    }
};
