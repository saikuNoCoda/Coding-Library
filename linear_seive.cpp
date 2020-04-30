// Problem - http://acm.hdu.edu.cn/showproblem.php?pid=1695
// Soln - https://ideone.com/8a0xzV


const int MAXN = 1e5 + 10;
int M[MAXN],phi[MAXN];
int is_composite[MAXN];
vector<int> prime;

void linear_seive_with_mobius_and_phi(){
    M[1] = 1,phi[1] = 1;

    for(int i=2;i<MAXN;i++){
        if(!is_composite[i]){
            prime.push_back(i);
            M[i] = -1,phi[i] = i-1;
        }
        for(int j=0;j<prime.size() && i*prime[j] < MAXN;j++){
            is_composite[i*prime[j]] = true;
            if(i%prime[j] == 0){
                M[i*prime[j]] = 0;
                phi[i*prime[j]] = phi[i]*prime[j];
                break;
            }else {
                M[i*prime[j]] = M[i]*M[prime[j]];
                phi[i*prime[j]] = phi[i]*phi[prime[j]];
            }
        }
    }
}
