
int extended_euclidean(int a,int b,int &x,int &y){
    x = 1,y = 0;
    int x1 = 0,y1 = 1,a1 = a,b1 = b;
    while(b1){
        int q = a1/b1;
        tie(x,x1) = make_tuple(x1,x-q*x1);
        tie(y,y1) = make_tuple(y1,y-q*y1);
        tie(a1,b1) = make_tuple(b1,a1-q*b1);
    }
    return a1;
}

pair<int,int> CRT(vector<int> A,vector<int> M){
    if(A.size() != M.size()) return {-1,-1};

    int n = A.size();

    int a1 = A[0],m1 = M[0];

    for(int i=1;i<n;i++){
        int a2 = A[i],m2 = M[i];
        int p,q;
        extended_euclidean(m1,m2,p,q);
        int mod = m1*m2;
        int x = ((a1*m2*q)%mod + (a2*m1*p)%mod)%mod; 
        a1 = x,m1 = m1*m2;
    }
    if(a1 < 0) a1 += m1;
    return {a1,m1};
}
