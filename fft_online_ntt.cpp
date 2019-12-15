// https://tanujkhattar.files.wordpress.com/2018/01/onlinefft1.pdf
// F[n] =n−1∑i=1F[i]∗G[n−i]

using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd> & a, bool invert) {
    int n = a.size();

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert) {
        for (cd & x : a)
            x /= n;
    }
}

void multiply(vector<int> const& a, vector<int> const& b,vector<int> &result) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) 
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);

    result.resize(n,0);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real());
}

const int MOD = 663224321;

vector<int> onlineFFT(vector<int> arr,int mySize = -1){
    vector<int> res;
  int need;
  if (mySize != -1)
    need = mySize;
  else
    need = arr.size();

  arr.resize(need + 5);
  res.resize(need + 5); // as (i+1,i+2) which we are doing down

  fill(res.begin(), res.end(), 0);

  res[0] = 1;

  for (ll i = 0; i <= need - 1;
       i++) // we know value of res[i] ,so we'll update forward ones
  {
    // first update using first two elements of arr
    res[i + 1] += (res[i] * arr[1]) % MOD;
    if (res[i + 1] >= MOD)
      res[i + 1] -= MOD;
    res[i + 2] += (res[i] * arr[2]) % MOD;
    if (res[i + 2] >= MOD)
      res[i + 2] -= MOD;

    // now go update using all blocks of size
    // i%(2^j)==0,j>0,convolve(arr[2^j+1,2^(2*j)],res[i-2^j,i-1])
    for (int pw = 2; (i % pw == 0) && ((pw + 1) < need) && i;pw = pw * 2) { // as if(2^j+1>n) no use...
      vector<int> A, B, C;
      copy(arr.begin() + pw + 1, arr.begin() + min(need - 1, 2 * pw) + 1,
           back_inserter(A));
      copy(res.begin() + i - pw, res.begin() + i, back_inserter(B));
      multiply(A, B, C);

      ll offset = i + 1;
      ll lim = min((ll)C.size(), need - offset);
      for (ll i = 0; i < lim; i++) {
        res[i + offset] += C[i];
        if (res[i + offset] >= MOD)
          res[i + offset] -= MOD;
      }
    }
  }
  return res;
}


const int MOD = 663224321;
const int LG = 19;
const int maxn = (1<<LG);
const int G = 3;
int W[maxn>>1],invW[maxn>>1];

int power(int x,int y,int MOD = ::MOD){
    int res = 1;

    while(y>0){
        if(y&1) res = (res*x)%MOD;
        x = (x*x)%MOD;
        y >>= 1;
    }
    return res;
}

void precompute_powers(){
    W[0] = invW[0] = 1;
    int base = power(G, (MOD-1)/maxn, MOD);
    int inv_base = power(base, MOD-2, MOD);
    for(int i = 1;i<maxn/2;i++){
        W[i] = (W[i-1] * 1LL * base) % MOD;
        invW[i] = (invW[i-1] * 1LL * inv_base) % MOD;
    }
}

void ntt (vector<int> &a, bool invert) {
    int n = (int) a.size();
    for (int i=1, j=0; i<n; ++i) {
        int bit = n >> 1;
        for (; j>=bit; bit>>=1)
            j -= bit;
        j += bit;
        if (i < j)
            swap (a[i], a[j]);
    }
 
    for (int len=2; len<=n; len<<=1) {
        for (int i=0; i<n; i+=len) {
            int ind = 0, add = maxn/len;
            for (int j=0; j<len/2; ++j) {
                int u = a[i+j],  v = (a[i+j+len/2] * 1LL * (invert?invW[ind]:W[ind])) % MOD;
                a[i+j] = (u + v) % MOD;
                a[i+j+len/2] = (u - v + MOD) % MOD;
                ind += add;
            }
        }
    }
    if (invert){
        int inv_n = power(n, MOD-2, MOD);
        for (int i=0; i<n; ++i)
            a[i] = (a[i] * 1LL * inv_n) % MOD;
    }
}
 

void multiply(vector<int> const& a, vector<int> const& b,vector<int> &result) {
    vector<int> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) 
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    ntt(fa, false);
    ntt(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] = (fa[i]*fb[i])%MOD;
        
    ntt(fa, true);

    result.resize(n,0);
}
