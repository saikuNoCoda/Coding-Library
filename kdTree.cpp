
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

// https://www.spoj.com/problems/FAILURE/
