#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 ;

inline int check(int x , int y) {return !x ? y : x ;}

inline ll count(int *n1 , int *n2) {return (ll)n1[0] * n2[1] + (ll)n1[1] * n2[0] ;}

void divi(int x , int *n) {
	n[0] = n[1] = x / 2 ;
	n[1] += x % 2 ;
}

struct data {
	bool epy ; ll sum ;
	int p[2][2][2] , L , R ;   //(0,0) L->R fir | (0,1) L->R sec | (1,0) R->L fir | (1,1) R->L sec

	void init() {
		epy = 1 ; sum = 0 ; L = R = 0 ;
		for (int i = 0 ; i < 2 ; ++i)
			for (int j = 0 ; j < 2 ; ++j) p[0][i][j] = p[1][i][j] = 0 ;
	}
	void setnum(int pl , int x) {
		epy = 0 ; L = R = pl ;
		if (x) p[1][0][0] = p[1][1][0] = pl , ++sum ;
		else p[0][0][0] = p[0][1][0] = pl ;
	}
	friend data operator +(data x , data y) {
		if (x.epy) return y ;
		else if (y.epy) return x ;

		data res ;
		res.epy = 0 ; res.sum = x.sum + y.sum ; res.L = x.L ; res.R = y.R ;

		///

		int l[2][2] , r[2][2] , lx = x.R - x.L + 1 , ly = y.R - y.L + 1 ;

		for (int i = 0 ; i < 2 ; ++i) {
			if (!x.p[i][0][0]) res.p[i][0][0] = y.p[i][0][0] , res.p[i][0][1] = y.p[i][0][1] ;
			else res.p[i][0][0] = x.p[i][0][0] , res.p[i][0][1] = check(x.p[i][0][1] , y.p[i][0][0]) ;

			if (!y.p[i][1][0]) res.p[i][1][0] = x.p[i][1][0] , res.p[i][1][1] = x.p[i][1][1] ;
			else res.p[i][1][0] = y.p[i][1][0] , res.p[i][1][1] = check(y.p[i][1][1] , x.p[i][1][0]) ;
		}

		for (int i = 0 ; i < 2 ; ++i) {
			l[i][0] = x.p[i][1][0] ? x.R - x.p[i][1][0] : lx ;
			l[i][1] = x.p[i][1][1] ? x.p[i][1][0] - x.p[i][1][1] - 1 : x.p[i][1][0] - x.L ;

			r[i][0] = y.p[i][0][0] ? y.p[i][0][0] - y.L : ly ;
			r[i][1] = y.p[i][0][1] ? y.p[i][0][1] - y.p[i][0][0] - 1 : y.R - y.p[i][0][0] ;
		}

		///

		// 0 ... 0 ... | ... 0 ... 0
		int nl0[2] , nl1[2] , nr0[2] , nr1[2] ;
		divi(l[0][0] , nl0) ; divi(l[0][1] , nl1) ;
		divi(r[0][0] , nr0) ; divi(r[0][1] , nr1) ;

		if (l[0][0] % 2) std::swap(nl1[0] , nl1[1]) ;
		if (r[0][0] % 2) std::swap(nr1[0] , nr1[1]) ;

		res.sum += count(nl0 , nr0) ;
		if (x.p[0][1][0]) {
			res.sum += nr0[(l[0][0] % 2) ^ 1] ;
			res.sum += count(nl1 , nr0) ;
		}
		if (y.p[0][0][0]) {
			res.sum += nl0[(r[0][0] % 2) ^ 1] ;
			res.sum += count(nr1 , nl0) ;
		}

		///

		// 1 ... 1 ... | ... 1 ... 1
		if (x.p[1][1][0]) {
			res.sum += std::max(r[1][0] - (!l[1][0]) , 0) ;
			res.sum += (ll)l[1][1] * r[1][0] ;
		}
		if (y.p[1][0][0]) {
			res.sum += std::max(l[1][0] - (!r[1][0]) , 0) ;
			res.sum += (ll)r[1][1] * l[1][0] ;
		}

		return res ;
	}
}tre[MAX_N << 2] , EMPTY ;

int n , m , a[MAX_N] ;

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

void build(int t , int x , int y) {
	if (x == y) {
		data *p = &tre[t] ;
		p->init() ; p->setnum(x , a[x]) ;

		return ;
	}

	int mid = (x + y) >> 1 ;
	build(t << 1 , x , mid) ; build(t << 1 | 1 , mid + 1 , y) ;

	tre[t] = tre[t << 1] + tre[t << 1 | 1] ;
}

void modify(int t , int x , int y , int f) {
	if (y < f || f < x) return ;
	if (x == y) {
		data *p = &tre[t] ;
		p->init() ; p->setnum(x , (a[x] ^= 1)) ;

		return ;
	}

	int mid = (x + y) >> 1 ;
	modify(t << 1 , x , mid , f) ; modify(t << 1 | 1 , mid + 1 , y , f) ;

	tre[t] = tre[t << 1] + tre[t << 1 | 1] ;
}

data find(int t , int x , int y , int fx , int fy) {
	if (y < fx || fy < x) return EMPTY ;
	if (fx <= x && y <= fy) return tre[t] ;

	int mid = (x + y) >> 1 ;
	data s1 = find(t << 1 , x , mid , fx , fy) ,
		 s2 = find(t << 1 | 1 , mid + 1 , y , fx , fy) ;

	return s1 + s2 ;
}

int main() {
	n = read() ; EMPTY.init() ;
	for (int i = 1 ; i <= n ; ++i) a[i] = read() ;

	///

	build(1 , 1 , n) ;

	m = read() ;
	for (; m-- ;) {
		int op , x , y ;
		op = read() ; x = read() ;

		if (op == 1) modify(1 , 1 , n , x) ;
		else {
			y = read() ;
			int len = y - x + 1 ; ll res = (ll)len * (len + 1) >> 1 ;
			res -= find(1 , 1 , n , x , y).sum ;

			printf("%lld\n" , res) ;
		}
	}

	return 0 ;
}