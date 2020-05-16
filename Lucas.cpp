// https://www.codechef.com/viewsolution/33124403
// https://forthright48.com/lucas-theorem-proof-and-applications/
//  Given N, K and prime P, if we write N and K in base P form as:
// N=n0+n1×P+n1×P2+⋯+nx×Px
// K=k0+k1×P+k1×P2+⋯+kx×Px
// where x is some non-negative number and 0≤ni,ki<P for 0≤i≤x, then
// (NK)≡∏i=0x(niki)modP

const int MAXN = 1e5 + 10;

int power(int x,int y,int mod){
    int res = 1;
    while(y){
        if(y&1) res = (res*x)%mod;
        x = (x*x)%mod; y >>= 1;
    }
    return res;
}

int fact[MAXN],invfact[MAXN];

void calc(int mod){
    const int LIM = min(MAXN-1,mod-1);
    fact[0] = invfact[0] = 1;
    FOR(i,1,LIM) fact[i] = (fact[i-1]*i)%mod;
    invfact[LIM] = power(fact[LIM],mod-2,mod);
    RFOR(i,0,LIM-1) invfact[i] = ((i+1)*invfact[i+1])%mod;
}

int nCr(int n,int r,int mod){
    if(n < r) return 0;
    int ret = (fact[n]*invfact[r])%mod;
    ret = (ret*invfact[n-r])%mod;
    return ret;
}

int lucas_nCr(int n,int r,int mod){
    calc(mod); int res = 1;
    while(n or r){
        const int ni = n%mod,ri = r%mod;
        res = (res*nCr(ni,ri,mod))%mod;
        n /= mod,r /= mod;
    }
    return res;
}
