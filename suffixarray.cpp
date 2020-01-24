//1) Finding the smallest cyclic shift
// The algorithm above sorts all cyclic shifts (without appending a character to the string), and therefore p[0]
// gives the position of the smallest cyclic shift.

//2) Finding a substring in a string

//3) Comparing two substrings of a string

//4) Longest common prefix of two substrings without additional memory

//5) Number of different substrings
// (n - p[i]) from i = 0 to n-1 - (lcp[i]) for i = 0 to n-2 

string S;
const int MAXN = 2e5 + 10;
int sa[MAXN],pos[MAXN],tmp[MAXN],lcp[MAXN],N,gap;

bool Sufcmp(int i, int j){
	if(pos[i] != pos[j]){
		return pos[i] < pos[j];
	}
	i += gap; j += gap;
	return (i < N && j < N) ? pos[i] < pos[j] : i > j;
}

void buildSA(){
	N = S.size();
	for(int i = 0; i < N; i++){
		sa[i] = i;
		pos[i] = S[i];
	}
	tmp[0] = 0;
	for(gap = 1; ; gap = (gap << 1)){
		sort(sa, sa + N, Sufcmp);
		for(int i = 0; i < N-1; i++) tmp[i+1] = tmp[i] + Sufcmp(sa[i], sa[i+1]);
		for(int i = 0; i < N; i++) pos[sa[i]] = tmp[i];
		if(tmp[N-1] == N-1) break;
	}
}

void buildLCP(){
	N = S.size();
	lcp[N-1] = 0;
	for(int i = 0, k = 0; i < N; i++){
		if(pos[i] != N-1){
			for(int j = sa[pos[i]+1]; S[i+k] == S[j+k]; )
				k++;
			lcp[pos[i]] = k;
			if(k) k--;
		}
	}
}

int count_unique_substrings(string s){
    S = s;
    buildSA(); buildLCP();
    int cnt = 0;
    for(int i=0;i<N;i++) cnt += N - sa[i] - lcp[i]; 
    return cnt;
}