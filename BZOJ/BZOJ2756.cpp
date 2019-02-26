#include <queue>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const ll INF = 1e17 ;
const int dx[4] = {0 , 0 , 1 , -1} , dy[4] = {1 , -1 , 0 , 0} ;
const int MAX_N = 40 + 5 , MAX_P = 1600 + 10 , MAX_M = 1e4 + 10 ;

struct Link {
	int num ; ll cap ;
	Link *next , *reg ;
}list[MAX_M << 1] ;

std::queue<int> que ;

Link *head[MAX_P] ;
int T , tot , ti , ap[MAX_P] , dep[MAX_P] ;
int n , m , cur , num[MAX_N][MAX_N] , bh[MAX_N][MAX_N] ;

///

void init() {
	cur = ti = 0 ;
	memset(ap , 0 , sizeof(ap)) ;
	memset(head , 0 , sizeof(head)) ;
}

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

///

ll dfs(int x , ll f) {
	if (x == T || !f) return f ;

	ll s = 0 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (dep[nx] != dep[x] + 1) continue ;

		ll nf = dfs(nx , std::min(f , h->cap)) ;
		s += nf ; h->reg->cap += nf ;
		f -= nf ; h->cap -= nf ;
	}
	if (f) dep[x] = -1 ;

	return s ;
}

bool bfs() {
	que.push(0) ;
	ap[0] = ++ti ; dep[0] = 1 ;

	for (; !que.empty() ;) {
		int x = que.front() ; que.pop() ;

		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ;
			if (ap[nx] == ti || !h->cap) continue ;

			que.push(nx) ;
			dep[nx] = dep[x] + 1 ; ap[nx] = ti ;
		}
	}

	return ap[T] == ti ;
}

ll dinic() {
	ll s = 0 ;
	for (; bfs() ; s += dfs(0 , INF)) ;

	return s ;
}

///

void ins(int x , int y , ll f) {
	list[cur].num = y ;
	list[cur].cap = f ;
	list[cur].next = head[x] ;
	list[cur].reg = &list[cur^1] ;
	head[x] = &list[cur++] ;

	list[cur].num = x ;
	list[cur].cap = 0 ;
	list[cur].next = head[y] ;
	list[cur].reg = &list[cur^1] ;
	head[y] = &list[cur++] ;
}

ll check(ll x) {
	ll t = 0 ; init() ;

	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= m ; ++j) {
			if ((i + j) & 1) {ins(bh[i][j] , T , x - num[i][j]) ; continue ;}
			else ins(0 , bh[i][j] , x - num[i][j]) , t += x - num[i][j] ;

			for (int k = 0 ; k < 4 ; ++k) {
				int ni = i + dx[k] , nj = j + dy[k] ;
				if (ni < 1 || nj < 1 || ni > n || nj > m) continue ;

				ins(bh[i][j] , bh[ni][nj] , INF) ;
			}
		}

	ll s = dinic() ;
	return s == t ? t : -1 ;
}

///

int main() {
	int CASE = read() ;
	for (; CASE-- ;) {
		tot = 0 ;
		n = read() ; m = read() ;

		int s = n * m , sn = 0 ; ll s1 = 0 , s2 = 0 ;
		for (int i = 1 ; i <= n ; ++i)
			for (int j = 1 ; j <= m ; ++j) {
				num[i][j] = read() ;
				bh[i][j] = ++tot ; sn = std::max(sn , num[i][j]) ;
			}
		for (int i = 1 ; i <= n ; ++i)
			for (int j = 1 ; j <= m ; ++j)
				if ((i + j) & 1) s2 += sn - num[i][j] ;
				else s1 += sn - num[i][j] ;

		T = ++tot ;

		///

		ll ans ;
		if (s & 1) {
			if (s1 > s2) ans = -1 ;
			else ans = check(sn + s2 - s1) ;
		}
		else {
			if (s1 != s2) ans = -1 ;
			else {
				ll L = sn - 1 , R = sn << 1 ;
				for (; L + 1 < R ;) {
					ll mid = (L + R) >> 1 ;
					if (check(mid) > -1) R = mid ;
					else L = mid ;
				}

				ans = check(R) ;
				printf("%d %lld --- " , sn , R) ;
			}
		}

		printf("%lld\n" , ans) ;
	}


	return 0 ;
}