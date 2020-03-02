 
//Hierholzer's algo for finding euler path or circuit in a directed graph
//Link: http://iampandiyan.blogspot.com/2013/10/c-program-to-find-euler-path-or-euler.html
//Time complexity: O(V + E)

const int MAXN = 2e5 + 10;
vector<int> graph[MAXN];
int indegree[MAXN],outdegree[MAXN];
vector<int> tour;

bool preconditions(int &src){
    int cnt1 = 0,cnt_1 = 0;

    for(int i=0;i<n;i++){
        if(abs(indegree[i] - outdegree[i]) >= 2) return 0;
        if(indegree[i] - outdegree[i] == -1) src = i;
        cnt1 += indegree[i] - outdegree[i] == 1;
        cnt_1 += indegree[i] - outdegree[i] == -1;
    }

    if(!cnt_1){
        for(int i=0;i<n;i++) if(outdegree[i]) {src = i; break;}
    }

    return (cnt1 == cnt_1 && cnt1 <= 1);
}

void dfs(int u){
    while(graph[u].size()){
        int v = graph[u].back();
        graph[u].pop_back();
        dfs(v);
    }
    tour.push_back(u);
}

bool Euler(){
    int src = 0;
    if(!preconditions(src)) return 0;
    dfs(src);
    for(int i=0;i<n;i++) if(graph[i].size()) return 0;
    reverse(tour.begin(),tour.end());
    return 1;
}
