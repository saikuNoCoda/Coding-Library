// EdmondsKarp Algorithm
// MAXFLOW
// O(V * E^2)

#define ll long long int

const ll MAXN = 205;
const ll INF = 1e8;

ll n;
ll capacity[MAXN][MAXN];
vector<ll> graph[MAXN];
ll parent[MAXN];

ll bfs(ll s,ll t){
    FOR(i,0,n) parent[i] = -1;
    queue<pair<ll,ll>> q;
    q.push({s,INF});

    while(!q.empty()){
        ll u = q.front().first;
        ll flow = q.front().second;
        q.pop();

        for(ll v:graph[u]){
            if(parent[v] == -1 && capacity[u][v]){
                parent[v] = u;
                ll new_flow = min(flow,capacity[u][v]);
                if(v == t) return new_flow;
                q.push({v,new_flow});
            }
        }
    }

    return 0;
}

ll maxflow(ll s,ll t){
    ll flow = 0;
    ll new_flow;

    while(new_flow = bfs(s,t)){
        flow += new_flow;
        ll curr = t;

        while(curr != s){
            ll prev = parent[curr];
            capacity[prev][curr] -= new_flow;
            capacity[curr][prev] += new_flow;
            curr = prev;
        }
    }

    return flow;
}