#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 5e5 + 10 , lgN = 20 + 5 ;

struct data {
	int pl , sum , le , ri ;

	friend bool operator <(data x , data y) {return x.sum < y.sum || (x.sum == y.sum && x.pl > y.pl) ;}
} ;

std::priority_queue<data> pq ;

int n , m , L , R , a[MAX_N] , s[MAX_N] , lgk[MAX_N] , f[MAX_N][lgN] ;

int comp(int x , int y) {
	if (s[x] > s[y]) return x ;
	else return y ;
}

int find(int x , int y) {
	int len = (y - x + 1) , p = lgk[len] ;

	return comp(f[x][p] , f[y - (1 << p) + 1][p]) ;
}

int main() {
	scanf("%d %d %d %d" , &n , &m , &L , &R) ;
	for (int i = 1 ; i <= n ; ++i) scanf("%d" , &a[i]) ;
	s[0] = lgk[1] = 0 ;
	for (int i = 1 ; i <= n ; ++i) s[i] = s[i - 1] + a[i] ;
	for (int i = 2 ; i <= n ; ++i) lgk[i] = lgk[i >> 1] + 1 ;

	///

	for (int i = 1 ; i <= n ; ++i) f[i][0] = i ;
	for (int j = 1 ; (1 << j) <= n ; ++j)
		for (int i = 1 ; i <= n ; ++i) {
			int p = i + (1 << (j - 1)) ;
			if (p <= n) f[i][j] = comp(f[i][j - 1] , f[p][j - 1]) ;
			else f[i][j] = f[i][j - 1] ;
		}

	for (int i = 1 ; i <= n ; ++i) {
		int le = i + L - 1 , ri = std::min(i + R - 1 , n) ;
		if (le > ri) break ;

		int a = find(le , ri) ;
		pq.push((data){i , s[a] - s[i - 1] , le , ri}) ;
	}

	///

	ll ans = 0 ;
	for (; m-- ;) {
		data tmp = pq.top() ;
		ans += tmp.sum ; pq.pop() ;

		int a = find(tmp.le , tmp.ri) , i = tmp.pl , t ;
		if (tmp.le != a) {
			t = find(tmp.le , a - 1) ;
			pq.push((data){i , s[t] - s[i - 1] , tmp.le , a - 1}) ;
		}
		if (tmp.ri != a) {
			t = find(a + 1 , tmp.ri) ;
			pq.push((data){i , s[t] - s[i - 1] , a + 1 , tmp.ri}) ;
		}
	}

	printf("%lld\n" , ans) ;

	return 0 ;
}