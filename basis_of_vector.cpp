
// BASIS OF A VECTOR SPACE MOD 2
// GAUSS ELEMINATION VARIENT
// COPIED FROM https://codeforces.com/blog/entry/68953
// MORE QUESTION AT https://codeforces.com/blog/entry/68953
// https://www.codechef.com/viewsolution/26693249

const ll MAXN = 1e5 + 10;
const ll LOG_A = 62;

ll basis[LOG_A];
ll sz;

void insertVector(ll mask){
    for(ll i=LOG_A;i>=0;i--){
        if((mask&(1LL<<i)) == 0) continue;

        if(!basis[i]){
            basis[i] = mask;
            ++sz;
            return;
        }

        mask ^= basis[i];
    }
}
