#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int mod = 1e9 + 7 ;

int n , m , ans , inv[4] ;

int qpow(int a , int t) {
	int s = 1 , tmp = a ;

	for (; t > 0 ; t >>= 1 , tmp = (ll)tmp * tmp % mod)
		if (t & 1) s = (ll)s * tmp % mod ;

	return s ;
}

int cal1() {
	int res = (ll)qpow(4 , n - 2) * qpow(3 , m - n) % mod ;
	res = (((ll)res * qpow(2 , n - 1) % mod) << 2) % mod ;

	return res ;
}

int cal2() {
	int res , s1 = qpow(4 , n - 4) + mod - 1 , s2 ;
	s1 = (ll)s1 * inv[3] % mod ; s1 = (ll)s1 * 20 % mod ;
	s1 = ((ll)s1 * qpow(3 , m - n) % mod) * qpow(2 , n - 1) % mod ;

	if (n == 3) {
		res = (ll)qpow(3 , m - 4) * qpow(2 , n - 1) % mod ;
		res = ((ll)res << 2) % mod ;
	}
	else if (n == m) {
		s2 = (ll)qpow(2 , n - 2) * 15 % mod ;
		res = (s1 + s2) % mod ;
	}
	else {
		s2 = ((ll)qpow(3 , m - n - 1) * qpow(2 , n - 1) % mod) * 20 % mod ;
		res = (s1 + s2) % mod ;
	}

	(res <<= 1) %= mod ;
	return res ;
}

int cal3() {
	int res , s1 = qpow(4 , n - 4) + mod - 1 , s2 ;
	s1 = (ll)s1 * inv[3] % mod ; s1 = (ll)s1 * 20 % mod ;
	s1 = ((ll)s1 * qpow(3 , m - n) % mod) * qpow(2 , n - 1) % mod ;

	s2 = (qpow(3 , m - n - 1) + mod - 1) % mod ;
	s2 = (ll)s2 * inv[2] % mod ; s2 = (ll)s2 * 12 % mod ; s2 = (ll)s2 * qpow(2 , n - 1) % mod ;

	if (n == 3) {
		res = s2 ;
		(res += (ll)12 * qpow(2 , n - 2) % mod) %= mod ;
	}
	else if (n == m) {
		res = (s1 + s2) % mod ;
		(res += (ll)3 * qpow(2 , n - 2) % mod) %= mod ;
		(res += ((ll)qpow(2 , n - 2) * 12) % mod) %= mod ;
	}
	else {
		res = (s1 + s2) % mod ;
		(res += (ll)12 * qpow(2 , n - 2) % mod) %= mod ;
		(res += (((ll)qpow(3 , m - n - 1) * qpow(2 , n - 1) % mod) * 16) % mod) %= mod ;
	}

	(res <<= 1) %= mod ;
	return res ;
}

int cal4() {
	int res ;

	if (n == 3) res = ((ll)qpow(3 , m - n - 1) * qpow(2 , n - 1)) % mod * 16 % mod ;
	else {
		res = (ll)qpow(4 , n - 4) * qpow(3 , m - n) % mod ;
		res = ((ll)res * qpow(2 , n - 1) % mod) * 20 % mod ;
	}

	return res ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	if (n > m) std::swap(n , m) ;
	for (int i = 2 ; i < 4 ; ++i) inv[i] = qpow(i , mod - 2) ;

	if (n == 1) ans = qpow(2 , m) ;
	else if (n == 2) ans = ((ll)qpow(3 , m - 1) << 2) % mod ;
	else if (n == 3 && m == 3) ans = 112 ;
	else {
		(ans += cal1()) %= mod ;
		(ans += cal2()) %= mod ;
		(ans += cal3()) %= mod ;
		(ans += cal4()) %= mod ;
	}

	printf("%d\n" , ans) ;

	return 0 ;
}