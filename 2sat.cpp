// https://www.codechef.com/viewsolution/28213034
// https://www.codechef.com/viewsolution/28213915

const int MAXN = 2e5 + 10;
int n,cnt;
vector<int> graph[MAXN],Rgraph[MAXN];
bool visit[MAXN];
vector<int> order;
int comp[MAXN];

struct TwoSat {
    void init(){
        order.clear();
        for(int i=0;i<=2*n;i++){
            graph[i].clear(); Rgraph[i].clear();
        }
    }

    void add(int u,int v){
        graph[u].push_back(v);
        Rgraph[v].push_back(u);
    }

    void dfs1(int u){
        visit[u] = true;
        for(int v:graph[u]){
            if(!visit[v]) dfs1(v);
        }
        order.push_back(u);
    }

    void dfs2(int u,int c){
        comp[u] = c;
        for(int v:Rgraph[u]){
            if(comp[v] == -1) dfs2(v,c);
        }
    }

    int solve(vector<int> &ans){
        memset(visit,0,sizeof(visit));

        for(int i=1;i<=2*n;i++) if(!visit[i]) dfs1(i);

        memset(comp,-1,sizeof(comp));
        reverse(order.begin(),order.end());

        int grp = 1;
        for(int x:order){
            if(comp[x] == -1) dfs2(x,grp++);
        }

        // COMPARING NEGATIONS COMPONENTS
        for(int i=1;i<=n;i++) if(comp[i] == comp[i+n]) return 0;

        ans.clear();

        for(int i=1;i<=n;i++){
            int choose = (comp[i] > comp[i+n])?i:(n+i);
            ans.push_back(choose);
        }

        return 1;
    }
};