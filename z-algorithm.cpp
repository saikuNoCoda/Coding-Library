
//https://atcoder.jp/contests/abc141/submissions/7546518

const ll MAXN = 1e5 + 10;
ll z[MAXN];

void z_function(string s){
    ll n = s.size();
 
    FOR(i,0,n+1) z[i] = 0;
 
    for(ll i=1,l=0,r=0;i<n;i++){
        if(i<=r) z[i] = min(r-i+1,z[i-l]);
        while(i+z[i]<n && s[z[i]] == s[i+z[i]]) z[i]++;
        if(i+z[i]-1>r) l=i,r=i+z[i]-1;
    }
}