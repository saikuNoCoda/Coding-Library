
const int MAXN = 1e5 + 10;
int n,m,cnt = 0;
int a[MAXN],comp[MAXN],visit[MAXN];
vector<int> graph[MAXN],Rgraph[MAXN],component[MAXN];
vector<int> todo;

void dfs(int u){
    visit[u] = 1;
    for(int v:graph[u]){
        if(visit[v]) continue;
        dfs(v);
    }
    todo.push_back(u);
}

void dfs2(int u,int val){
    comp[u] = val;
    component[val].push_back(a[u]);

    for(int v:Rgraph[u]){
        if(comp[v] == -1)
            dfs2(v,val);
    }
}

void sccAddE(int u,int v){
    graph[u].push_back(v);
    Rgraph[v].push_back(u);
}

void scc(){
    for(int i=1;i<=n;i++) comp[i] = -1;

    for(int i=1;i<=n;i++) if(!visit[i]) dfs(i);

    reverse(todo.begin(),todo.end());

    for(int x:todo){
        if(comp[x] == -1){
            dfs2(x,x); cnt++;
        }
    }
}

// https://codeforces.com/contest/1239/submission/66564620
// https://codeforces.com/contest/894/submission/66607463