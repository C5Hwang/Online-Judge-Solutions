#include <queue>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

#define db double
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const db eps = 1e-5 ;
const int MAX_N = 50 + 5 , MAX_P = 2500 + 10 , MAX_M = 15e3 + 10 , INF = 0x3f3f3f3f ;

struct Link {
	int num ; db cap ;
	Link *next , *reg ;
}list[MAX_M << 1] ;

std::queue<int> que ;

db sum ;
Link *head[MAX_P] ;
int T , ti , cur , dep[MAX_P] , ap[MAX_P] ;
int n , m , bh[MAX_N][MAX_N] , v[MAX_N][MAX_N] , c1[MAX_N][MAX_N] , c2[MAX_N][MAX_N] ;

///

db dfs(int x , db f) {
	if (x == T || f < eps) return f ;

	db sum = 0 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (dep[nx] != dep[x] + 1) continue ;

		db nf = dfs(nx , std::min(f , h->cap)) ;
		sum += nf ; h->reg->cap += nf ;
		f -= nf ; h->cap -= nf ;
	}
	if (eps < f) dep[x] = -1 ;

	return sum ;
}

bool bfs() {
	que.push(0) ;
	dep[0] = 1 ; ap[0] = ++ti ;

	for (; !que.empty() ;) {
		int x = que.front() ; que.pop() ;

		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ;
			if (ap[nx] == ti || h->cap < eps) continue ;

			que.push(nx) ;
			dep[nx] = dep[x] + 1 ; ap[nx] = ti ;
		}
	}

	return ap[T] == ti ;
}

inline db dinic() {
	db sum = 0 ;
	for (; bfs() ; sum += dfs(0 , INF)) ;

	return sum ;
}

///

void init() {
	ti = cur = 0 ;
	memset(ap , 0 , sizeof(ap)) ;
	memset(head , 0 , sizeof(head)) ;
}

void ins(int x , int y , db v) {
	list[cur].num = y ;
	list[cur].cap = v ;
	list[cur].reg = &list[cur^1] ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;

	list[cur].num = x ;
	list[cur].cap = 0 ;
	list[cur].reg = &list[cur^1] ;
	list[cur].next = head[y] ;
	head[y] = &list[cur++] ;
}

void build(db k) {
	init() ; T = n * m + 1 ;

	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= m ; ++j)
			ins(0 , bh[i][j] , v[i][j]) ;
	for (int i = 1 ; i <= n + 1 ; ++i)
		for (int j = 1 ; j <= m ; ++j) {
			db v = k * c1[i][j] ;

			if (i == 1 || i == n + 1) ins(bh[std::max(i - 1 , 1)][j] , T , v) ;
			else ins(bh[i][j] , bh[i - 1][j] , v) , ins(bh[i - 1][j] , bh[i][j] , v) ;
		}
	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= m + 1 ; ++j) {
			db v = k * c2[i][j] ;

			if (j == 1 || j == m + 1) ins(bh[i][std::max(j - 1 , 1)] , T , v) ;
			else ins(bh[i][j] , bh[i][j - 1] , v) , ins(bh[i][j - 1] , bh[i][j] , v) ;
		}
}

bool check(db k) {
	build(k) ;

	return sum - dinic() > eps ;
}

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

///

int main() {
	db L = 0 , R = 0 ;
	n = read() ; m = read() ;
	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= m ; ++j) {
			v[i][j] = read() ; bh[i][j] = (i - 1) * m + j ;
			R = std::max(R , v[i][j] + 1.0) ; sum += v[i][j] ;
		}
	for (int i = 1 ; i <= n + 1 ; ++i)
		for (int j = 1 ; j <= m ; ++j)
			c1[i][j] = read() ;
	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= m + 1 ; ++j)
			c2[i][j] = read() ;

	///

	for (; fabs(L - R) > eps ;) {
		db mid = (L + R) / 2 ;

		if (check(mid)) L = mid ;
		else R = mid ;
	}

	printf("%0.3lf\n" , L) ;

	return 0 ;
}