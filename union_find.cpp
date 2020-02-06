
const int MAXN = 1e5 + 10;
int parent[MAXN],rankk[MAXN];

void init(){
    FOR(i,1,MAXN-1) parent[i] = i,rankk[i] = 1;
}

int par(int x){
    while(parent[x] != x){
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

void unionn(int x,int y){
    x = par(x),y = par(y);
    if(x == y) return;
    if(rankk[y] > rankk[x]) swap(x,y);
    rankk[x] += rankk[y];
    parent[y] = parent[x];
}
