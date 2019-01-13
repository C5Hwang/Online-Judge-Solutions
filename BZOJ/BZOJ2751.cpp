#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__) ;

const int MAX_N = 1e5 + 10 , mod = 1e9 + 7 ;

struct data {
	int pl , num ;
}t[MAX_N] ;

int n , m , k , tot ;

bool cmp(data x , data y) {return x.pl < y.pl || (x.pl == y.pl && x.num < y.num) ;}

int qpow(int a , int t) {
	int tmp = a , s = 1 ;
	for (; t ; t >>= 1 , tmp = (ll)tmp * tmp % mod)
		if (t & 1) s = (ll)s * tmp % mod ;

	return s ;
}

int main() {
	scanf("%d %d %d" , &n , &m , &k) ;
	for (int i = 1 ; i <= k ; ++i) scanf("%d %d" , &t[i].pl , &t[i].num) ;

	///

	std::sort(t + 1 , t + 1 + k , cmp) ;

	t[0].pl = 0 ; tot = ((ll)n * (n + 1) >> 1) % mod ;

	int nw = 1 , ans = 1 ;
	for (int i = 1 ; i <= k ; ++i) {
		if (t[i].pl != t[i - 1].pl) {
			ans = (ll)ans * nw % mod ;
			nw = tot ; --m ;
		}
		else if (t[i].num == t[i - 1].num) continue ;

		nw = (nw - t[i].num + mod) % mod ;
	}

	ans = (ll)ans * nw % mod ;
	ans = (ll)ans * qpow(tot , m) % mod ;

	printf("%d\n" , ans) ;

	return 0 ;
}