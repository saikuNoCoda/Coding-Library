//https://www.codechef.com/viewsolution/33606632


const int MAXN = 503;
int N,pref_men[MAXN][MAXN],pref_women[MAXN][MAXN];
int inv[MAXN][MAXN],idx[MAXN],wife[MAXN],husband[MAXN];

void stable_marriage(){
    FOR(i,0,N-1) FOR(j,0,N-1) inv[i][pref_women[i][j]] = j;
    fill(idx,idx+N,0);
    fill(husband,husband+N,-1);

    int m,w,dumped;

    FOR(i,0,N-1){
        m = i;
        while(m>=0){
            while(true){
                w = pref_men[m][idx[m]];
                ++idx[m];
                if(husband[w] < 0 || inv[w][m] < inv[w][husband[w]]) break; 
            }

            dumped = husband[w];
            husband[w] = m;
            wife[m] = w;
            m = dumped;
        }
    }
}
