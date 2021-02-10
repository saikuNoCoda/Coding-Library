
const int MAXN = 1<<17;
const int INF = 2000000000000000007;

struct point {
    int p[2];
    bool operator !=(const point &a) const {
        return !(p[0]==a.p[0] && p[1]==a.p[1]);
    }
};

struct kdNode {
    int axis,value;
    point p;
    kdNode *left, *right;
};

struct cmpPoints {
    int axis;
    cmpPoints() {}
    cmpPoints(int x): axis(x) {}
    bool operator () (const point &a,const point &b) const {
        return a.p[axis]<b.p[axis];
    }
};

typedef kdNode* nodePtr;

point arr[MAXN],pts[MAXN];
nodePtr root;
int n,ans;

int squaredDistance(point a,point b){
    int ans = 0;
    for(int i=0;i<2;i++) ans += (a.p[i]-b.p[i])*(a.p[i]-b.p[i]);
    return ans;
}

void buildTree(nodePtr &node,int s,int e,int axis){
    if(s > e){
        node = NULL;
        return;
    }

    node = new kdNode();

    if(s == e){
        node->p = arr[s];
        node->left = NULL;
        node->right = NULL;
        return;
    }

    int mid = (s+e)/2;

    nth_element(arr+s,arr+mid,arr+e+1,cmpPoints(axis));
    node->value = arr[mid].p[axis];
    node->axis = axis;

    buildTree(node->left,s,mid,axis^1);
    buildTree(node->right,mid+1,e,axis^1);
}

void nearestNeighbor(nodePtr node,point q,int &ans){
    if(node == NULL) return;

    if(node->left == NULL && node->right == NULL){
        if(q != node->p) ans = min(ans,squaredDistance(node->p,q));
        return;
    }

    if(q.p[node->axis] <= node->value){
        nearestNeighbor(node->left,q,ans);
        if(q.p[node->axis] + sqrt(ans) >= node->value){
            nearestNeighbor(node->right,q,ans);
        }
    }else {
        nearestNeighbor(node->right,q,ans);
        if(q.p[node->axis]-sqrt(ans) <= node->value){
            nearestNeighbor(node->left,q,ans);
        }
    }
}



struct vpNode {
    int threshold;
    pair<int,int> center;
    vpNode *left, *right;
};

typedef vpNode *nodePtr;

int n,ans;
pair<int,int> pts[MAXN],arr[MAXN];
nodePtr root;

int squaredDistance(pair<int,int> a,pair<int,int> b){
    return (a.first-b.first)*(a.first-b.first) + (a.second-b.second)*(a.second-b.second);
}

struct cmpPoints{
    pair<int,int> a;
    cmpPoints() {}
    cmpPoints(pair<int,int> p): a(p) {}
    bool operator () (const pair<int,int> &x,const pair<int,int> &y) const {
        return squaredDistance(a,x)<squaredDistance(a,y);
    }
};

void build(nodePtr &node,int s,int e){
    if(s > e){
        node = NULL;
        return;
    }

    node = new vpNode();

    if(s == e){
        node->threshold = 0;
        node->center=arr[s];
        node->left = NULL;
        node->right = NULL;
        return;
    }

    int pos = s+rand()%(e-s+1);
    swap(arr[s],arr[pos]);
    node->center = arr[s];
    sort(arr+s+1,arr+e+1,cmpPoints(arr[s]));
    node->threshold = squaredDistance(arr[s],arr[(s+e)>>1]);
    build(node->left,s,(s+e)>>1);
    build(node->right,((s+e)>>1)+1,e);
}

void query(nodePtr &node,pair<int,int> q,int &ans){
    if(node == NULL) return;
    if(node->center != q) ans = min(ans,squaredDistance(node->center,q));
    if(node->left == NULL && node->right == NULL) return;

    if(squaredDistance(q,node->center) <= node->threshold){
        query(node->left,q,ans);
        if(sqrt(squaredDistance(node->center,q)) + sqrt(ans) > sqrt(node->threshold)){
            query(node->right,q,ans);
        }
    }else {
        query(node->right,q,ans);
        if(sqrt(squaredDistance(node->center,q))- sqrt(ans)<sqrt(node->threshold)){
            query(node->left,q,ans);
        }
    }
}


// https://www.spoj.com/problems/FAILURE/
