const ll MAXN = 2e5 + 10,L = 25;

vector<ll> graph[MAXN];
ll level[MAXN];
ll parent[L][MAXN];

void dfs(ll u,ll p){
	level[u] = level[p] + 1;
	parent[0][u] = p;
	
	for(ll v:graph[u]){
		if(v == p) continue;
		dfs(v,u);
	}
}

ll lca_(ll a,ll b){
	if(level[a]<level[b]) swap(a,b);
 
	ll diff = level[a]-level[b];
 
	RFOR(i,0,L-1) if(diff&(1<<i)) a = parent[i][a];
 
	if(a == b) return a;
 
	RFOR(i,0,L-1){
		if(parent[i][a] != parent[i][b]){
			a = parent[i][a];
			b = parent[i][b];
		}
	}
	return parent[0][a];
}
 
ll dist(ll a,ll b){
	return level[a] + level[b] - 2*level[lca_(a,b)];
}
 
void process_lca(){
    FOR(i,1,L-1){
		FOR(j,1,MAXN-1){
			parent[i][j] = parent[i-1][parent[i-1][j]];
		}
	}
}
