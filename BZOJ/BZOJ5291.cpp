#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__  , __LINE__) ;

const int MAX_N = 2e5 + 10 , mod = 1e9 + 7 ;

inline int MOD(int x) {return x >= mod ? x - mod : x ;}

struct data {
	int a[3] , s[3] ;

	void init() {
		for (int i = 0 ; i < 3 ; ++i) a[i] = s[i] = 0 ;
	}
	int calc(int n) {
		int s1 = s[1] , s2 = (ll)n * s[2] % mod ;
		return MOD(s1 + s2) ;
	}
	friend data operator +(data x , int y) {
		data r ;
		for (int i = 0 ; i < 3 ; ++i)
			r.a[i] = x.a[i] , r.s[i] = (x.s[i] + (ll)y * x.a[i]) % mod ;
		return r ;
	}
	friend data operator +(data x , data y) {
		data r ;
		for (int i = 0 ; i < 3 ; ++i)
			r.a[i] = MOD(x.a[i] + y.a[i]) , r.s[i] = MOD(x.s[i] + y.s[i]) ;
		return r ;
	}
	friend data operator *(data x , data y) {
		data r ;
		for (int i = 0 ; i < 3 ; ++i) r.s[i] = MOD(x.s[i] + y.s[i]) ;
		return r ;
	}
}tre[MAX_N << 2] , epy ;

int n , m , ma , s[MAX_N] , a[MAX_N] , le[MAX_N] , ri[MAX_N] , v[MAX_N] , lzy[MAX_N << 2] ;

inline int squ(int x) {return (ll)x * x % mod ;}

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

void build(int t , int x , int y) {
	if (x == y) {
		tre[t].init() ; lzy[t] = 0 ;
		tre[t].a[0] = 1 ; tre[t].a[1] = MOD(s[a[x]] + mod - squ(a[x])) ; tre[t].a[2] = a[x] ;
		tre[t] = tre[t] + v[x] ;

		return ;
	}

	int mid = (x + y) >> 1 ;
	build(t << 1 , x , mid) ; build(t << 1 | 1 , mid + 1 , y) ;

	tre[t] = tre[t << 1] + tre[t << 1 | 1] ;
}

void down(int t) {
	int L = t << 1 , R = t << 1 | 1 , d = lzy[t] ;
	if (!d) return ;

	tre[L] = tre[L] + d ; tre[R] = tre[R] + d ;
	lzy[L] = MOD(lzy[L] + d) ; lzy[R] = MOD(lzy[R] + d) ;

	lzy[t] = 0 ;
}

void update(int t) {
	data *p = &tre[t] , *l = &tre[t << 1] , *r = &tre[t << 1 | 1] ;
	for (int i = 0 ; i < 3 ; ++i)
		p->s[i] = MOD(l->s[i] + r->s[i]) ;
}

void modify(int t , int x , int y , int fx , int fy , int d) {
	if (y < fx || fy < x) return ;
	if (fx <= x && y <= fy) {
		tre[t] = tre[t] + d ; lzy[t] = MOD(lzy[t] + d) ;

		return ;
	}

	down(t) ;

	int mid = (x + y) >> 1 ;
	modify(t << 1 , x , mid , fx , fy , d) ; modify(t << 1 | 1 , mid + 1 , y , fx , fy , d) ;

	update(t) ;
}

data find(int t , int x , int y , int fx , int fy) {
	if (y < fx || fy < x) return epy ;
	if (fx <= x && y <= fy) return tre[t] ;

	down(t) ;

	int mid = (x + y) >> 1 ;
	data s1 = find(t << 1 , x , mid , fx , fy) ,
		 s2 = find(t << 1 | 1 , mid + 1 , y , fx , fy) ;

	return s1 * s2 ;
}

int count(int x) {
	if (!x) return 0 ;
	int L = le[x] , R = ri[x] ;

	data p1 , p2 , p3 ;
	p1 = find(1 , 1 , n , 1 , L - 1) ; p2 = find(1 , 1 , n , L , R) ; p3 = find(1 , 1 , n , R + 1 , n) ;

	int s1 = (ll)s[x] * p2.s[0] % mod , s2 = MOD(p1.calc(x) + p3.calc(x)) ;
	return MOD(s1 + s2) ;
}

int cal(int x) {
	if (!x) return 0 ;

	int res = 0 ;
	if (a[x] == x) res = count(a[x]) ;
	else if (n % 2) {
		res = MOD(count(ma) + count(ma - 1)) ;
		res = MOD(res - count(a[x] - 1) + mod) ;
	}
	else {
		res = MOD(count(ma) << 1) ;
		res = MOD(res - count(a[x] - 1) + mod) ;
	}

	return res ;
}

int main() {
	n = read() ; m = read() ; ma = 0 ; epy.init() ;
	for (int i = 1 ; i <= n ; ++i) le[i] = n + 1 , ri[i] = 0 ;

	for (int i = 1 ; i <= n ; ++i) {
		v[i] = read() ;	s[i] = ((ll)i * (i + 1) >> 1) % mod ;

		a[i] = std::min(i , n - i + 1) ; ma = std::max(ma , a[i]) ;
		le[a[i]] = std::min(le[a[i]] , i) ; ri[a[i]] = std::max(ri[a[i]] , i) ;
	}

	///

	build(1 , 1 , n) ;
	for (; m-- ;) {
		int op , x , y , d ;
		op = read() ; x = read() ; y = read() ;
		
		if (op == 1) {
			d = read() ;
			if (x > y) std::swap(x , y) ;
			modify(1 , 1 , n , x , y , d) ;
		}
		else {
			int res = MOD(cal(y) - cal(x - 1) + mod) ;
			printf("%d\n" , res) ;
		}
	}

	return 0 ;
}