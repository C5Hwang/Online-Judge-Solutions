#include <bits/stdc++.h>

#define ll long long

const int MAX_N = 18 + 5 , MAX_S = (1 << 18) + 10 , mod = 998244353 ;

struct Link {
	int num ;
	Link *next ;
}list[MAX_N << 1] ;
struct data {
	int x , y ;

	friend data operator *(data a , int t) {
		return (data){int((ll)a.x * t % mod) , int((ll)a.y * t % mod)} ;
	}
	friend data operator +(data a , data b) {
		return (data){(a.x + b.x) % mod , (a.y + b.y) % mod} ;
	}
	friend data operator +(data a , int t) {
		return (data){a.x , (a.y + t) % mod} ;
	}
}g[MAX_N] ;

Link *head[MAX_N] ;
int n , q , x , cur , deg[MAX_N] , f[MAX_N][MAX_S] ;

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

int qpow(int x , int t) {
	int s = 1 ;
	for (; t ; t >>= 1 , x = (ll)x * x % mod)
		if (t & 1) s = (ll)s * x % mod ;

	return s ;
}

inline int getinv(int x) {return qpow(x , mod - 2) ;}

void dp(int x , int fa , int S) {
	int nS ;
	if ((1 << x) & S) nS = S - (1 << x) ;
	else nS = S ;

	int P = deg[x] ;
	data nw = nS ? (data){0 , 1} : (data){0 , 0} ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa) continue ;

		dp(nx , x , S) ;
		if (nS < S) nw = nw + int((ll)P * f[nx][nS] % mod) ;
		else nw = nw + g[nx] * P ;
	}

	int ny = getinv((1 - nw.x + mod) % mod) ;
	if (x == fa) f[x][S] = (ll)ny * nw.y % mod ;
	else {
		g[x] = (data){0 , nw.y} ;

		if (nS < S) g[x] = g[x] + int((ll)P * f[fa][nS] % mod) ;
		else g[x].x = P ;

		g[x] = g[x] * ny ;
	}
}

void cal(int x , int fa , int S) {
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa) continue ;

		f[nx][S] = ((ll)g[nx].x * f[x][S] % mod + g[nx].y) % mod ;
		cal(nx , x , S) ;
	}
}

int main() {
	scanf("%d %d %d" , &n , &q , &x) ; --x ;
	for (int i = 1 ; i < n ; ++i) {
		int x , y ;

		scanf("%d %d" , &x , &y) ; --x ; --y ;
		ins(x , y) ; ins(y , x) ; ++deg[x] ; ++deg[y] ;
	}
	for (int i = 0 ; i < n ; ++i) deg[i] = getinv(deg[i]) ;

	///

	int tS = (1 << n) - 1 ;
	for (int i = 1 ; i <= tS ; ++i) {
		dp(0 , 0 , i) ; cal(0 , 0 , i) ;
	}

	for (; q-- ;) {
		int t , S = 0 ;
		scanf("%d" , &t) ;

		for (; t-- ;) {
			int num ;
			scanf("%d" , &num) ;
			--num ; S |= (1 << num) ;
		}

		printf("%d\n" , f[x][S]) ;
	}

	return 0 ;
}