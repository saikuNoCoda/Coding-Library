//https://github.com/jakobkogler/Algorithm-DataStructures/blob/master/Strings/AhoCorasick.h
// Uses
// Find all strings from a given set in a text
// Finding the lexicographical smallest string of a given length that doesn't match any given strings
// Finding the shortest string containing all given strings
// Finding the lexicographical smallest string of length L containing k strings
// Available - https://cp-algorithms.com/string/aho_corasick.html

const int K = 26;
 
class AhoCorasick {
public:
    
    struct Vertex {
        array<int,K> next;
        bool terminal = false;
        int terminal_idx = -1;
        int p = -1;
        char pch;
        int depth = 0;
        int link = 0;
        int next_terminal = 0;
        array<int,K> go;
        int value = 0;
        int range_value = 0;

        Vertex(int p,char ch,int depth): p(p), pch(ch), depth(depth){
            fill(next.begin(),next.end(),0);
            fill(go.begin(),go.end(),0);
        }
    };

    vector<Vertex> t;

    AhoCorasick() :t(1,{-1,'$',0}) {}
    
    void add_string(string const &s,int idx,int val){
        int v = 0;
        for(char ch: s){
            int c = ch-'a';
            if(!t[v].next[c]){
                t[v].next[c] = t.size();
                t.emplace_back(v,ch,t[v].depth+1);
            }
            v = t[v].next[c];
        }

        t[v].terminal = true;
        t[v].terminal_idx = idx;
        t[v].value += val;
    }

    void push_links(){
        queue<int> q;
        q.push(0);

        while(!q.empty()){
            int v = q.front();
            auto &cur = t[v];
            auto &link = t[cur.link];
            q.pop();
            cur.next_terminal = link.terminal?cur.link:link.next_terminal;
            cur.range_value = link.range_value + cur.value;

            for(int c=0;c<K;c++){
                if(cur.next[c]){
                    t[cur.next[c]].link = v?link.next[c]:0;
                    q.push(cur.next[c]);
                }else {
                    cur.next[c] = link.next[c];
                }
            }
        }
    }

    int transition(int idx,char c){
        return t[idx].next[c-'a'];
    }

    int get_range(int idx){
        return t[idx].range_value;
    }

    Vertex const& getInfo(int idx){
        return t[idx];
    }
};
