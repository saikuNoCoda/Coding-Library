const ll MAXN = 1e5 + 10;
const ll LG = 20;
ll floor_log[MAXN];
ll sparseT[MAXN][LG];
ll a[MAXN];
ll n;

void preprocess(){
    floor_log[1] = 0;
    FOR(i,2,MAXN-1) floor_log[i] = floor_log[i/2] + 1;
}

void create_sparse_table(){
    FOR(i,1,n) sparseT[i][0] = a[i];

    FOR(j,1,LG-1){
        for(ll i=1;(i+(1<<j)-1)<=n;i++){
            sparseT[i][j] = min(sparseT[i][j-1],sparseT[i+(1<<(j-1))][j-1]);
        }
    }
}

ll query_sparse_table(ll L,ll R){
    ll j = floor_log[R-L+1];
    return min(sparseT[L][j],sparseT[R-(1<<j)+1][j]);
}
