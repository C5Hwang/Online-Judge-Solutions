#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define db long double
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 3e4 + 10 , MAX_M = 12e4 + 10 , mod = (119 << 23) + 1 , G = 3 ;

struct Link {
	int num ;
	Link *next ;
}list[MAX_N << 1] ;

bool vis[MAX_N] ;
Link *head[MAX_N] ;
int f[MAX_M] , cnt[MAX_M] , rev[MAX_M] ;
int n , m , cur , root , msiz , tot , siz[MAX_N] ;

///

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

int qpow(int a , int t) {
	int tmp = a , s = 1 ;
	for (; t ; t >>= 1 , tmp = (ll)tmp * tmp % mod)
		if (t & 1) s = (ll)s * tmp % mod ;

	return s ;
}

void fnt(int *f , int ty) {
	for (int i = 0 ; i < n ; ++i) if (i < rev[i]) std::swap(f[i] , f[rev[i]]) ;

	for (int L = 2 ; L <= n ; L <<= 1) {
		int hf = L >> 1 , phi = mod - 1 , gn ;
		if (ty > 0) gn = qpow(G , phi / L) ;
		else gn = qpow(G , phi - phi / L) ;

		for (int i = 0 ; i < n ; i += L) {
			int g = 1 ;
			for (int j = 0 ; j < hf ; ++j , g = (ll)g * gn % mod) {
			 	int tmp = (ll)f[i + j + hf] * g % mod ;

			 	f[i + j + hf] = (f[i + j] + mod - tmp) % mod ;
			 	(f[i + j] += tmp) %= mod ;
			}
		}
	}
}

void calc(int ty) {
	n = 1 ; m <<= 1 ; int L = 0 ;
	for (; n <= m ; n <<= 1 , ++L) ;
	for (int i = 0 ; i < n ; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1)) ;

	fnt(f , 1) ;
	for (int i = 0 ; i < n ; ++i) f[i] = (ll)f[i] * f[i] % mod ;
	fnt(f , -1) ;

	int ny = qpow(n , mod - 2) ;
	for (int i = 0 ; i <= m ; ++i) {
		int a = (ll)f[i] * ny % mod ;
		cnt[i] += a * ty ;
	}

	for (int i = 0 ; i < n ; ++i) f[i] = 0 ;
}

///

void findroot(int x , int fa) {
	siz[x] = 1 ; int mx = 0 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa || vis[nx]) continue ;

		findroot(nx , x) ;
		siz[x] += siz[nx] ; mx = std::max(mx , siz[nx]) ;
	}
	mx = std::max(mx , tot - siz[x]) ;

	if (msiz > mx) msiz = mx , root = x ;
}

void count(int x , int fa , int d) {
	++f[d] ; m = std::max(d , m) ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa || vis[nx]) continue ;

		count(nx , x , d + 1) ;
	}
}

void work(int x) {
	vis[x] = 1 ; m = 0 ; ++f[0] ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (vis[nx]) continue ;

		count(nx , nx , 1) ;
	}
	calc(1) ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (vis[nx]) continue ;

		m = 0 ; count(nx , nx , 1) ; calc(-1) ;
	}

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (vis[nx]) continue ;

		root = 0 ; msiz = tot = siz[nx] ;
		findroot(nx , nx) ;
		work(root) ;
	}
}

///

int main() {
	scanf("%d" , &n) ;
	for (int i = 1 ; i < n ; ++i) {
		int x , y ; scanf("%d %d" , &x , &y) ;
		ins(x , y) ; ins(y , x) ;
	}

	///

	int tmp = n ;
	root = 0 ; msiz = tot = n ;
	findroot(1 , 1) ;
	work(root) ;

	///

	n = tmp ;

	db ans = 0 ;
	for (int i = 0 ; i <= n ; ++i) ans += cnt[i] * 1.0 / (i + 1) ; 
	printf("%0.4Lf\n" , ans) ;

	return 0 ;
}