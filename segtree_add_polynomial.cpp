// https://www.hackerrank.com/contests/epiccode/challenges/square-array/copy-from/162270622


const int MAXN = 2e5 + 10;
const int MOD = 1e9 + 7;
int powers[MAXN][3];
int seg[4*MAXN];
int lazy[4*MAXN][3];

tuple<int,int,int> get_coefficients(int l,int sign){
    tuple<int,int,int> ans;
    
    get<0>(ans) = 1;
    get<1>(ans) = ((3-(2*l)%MOD)%MOD + MOD)%MOD;
    get<2>(ans) = ((((l*l)%MOD + 2)%MOD - (3*l)%MOD)%MOD + MOD)%MOD;
    get<0>(ans) = ((get<0>(ans)*sign)%MOD + MOD)%MOD;
    get<1>(ans) = ((get<1>(ans)*sign)%MOD + MOD)%MOD;
    get<2>(ans) = ((get<2>(ans)*sign)%MOD + MOD)%MOD;
    
    return ans;
}

int get_sum(tuple<int,int,int> coeff,int l,int r){
    int a,b,c;
    tie(a,b,c) = coeff;
    int ans = ((powers[r][0] - powers[l-1][0])*a)%MOD;
    ans += ((powers[r][1] - powers[l-1][1])*b)%MOD; ans %= MOD;
    ans += ((powers[r][2] - powers[l-1][2])*c)%MOD; ans %= MOD;
    ans = (ans + MOD)%MOD;
    return ans;
}

void propagate(int node,int s,int e){
    seg[node] = (seg[node] + get_sum({lazy[node][0],lazy[node][1],lazy[node][2]},s,e))%MOD;

    if(s != e){
        FOR(i,0,2) lazy[2*node][i] = (lazy[2*node][i] + lazy[node][i])%MOD;
        FOR(i,0,2) lazy[2*node+1][i] = (lazy[2*node+1][i] + lazy[node][i])%MOD;
    }
    lazy[node][0] = lazy[node][1] = lazy[node][2] = 0;
}

void update(int node,int s,int e,int qs,int qe,tuple<int,int,int> val){
    propagate(node,s,e);
    if(s > e || qs > e || qe < s) return;
    
    if(qs <= s && e <= qe){
        lazy[node][0] = get<0>(val);
        lazy[node][1] = get<1>(val);
        lazy[node][2] = get<2>(val);
        propagate(node,s,e);
        return;
    }

    int mid = (s+e)>>1;
    update(2*node,s,mid,qs,qe,val);
    update(2*node+1,mid+1,e,qs,qe,val);
    
    seg[node] = (seg[2*node]+seg[2*node+1])%MOD;
}

int query(int node,int s,int e,int qs,int qe){
    propagate(node,s,e);
    if(s > e || qs > e || qe < s) return 0;

    if(qs <= s && e <= qe) return seg[node];
    
    int mid = (s+e)>>1;
    return (query(2*node,s,mid,qs,qe) + query(2*node+1,mid+1,e,qs,qe))%MOD;
}

void solve(){
    int n,q; cin>>n>>q;
    FOR(i,1,n){
        powers[i][0] = (powers[i-1][0] + (i*i)%MOD)%MOD;
        powers[i][1] = (powers[i-1][1] + i)%MOD;
        powers[i][2] = (powers[i-1][2] + 1)%MOD;
    }

    FOR(i,1,q){
        int type,l,r; cin>>type>>l>>r;
        if(type == 2) cout<<query(1,1,n,l,r)<<endl;
        else {
            update(1,1,n,l,r,get_coefficients(l,1));
        }
    }
}
    
