const ll MAXB = (1<<20) + 10;
const ll MAXN = 1e6 + 10;
ll arr[MAXN];
ll a[MAXB];

void solve(){
    ll n; cin>>n;

    FOR(i,1,n){
        cin>>arr[i]; a[arr[i]]++;
    }

    FOR(i,0,19){
        FOR(mask,0,(1<<20)-1){
            if(mask&(1<<i)) a[mask] = a[mask] + a[mask^(1<<i)];
        }
    }
}       
