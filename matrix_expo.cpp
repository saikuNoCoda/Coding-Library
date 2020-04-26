// NORMAL MATRIX EXPO

#define ll long long int
#define ZERO(a) memset((a),0,sizeof((a)))

const ll MAXN = 100;
ll mat[MAXN][MAXN];
const ll MOD = 1e9 + 7;

void mul(ll A[][MAXN],ll B[][MAXN]){
    ll C[MAXN][MAXN];

    FOR(i,0,MAXN-1) FOR(j,0,MAXN-1) C[i][j] = 0;

    FOR(i,1,MAXN-1){
        FOR(j,1,MAXN-1){
            FOR(k,1,MAXN-1){
                C[i][j] = (C[i][j] + (A[i][k]*B[k][j])%MOD)%MOD;
            }
        }
    }

    FOR(i,1,MAXN-1) FOR(j,1,MAXN-1) A[i][j] = C[i][j];
}

void power_mat(ll A[][MAXN],ll p){
    ll res[MAXN][MAXN];
    ZERO(res);

    FOR(i,1,MAXN-1) res[i][i] = 1;

    while(p){
        if(p&1) mul(res,A);
        mul(A,A);
        p >>= 1;
    }
    FOR(i,1,MAXN-1) FOR(j,1,MAXN-1) A[i][j] = res[i][j];
}


// MATRIX MUL MOD 2

const int MAXN = 500;
bitset<MAXN> A[MAXN],ans[MAXN],tmp[MAXN];

void mat_mul_xor(bitset<MAXN> M1[MAXN],bitset<MAXN> M2[MAXN]){
    bitset<MAXN> row[MAXN],col[MAXN];

    FOR(i,0,MAXN-1) FOR(j,0,MAXN-1) row[i][j] = M1[i][j];
    FOR(i,0,MAXN-1) FOR(j,0,MAXN-1) col[j][i] = M2[i][j];
    
    FOR(i,0,MAXN-1) FOR(j,0,MAXN-1) tmp[i][j] = ((row[i]&col[j]).count())&1;
}
