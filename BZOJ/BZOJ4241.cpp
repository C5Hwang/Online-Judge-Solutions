#include <map>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define ed(x) (x * siz)
#define st(x) ((x - 1) * siz + 1)
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 , MAX_B = 400 + 10 ;

std::map<int , int> bh ;

int ap[MAX_N] , f[MAX_B][MAX_B] , s[MAX_B][MAX_N] ;
int n , m , tot , siz , a[MAX_N] , num[MAX_N] , bk[MAX_N] ;

///

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

///

int count(int x , int y , int a) {
	if (x > y) return 0 ;

	return s[y][a] - s[x - 1][a] ;
}

void update(int &res , ll &sum , int x , int y , int L , int R) {
	for (int i = L ; i <= R ; ++i) {
		int t = a[i] ;
		if (!ap[t]) continue ;

		ll s = (count(x , y , t) + ap[t]) * (ll)num[t] ;
		if (s > sum) sum = s , res = t ;
		ap[t] = 0 ;
	}
}

ll work(int x , int y) {
	int x1 , y1 , x2 , y2 , bx , by ;

	x1 = x ; y1 = std::min(ed(bk[x]) , y) ;
	if (bk[x] != bk[y]) x2 = st(bk[y]) , y2 = y ;
	else x2 = 1 , y2 = 0 ;
	if (bk[x] + 1 < bk[y]) bx = bk[x] + 1 , by = bk[y] - 1 ;
	else bx = 1 , by = 0 ;

	for (int i = x1 ; i <= y1 ; ++i) ++ap[a[i]] ;
	for (int i = x2 ; i <= y2 ; ++i) ++ap[a[i]] ;

	int res = bx > by ? 0 : f[bx][by] ;
	ll sum = (count(bx , by , res) + ap[res]) * (ll)num[res] ;

	update(res , sum , bx , by , x1 , y1) ;
	update(res , sum , bx , by , x2 , y2) ;

	return sum ;
}

///

int main() {
	n = read() ; m = read() ; siz = (int)sqrt(n) ;
	for (int i = 1 ; i <= n ; ++i) {
		int t = read() ;

		if (!bh.count(t)) {
			bh[t] = ++tot ;
			num[tot] = t ;
		}
		a[i] = bh[t] ;
	}
	for (int i = 1 ; i <= n ; ++i) bk[i] = (i - 1) / siz + 1 ;

	///

	for (int i = 1 ; i <= bk[n] ; ++i) {
		int L = st(i) , R = std::min(ed(i) , n) ;

		for (int j = L ; j <= R ; ++j) ++ap[a[j]] ;

		for (int j = 1 ; j <= tot ; ++j) {
			s[i][j] = s[i - 1][j] + ap[j] ;
			ap[j] = 0 ;
		}
	}

	for (int i = 1 ; i <= bk[n] ; ++i)
		for (int j = i ; j <= bk[n] ; ++j) {
			int L = st(j) , R = std::min(ed(j) , n) ;
			for (int k = L ; k <= R ; ++k) ++ap[a[k]] ;

			int res = i == j ? 0 : f[i][j - 1] ;
			ll sum = (count(i , j - 1 , res) + ap[res]) * (ll)num[res] ;

			update(res , sum , i , j - 1 , L , R) ;

			f[i][j] = res ;
		}

	///

	for (int i = 0 ; i < m ; ++i) {
		int a , b ; a = read() ; b = read() ;

		printf("%lld\n" , work(a , b)) ;
	}

	return 0 ;
}