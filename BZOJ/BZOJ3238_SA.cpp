#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 5e5 + 10 ;

struct data {int pl , l ; ll sum ;}sta[MAX_N] ;

char s[MAX_N] ;
int n , R , sa[MAX_N] , rk[MAX_N] , r1[MAX_N] , cnt[MAX_N] , sec[MAX_N] , h[MAX_N] ;

bool cmp(int x , int y , int l) {
	return rk[x] == rk[y] && rk[x + l] == rk[y + l] ;
}

void getsa(int m) {
	for (int i = 0 ; i <= m ; ++i) cnt[i] = 0 ;
	for (int i = 0 ; i < n ; ++i) ++cnt[rk[i] = s[i]] ;
	for (int i = 1 ; i <= m ; ++i) cnt[i] += cnt[i - 1] ;
	for (int i = n - 1 ; i >= 0 ; --i) sa[cnt[rk[i]]--] = i ;

	int p = 0 ;
	for (int k = 1 ; p < n ; k <<= 1 , m = p) {
		int o = 0 ;
		for (int i = n - k ; i < n ; ++i) sec[++o] = i ;
		for (int i = 1 ; i <= n ; ++i) if (sa[i] >= k) sec[++o] = sa[i] - k ;

		for (int i = 0 ; i <= m ; ++i) cnt[i] = 0 ;
		for (int i = 1 ; i <= n ; ++i) ++cnt[rk[sec[i]]] ;
		for (int i = 1 ; i <= m ; ++i) cnt[i] += cnt[i - 1] ;
		for (int i = n ; i ; --i) sa[cnt[rk[sec[i]]]--] = sec[i] ;

		r1[sa[1]] = p = 1 ;
		for (int i = 2 ; i <= n ; ++i)
			if (cmp(sa[i] , sa[i - 1] , k)) r1[sa[i]] = p ;
			else r1[sa[i]] = ++p ;
		for (int i = 0 ; i < n ; ++i) rk[i] = r1[i] ;
	}
}

void geth() {
	int k = 0 ;
	for (int i = 0 ; i < n ; ++i) {
		if (rk[i] == 1) {k = 0 ; continue ;}

		if (k) --k ;
		int j = sa[rk[i] - 1] ;
		for (; i + k < n && j + k < n && s[i + k] == s[j + k] ; ++k) ;
		h[rk[i]] = k ;
	}
}

int main() {
	scanf("%s" , s) ;
	n = strlen(s) ;

	getsa('z') ; geth() ;

	///

	ll sum = 0 , res = (ll)n * (n + 1) * (n - 1) >> 1 ;
	sta[++R] = (data){0 , 0 , 0} ;

	for (int i = 2 ; i <= n ; ++i) {
		int x = h[i] ;
		for (; R && sta[R].l >= x ; sum -= sta[R--].sum) ;

		ll tmp = (i - 1 - sta[R].pl) * (ll)x ;
		sta[++R] = (data){i - 1 , x , tmp} ;
		sum += tmp ; res -= (sum << 1) ;
	}

	printf("%lld\n" , res) ;

	return 0 ;
}