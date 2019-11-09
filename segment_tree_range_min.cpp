const ll MAXN = 1e5 + 10;
ll seg[4*MAXN],lazy[4*MAXN];

void propogate(ll node,ll s,ll e){
    seg[node] = min(seg[node],lazy[node]);
 
    if(s != e){
        lazy[2*node] = min(lazy[node],lazy[2*node]);
        lazy[2*node+1] = min(lazy[node],lazy[2*node+1]);
    }
}
 
void update(ll node,ll s,ll e,ll qs,ll qe,ll val){
    propogate(node,s,e);
    
    if(s > e || qs > e || qe < s) return;
 
    if(qs <= s && e <= qe){
        lazy[node] = min(lazy[node],val);
        propogate(node,s,e);
        return;
    }
 
    ll mid = (s+e)>>1;
    update(2*node,s,mid,qs,qe,val);
    update(2*node+1,mid+1,e,qs,qe,val);
 
    seg[node] = min(seg[2*node],seg[2*node+1]);
}
 
const ll INF = 1e17;
ll query(ll node,ll s,ll e,ll pos){
    propogate(node,s,e);
    if(s > e) return INF;
 
    if(s == e){
        return seg[node];
    }
 
    ll mid = (s+e)>>1;
    if(pos <= mid) return query(2*node,s,mid,pos);
    else return query(2*node+1,mid+1,e,pos);
}