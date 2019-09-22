
// https://www.spoj.com/problems/LPS/
// https://ideone.com/fx3LZx
// MANACHER'S ALGORITHM FOR PALINDROMIC CENTER AT EACH INDEX

const ll MAXN = 1e5 + 10;
string s;
ll d1[MAXN],d2[MAXN];
ll n;

void odd_palindrome(){
    for(ll i=0,l=0,r=-1;i<n;i++){
        ll k = (i>r)?1:min(d1[l+r-i],r-i+1);
        while(0 <= i-k && i+k<n && s[i-k] == s[i+k]){
            k++;
        }
        d1[i] = k--;
        if(i+k>r){
            l = i-k; r = i+k;
        }
    }
}

void even_palindrome(){
    for(ll i=0,l=0,r=-1;i<n;i++){
        ll k = (i>r)?0:min(d2[l+r-i+1],r-i+1);
        while(0 <= i-k-1 && i+k<n && s[i-k-1] == s[i+k]){
            k++;
        }
        d2[i] = k--;
        if(i+k > r){
            l = i-k-1,r = i+k;
        }
    }
}
