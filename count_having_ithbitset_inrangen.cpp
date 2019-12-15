ll func(ll i,ll N){
    ll group = (1LL<<(i+1));
    ll ans = (N+1)/group *(1LL<<i);
 
    ll rem = (N+1)%group;
 
    return ans + max(0LL,rem-(1LL<<i));
}
 