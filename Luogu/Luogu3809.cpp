#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG pritnf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e6 + 10 ;

char s[MAX_N] ;
int n , m , rk[MAX_N] , r1[MAX_N] , sa[MAX_N] , sec[MAX_N] , cnt[MAX_N] ;

bool cmp(int x , int y , int l) {
	return rk[x] == rk[y] && rk[x + l] == rk[y + l] ;
}

void work() {
	for (int i = 0 ; i <= m ; ++i) cnt[i] = 0 ;
	for (int i = 0 ; i < n ; ++i) ++cnt[rk[i] = s[i]] ;
	for (int i = 1 ; i <= m ; ++i) cnt[i] += cnt[i - 1] ;
	for (int i = n - 1 ; i >= 0 ; --i) sa[cnt[s[i]]--] = i ;

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

int main() {
	scanf("%s" , s) ;
	n = strlen(s) ;
	for (int i = 0 ; i < n ; ++i) m = std::max(m , (int)s[i]) ;

	work() ;
	for (int i = 1 ; i <= n ; ++i) printf("%d " , sa[i] + 1) ; printf("\n") ;

	return 0 ;
}