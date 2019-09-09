// DINIC's ALGORITHM
// MAXFLOW ALGORITHM
// O(V^2 * E)

#define ll long long int

const ll MAXN = 205;
const ll INF = 1e8;

queue<ll> que;

struct edge {
    ll v,flow,C,rev;
};

vector<edge> graph[MAXN];
ll level[MAXN],start[MAXN];

void addEdge(ll u,ll v,ll C){
    edge a = {v,0,C,(ll)graph[v].size()};
    edge b = {u,0,0,(ll)graph[u].size()};

    graph[u].push_back(v);
    graph[v].push_back(u);
}

bool bfs(ll s,ll t){
    for(ll i=0;i<MAXN;i++) level[i] = -1;

    que.push(s); level[s] = 0;

    while(!que.empty()){
        ll u = que.front();
        que.pop();

        for(auto vv:graph[u]){
            if(level[vv.v] == -1 && vv.flow < vv.C){
                level[vv.v] = level[u] + 1;
                que.push(vv.v);
            } 
        }
    }

    if(level[t] == -1) return false;
    else return true;
}

ll dfs(ll u,ll t,ll cflow){
    if(u == t) return cflow;

    for(;start[u]<graph[u].size();start[u]++){
        edge &ef = graph[u][start[u]];

        if(level[ef.v] == level[u] + 1 && ef.flow < ef.C){
            ll new_flow = min(cflow,ef.C - ef.flow);
            ll final_flow = dfs(ef.v,t,new_flow);

            if(final_flow > 0){
                ef.flow += final_flow;
                graph[ef.v][ef.rev].flow -= final_flow;
                return final_flow;
            }
        }
    }

    return 0;
}

ll maxflow(ll s,ll t){
    ll ans = 0;

    while(bfs(s,t)){
        for(ll i=0;i<MAXN;i++) start[i] = 0;

        while(true){
            ll new_flow = dfs(s,t,INF);
            if(new_flow <= 0) break;
            ans += new_flow;
        }
    }

    return ans;
}