
const ll MAXN = 1e5 + 10;
const ll LG = 20;
const ll INF = 1e9;

set<ll> graph[MAXN];
ll paren[MAXN],subtree[MAXN],level[MAXN];
ll par[LG][MAXN];
ll n,m;

// FOR 0TH PARENT AND LEVEL AND PAR DP
void dfs1(ll u,ll p){
    
    par[0][u] = p;
    level[u] = level[p] + 1;
    FOR(i,1,LG-1) par[i][u] = par[i-1][par[i-1][u]];
    
    for(ll v:graph[u]){
        if(v == p) continue;
        dfs1(v,u);
    }
}

ll lca_(ll a,ll b){
    if(level[a] < level[b]) swap(a,b);

    ll diff = level[a] - level[b];

    FOR(i,0,LG-1) if(diff&(1<<i)) a = par[i][a];

    if(a == b) return a;

    RFOR(i,0,LG-1){
        if(par[i][a] != par[i][b]) a = par[i][a],b = par[i][b];
    }

    return par[0][a];
}

ll dist(ll a,ll b){
    return level[a] + level[b] - 2*level[lca_(a,b)];
}

ll nodes;

void dfs_for_subtree(ll u,ll p){
    subtree[u] = 1;
    nodes++;
    for(ll v:graph[u]){
        if(v == p) continue;
        dfs_for_subtree(v,u);
        subtree[u] += subtree[v];
    }
}

ll dfs_for_centroid(ll u,ll p){
    for(ll v:graph[u]){
        if(v != p && subtree[v] > nodes/2) return dfs_for_centroid(v,u);
    }
    return u;
}

void decompose(ll root,ll p){
    nodes = 0;
    dfs_for_subtree(root,root);
    ll centroid = dfs_for_centroid(root,root);
    paren[centroid] = p;

    for(ll v:graph[centroid]){
        graph[v].erase(centroid);
        decompose(v,centroid);
    }

    graph[centroid].clear();
}
