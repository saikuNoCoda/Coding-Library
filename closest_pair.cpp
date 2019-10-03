 
const ll MAXN = 1e5 + 10;
const ll INF = 1e9;
pair<ll,ll> A[MAXN];
 
bool comp(pair<ll,ll> a,pair<ll,ll> b){
    return a.second < b.second;
}
 
ll fnc(ll L,ll R){
    if(L == R) return INF;
    ll M = (L+R)>>1;
 
    ll d = min(fnc(L,M),fnc(M+1,R));
    sort(A+L,A+R+1);
 
    ll midx = A[(L+R)>>1].first;
    vector<pair<ll,ll>> v;
 
    FOR(i,L,R){
        if((midx - A[i].first)*(midx - A[i].first) < d) v.push_back(A[i]);
    }
 
    sort(all(v),comp);
 
    for(ll i=0;i<v.size();i++){
        for(ll j=i+1;j<v.size();j++){
            if((v[i].second - v[j].second)*(v[i].second - v[j].second) >= d) break;
            d = min(d,(v[i].first - v[j].first)*(v[i].first - v[j].first) + (v[i].second - v[j].second)*(v[i].second - v[j].second));
        }
    }
    return d;
}