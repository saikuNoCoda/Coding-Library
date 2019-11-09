const ll MAXN = 1e5 + 10;
pair<ll,ll> a[MAXN];
 
pair<ll,ll> seg_min[4*MAXN];
pair<ll,ll> seg_max[4*MAXN];
 
void update(ll node,ll s,ll e,ll pos,ll val){
 
    if(s > e) return;

    if(s == e){
        seg_min[node] = {val,pos};
        seg_max[node] = {val,pos};
        return;
    }
 
    ll mid = (s+e)>>1;
    if(pos <= mid) update(2*node,s,mid,pos,val);
    else update(2*node+1,mid+1,e,pos,val);
 
    seg_max[node] = max(seg_max[2*node],seg_max[2*node+1]);
    seg_min[node] = min(seg_min[2*node],seg_min[2*node+1]);   
}
 
pair<ll,ll> query_min(ll node,ll s,ll e,ll qs,ll qe){
    if(s > e || qs > e || qe < s) return {1e10,0};
 
    if(qs <= s && e <= qe){
        return seg_min[node];
    }
 
    ll mid = (s+e)>>1;
    return min(query_min(2*node,s,mid,qs,qe),query_min(2*node+1,mid+1,e,qs,qe));
}
 
pair<ll,ll> query_max(ll node,ll s,ll e,ll qs,ll qe){
    if(s > e || qs > e || qe < s) return {0,0};
 
    if(qs <= s && e <= qe){
        return seg_max[node];
    }
 
    ll mid = (s+e)>>1;
    return max(query_max(2*node,s,mid,qs,qe),query_max(2*node+1,mid+1,e,qs,qe));
}