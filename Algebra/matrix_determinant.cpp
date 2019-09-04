/*
	Coding Library - G.O.A.T. Remembers

	Calculating the determinant of a matrix
	Complexity - O(n^3)
	Pre-req - Gauss-Jordan Elimination
*/

/*****************************************************

@author: vichitr
Compiled On: 5th Sept 2019

*****************************************************/
#include<bits/stdc++.h>
#define MAX 9223372036854775807
#define endl "\n"
#define ll long long
#define int long long
#define double long double
#define pb push_back
#define pf pop_front
#define mp make_pair
#define ip pair<int, int>

#define loop(i,n) for(int i=0;i<n;i++)
#define loops(i,s,n) for(int i=s;i<=n;i++)
#define fast ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(NULL)
using namespace std;

const ll MOD = 1e9+7;
const ll SZ = 107;
const ll N = 1e6+7;


double det(vector<vector<double>> &mat)
{
	double det = 1;

	int n = mat.size();
	// int m = mat[0].size();

	for(int i=0;i<n;i++)
	{
		int sel = i;
		for(int j=i+1;j<n;j++)
		{
			if(abs(mat[j][i])>abs(mat[sel][i]))
				sel = j;
		}

		if(mat[sel][i]==0)
		{
			return 0.0;
		}
		if(sel != i){
			swap(mat[i], mat[sel]);
			det *= -1.0;
		}
		det *= mat[i][i];

		for(int j=i+1;j<n;j++)
			mat[i][j] /= mat[i][i];

		for(int j=0;j<n;j++)
		{
			if(i==j) continue;
			for(int k=i+1;k<n;k++)
			{
				mat[j][k] -= mat[j][i] * mat[i][k];
			}
		}
	}
	return det;
}

void solve()
{
	int n; cin>>n;
	vector<vector<double>> v(n, vector<double>(n));
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			cin>>v[i][j];
	cout<<det(v)<<endl;
}

signed main()
{
	int t = 1; 
	// cin>>t;
	while(t--)
		solve();
	return 0;
}