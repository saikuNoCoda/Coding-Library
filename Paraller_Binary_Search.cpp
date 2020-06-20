// https://atcoder.jp/contests/agc002/submissions/14510648
// https://www.spoj.com/problems/METEORS/
// https://ideone.com/dFZD39
// https://codeforces.com/blog/entry/45578


const int MAXN = 1e5 + 10;
int par[MAXN],rankk[MAXN];
int x[MAXN],y[MAXN],z[MAXN];
int u[MAXN],v[MAXN];
int s[MAXN],e[MAXN],mid[MAXN],ans[MAXN];
vector<int> to_check[MAXN];

int parent(int x){
    while(par[x] != x){
        par[x] = par[par[x]];
        x = par[x];
    }
    return x;
}

void solve(){

    int n,m; cin>>n>>m;

    FOR(i,1,m) cin>>u[i]>>v[i];

    int q; cin>>q;

    FOR(i,1,q){
        cin>>x[i]>>y[i]>>z[i];
        s[i] = 1,e[i] = m;
        mid[i] = (s[i] + e[i])/2;
        to_check[mid[i]].push_back(i);
    }

    bool need_loop = true;
    
    while(need_loop){
        need_loop = false;
        FOR(i,1,n) par[i] = i,rankk[i] = 1;

        FOR(i,1,m){
            int uu = u[i],vv = v[i];
            uu = parent(uu),vv = parent(vv);

            if(rankk[uu] < rankk[vv]) swap(uu,vv);

            if(uu != vv) par[vv] = uu,rankk[uu] += rankk[vv];

            while(!to_check[i].empty()){
                int idx = to_check[i].back();
                to_check[i].pop_back();

                int xx = x[idx],yy = y[idx],zz = z[idx];
                xx = parent(xx),yy = parent(yy);

                int tot = 0;
                if(xx == yy) tot = rankk[xx];
                else tot = rankk[xx] + rankk[yy];

                if(tot >= zz) ans[idx] = mid[idx],e[idx] = mid[idx]-1;
                else s[idx] = mid[idx]+1;

                mid[idx] = (s[idx] + e[idx])/2;

                if(s[idx] <= e[idx]){
                    to_check[mid[idx]].push_back(idx);
                    need_loop = true;
                }
            }
        }
    }

    FOR(i,1,q) cout<<ans[i]<<endl;
}



///====================================================================================================================>>>>>>>>>>>>>>>>>>>>>>>>>>

const int MAXN = 3e5 + 10;
vector<int> owner[MAXN];
int req[MAXN];
int l[MAXN],r[MAXN],cnt[MAXN];
int s[MAXN],e[MAXN],mid[MAXN],ans[MAXN];
vector<int> to_check[MAXN];
int n,m,q;
int bit[MAXN];

void update(int idx,int val){
    for(;idx<=m;idx += (idx&(-idx))){
        bit[idx] += val;
    }
}

int query(int idx){
    int ret = 0;
    for(;idx>0;idx -= (idx&(-idx))) ret += bit[idx];
    return ret;
}

void circular_update(int idx){
    if(l[idx] <= r[idx]){
        update(l[idx],cnt[idx]);
        update(r[idx]+1,-cnt[idx]);
    }else {
        update(1,cnt[idx]);
        update(r[idx]+1,-cnt[idx]);
        update(l[idx],cnt[idx]);
    }
}

void solve(){
    cin>>n>>m;

    FOR(i,1,m){
        int x; cin>>x; 
        owner[x].push_back(i);
    }

    FOR(i,1,n) cin>>req[i];

    cin>>q;
    FOR(i,1,q){
        cin>>l[i]>>r[i]>>cnt[i];
    }

    FOR(i,1,n) s[i] = 1,e[i] = q+1,mid[i] = (s[i]+e[i])/2,ans[i] = e[i];
    FOR(i,1,n) to_check[mid[i]].push_back(i);

    bool need_loop = true;

    while(need_loop){
        need_loop = false;
        FOR(i,1,m) bit[i] = 0;

        FOR(i,1,q){
            circular_update(i);

            while(!to_check[i].empty()){
                int idx = to_check[i].back();
                to_check[i].pop_back();

                int sum = 0;
                for(auto sec:owner[idx]){
                    sum += query(sec);
                    if(sum >= req[idx]) break;
                }

                if(sum >= req[idx]) ans[idx] = mid[idx],e[idx] = mid[idx]-1;
                else s[idx] = mid[idx]+1;

                mid[idx] = (s[idx]+e[idx])/2;
                if(s[idx] <= e[idx]){
                    to_check[mid[idx]].push_back(idx);
                    need_loop = true;
                }
            }
        }
    }

    FOR(i,1,n){
        if(ans[i] <= q) cout<<ans[i]<<endl;
        else cout<<"NIE\n";
    }
}
    
