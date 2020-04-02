
struct node{
    int cnt;
    node *lft,*rgt;

    node() {}
    node(int c){
        cnt = c; lft = rgt = NULL;
    }
};

node *seg[MAXN];

void build(node *n,int s,int e){
    if(s >= e) return;

    node *lft = new node(0);
    node *rgt = new node(0);

    int mid = (s+e)>>1;
    build(lft,s,mid); build(rgt,mid+1,e);

    n->lft = lft; n->rgt = rgt;
}

void update(node *prev,node *cur,int s,int e,int idx){
    if(s > e) return;

    if(s == e){
        cur->cnt = prev->cnt + 1;
        return;
    }

    int mid = (s+e)>>1;

    node *new_node = new node(0);

    if(idx <= mid){
        cur->lft = new_node;
        cur->rgt = prev->rgt;
        update(prev->lft,cur->lft,s,mid,idx);
    }
    else {
        cur->rgt = new_node;
        cur->lft = prev->lft;
        update(prev->rgt,cur->rgt,mid+1,e,idx);
    }

    cur->cnt = cur->lft->cnt + cur->rgt->cnt;
}

node* query(node *n,int s,int e,int qs,int qe){
    node *temp = new node(0);

    if(qs > e || qe < s || s > e) return temp;

    if(qs <= s && e <= qe){
        return n;
    }

    int mid = (s+e)>>1;

    node *lft = query(n->lft,s,mid,qs,qe);
    node *rgt = query(n->rgt,mid+1,e,qs,qe);

    temp->cnt = lft->cnt + rgt->cnt;
    return temp;
}

void preprocess(){
    FOR(i,0,n) seg[i] = new node(0);
    build(seg[0],1,n);
}
