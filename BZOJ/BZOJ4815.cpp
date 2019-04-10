#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 4e6 + 10 , mod = 1e9 + 7 ;

int tot , pri[MAX_N] , phi[MAX_N] , g[MAX_N] ;
int n , Q , siz , f[MAX_N] , s[MAX_N] , bs[MAX_N] , bk[MAX_N] , le[MAX_N] , ri[MAX_N] ;

///

void init() {
	siz = (int)sqrt(n) ;

	for (int i = 1 ; i <= n ; ++i)
		bk[i] = i / siz , le[i] = n + 1 , ri[i] = 0 , f[i] = (ll)i * i % mod ;
	for (int i = 1 ; i <= n ; ++i)
		le[bk[i]] = std::min(le[bk[i]] , i) , ri[bk[i]] = std::max(ri[bk[i]] , i) ;

	///

	s[1] = f[1] ;
	for (int i = 2 ; i <= n ; ++i)
		if (bk[i] != bk[i - 1]) s[i] = f[i] ;
		else s[i] = (s[i - 1] + f[i]) % mod ;
	bs[0] = s[ri[0]] ;
	for (int i = 1 ; i <= bk[n] ; ++i) bs[i] = (bs[i - 1] + s[ri[i]]) % mod ;
}

void init_phi() {
	phi[1] = 1 ;
	for (int i = 2 ; i <= n ; ++i) {
		if (!phi[i]) {pri[tot++] = i ; phi[i] = i - 1 ;}

		for (int j = 0 ; j < tot ; ++j) {
			int tmp = i * pri[j] ;
			if (tmp > n) break ;

			if (i % pri[j]) phi[tmp] = phi[i] * (pri[j] - 1) ;
			else {phi[tmp] = phi[i] * pri[j] ; break ;}
		}
	}

	for (int i = 1 ; i <= n ; ++i) g[i] = (ll)i * i % mod * phi[i] % mod ;
	for (int i = 1 ; i <= n ; ++i) g[i] = (g[i - 1] + g[i]) % mod ;
}

///

inline int gcd(int x , int y) {return y ? gcd(y , x % y) : x ;}

void modify(int p , int x) {
	int B = bk[p] ; f[p] = x ;

	for (int i = p ; i <= ri[B] ; ++i)
		if (bk[i] != bk[i - 1]) s[i] = f[i] ;
		else s[i] = (s[i - 1] + f[i]) % mod ;
	for (int i = B ; i <= bk[n] ; ++i)
		if (i) bs[i] = (bs[i - 1] + s[ri[i]]) % mod ;
		else bs[i] = s[ri[i]] ;
}

int getsum(int p) {
	int B = bk[p] , s1 = B ? bs[B - 1] : 0 , s2 = s[p] ;

	return (s1 + s2) % mod ;
}

///

int main() {
	scanf("%d %d" , &Q , &n) ;

	init() ; init_phi() ;

	///

	for (; Q-- ;) {
		int a , b , k , d ; ll x ;
		scanf("%d %d %lld %d" , &a , &b , &x , &k) ;

		d = gcd(a , b) ;
		x = x / (a / d) / (b / d) % mod ;
		modify(d , x) ;

		///

		int ans = 0 ;
		for (int L = 1 ; L <= k ;) {
			int t = k / L , R = k / t ;
			int s1 = (getsum(R) - getsum(L - 1) + mod) % mod , s2 = g[t] ;
			ans = (ans + (ll)s1 * s2) % mod ; L = R + 1 ;
		}

		printf("%d\n" , ans) ;
	}

	return 0 ;
}