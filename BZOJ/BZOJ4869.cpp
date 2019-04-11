#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 5e4 + 10 ;

int tot , mp[MAX_N] ;
int n , m , p , c , a[MAX_N] , sum[MAX_N << 2] , ti[MAX_N << 2] ;

///

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

int getphi(int x) {
	int res = x ;
	for (int i = 2 ; i * i <= x ; ++i) {
		if (x % i) continue ;
		for (; !(x % i) ; x /= i) ;

		res = res / i * (i - 1) ;
	}
	if (x > 1) res = res / x * (x - 1) ;

	return res ;
}

inline int times(int a , int b , int mod , bool &yc) {
	ll tmp = (ll)a * b ;
	if (tmp > mod) yc = 1 ;

	return tmp % mod ;
}

int qpow(int a , int t , int mod , bool &yc) {
	int sum = 1 , tmp = a ;
	for (; t ; t >>= 1 , tmp = times(tmp , tmp , mod , yc))
		if (t & 1) sum = times(sum , tmp , mod , yc) ;

	return sum ;
}

int getnum(int idx , int t , int p) {
	int mod = mp[p] ;
	if (!t) {
		if (a[idx] > mod) return a[idx] % mod + mod ;
		else return a[idx] ;
	}
	if (p == tot - 1) return 1 ;

	bool yc = 0 ;
	int tmp = getnum(idx , t - 1 , p + 1) , num = qpow(c , tmp , mod , yc) ;

	if (!p) return num ;
	else return num + (yc ? mod : 0) ;
}

///

void update(int x) {
	int L = x << 1 , R = x << 1 | 1 ;

	sum[x] = (sum[L] + sum[R]) % p ;
	ti[x] = std::min(ti[L] , ti[R]) ;
}

void build(int t , int x , int y) {
	if (x == y) {
		sum[t] = a[x] ; ti[t] = 0 ;
		return ;
	}

	int mid = (x + y) >> 1 ;
	build(t << 1 , x , mid) ; build(t << 1 | 1 , mid + 1 , y) ;

	update(t) ;
}

void modify(int t , int x , int y , int fx , int fy) {
	if (y < fx || fy < x) return ;
	if (ti[t] >= tot) return ;
	if (x == y) {
		++ti[t] ; sum[t] = getnum(x , ti[t] , 0) ;

		return ;
	}

	int mid = (x + y) >> 1 ;
	modify(t << 1 , x , mid , fx , fy) ;
	modify(t << 1 | 1 , mid + 1 , y , fx , fy) ;

	update(t) ;
}

int getsum(int t , int x , int y , int fx , int fy) {
	if (y < fx || fy < x) return 0 ;
	if (fx <= x && y <= fy) return sum[t] ;

	int mid = (x + y) >> 1 ,
		s1 = getsum(t << 1 , x , mid , fx , fy) ,
		s2 = getsum(t << 1 | 1 , mid + 1 , y , fx , fy) ;

	return (s1 + s2) % p ;
}

///

int main() {
	n = read() ; m = read() ; p = read() ; c = read() ;
	for (int i = 1 ; i <= n ; ++i) a[i] = read() ;

	///

	build(1 , 1 , n) ;
	mp[tot++] = p ;
	for (; p > 1 ;) {
		p = getphi(p) ;
		mp[tot++] = p ;
	}
	p = mp[0] ;

	///

	for (; m-- ;) {
		int op , l , r ;
		op = read() ; l = read() ; r = read() ;

		if (op == 0) modify(1 , 1 , n , l , r) ;
		else printf("%d\n" , getsum(1 , 1 , n , l , r)) ;
	}

	return 0 ;
}