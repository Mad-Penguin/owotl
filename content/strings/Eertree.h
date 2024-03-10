/**
 * Author: Jose Soto
 * Date: 2024-09-03
 * License: ???
 * Description: Computes eertree for a given string. Letters have to be added one by one from left to right. After adding all the letters maybe call computeFrequency().
 * Usage: 
 * Let $s$ be the original string and $p$ be the palindrome associated with node $u$
 * et[$u$].l is the length of $p$
 * et[$u$].cnt is the number of times $p$ appears as the longest palindrome suffix of a prefix $s[0:i]$. After calling computeFrequency() is the number of times $p$ appears in $s$.
 * et[$u$].link is the node corresponding to the longest proper palindrome of $p$
 * Time: $O(N)$ time and $O(N \alpha)$ memory. If array is replaced with map $O(N \log \alpha)$ time and $O(N)$ memory.
 * Status: Tested
 */
constexpr short alpha = 26;
constexpr char offset = 'a';

struct state{
    int l, link, cnt;
    array<int,alpha> go;
    state(){
        l = cnt = 0;
        go.fill(0);
    }
};

struct eertree{
    int n = 2;
    int last = 1;
    vector<state> et;
    string s;

    eertree(){
        et.resize(2);
        et[0].link = et[1].link = 1;
        et[1].l = -1;
    }

    int palSuff(int x){
        while(s[sz(s) - 2 - et[x].l] != s.back()) x = et[x].link;
        return x;
    }

    int add(char ch){
        s.pb(ch);
        last = palSuff(last);
        bool new_pal = !et[last].go[ch-offset];
        if(new_pal){
            et.pb(state());
            et[last].go[ch-offset] = n++;
            et.back().link = et[palSuff(et[last].link)].go[ch-offset];
            et.back().l = et[last].l + 2;
            if(et.back().l == 1) et.back().link = 0;
        }
        last = et[last].go[ch-offset];
        // Do something with last, maybe if new_pal
        et[last].cnt++;
        if(et[last].l == sz(s)) last = et[last].link;
        return new_pal;
    }

    void computeFrequency(){
        for(int i=n-1; i>1; i--)
            et[ et[i].link ].cnt += et[i].cnt;
    }
};
