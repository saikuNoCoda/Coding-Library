
const int MAXN = 100;
const int MOD = 1e9 + 7;
int dfa[MAXN][26];
int paths[MAXN][MAXN];

void kmp_for_automata(string pattern){
    int n = sz(pattern);
    dfa[0][pattern[0]-'a'] = 1;

    for(int x = 0,i=1;i<n;i++){
        for(int c=0;c<26;c++){
            dfa[i][c] = dfa[x][c];
        }
        dfa[i][pattern[i]-'a'] = i+1;
        x = dfa[x][pattern[i]-'a'];
    }
}

void build_automata(string s){
    kmp_for_automata(s);

    for(int c=0;c<26;c++){
        for(int i=0;i<s.length();i++){
            paths[i][dfa[i][c]]++;
        }
    }
    paths[sz(s)-1][sz(s)-1] = 26;
}
