#include <queue>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 100 + 10 , MAX_M = 4e4 + 400 , MAX_T = 4e6 + 4e4 + 10 , INF = 110 ;

struct Edge {int x , y ;}eg[MAX_M] ;
struct Link {
	int num , cap ;
	Link *reg , *next ;
}list[MAX_T << 1] ;

std::queue<int> que ;

Link *head[MAX_M] ;
int n , m , k , tot , bh[MAX_N][MAX_N << 1][2] ;
int S , T , cur , ti , ap[MAX_M] , dep[MAX_M] ;

void init() {
	cur = ti = 0 ;
	memset(ap , 0 , sizeof(ap)) ;
	memset(head , 0 , sizeof(head)) ;
}

void ins(int x , int y , int f) {
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

int dfs(int x , int f) {
	if (x == T || !f) return f ;

	int s = 0 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (dep[nx] != dep[x] + 1) continue ;

		int nf = dfs(nx , std::min(f , h->cap)) ;
		s += nf ; h->reg->cap += nf ;
		f -= nf ; h->cap -= nf ;
	}
	if (f) dep[x] = -1 ;

	return s ;
}

bool bfs() {
	que.push(S) ;
	ap[S] = ++ti ; dep[S] = 1 ;

	for (; !que.empty() ;) {
		int x = que.front() ; que.pop() ;

		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ;
			if (ap[nx] == ti || !h->cap) continue ;

			que.push(nx) ;
			ap[nx] = ti ; dep[nx] = dep[x] + 1 ;
		}
	}

	return ap[T] == ti ;
}

inline int dinic() {
	int sum = 0 ;
	for (; bfs() ; sum += dfs(S , INF)) ;

	return sum ;
}

bool check(int x) {
	init() ; --x ;

	S = bh[0][0][1] ; T = bh[n - 1][x][0] ;
	for (int i = 0 ; i < m ; ++i) {
		Edge *p = &eg[i] ;
		for (int j = 0 ; j < x ; ++j)
			ins(bh[p->x][j][1] , bh[p->y][j + 1][0] , INF) ,
			ins(bh[p->y][j][1] , bh[p->x][j + 1][0] , INF) ;
	}

	for (int i = 1 ; i < n - 1 ; ++i) {
		for (int j = 0 ; j <= x ; ++j) ins(bh[i][j][0] , bh[i][j][1] , 1) ;
		for (int j = 0 ; j < x ; ++j) ins(bh[i][j][0] , bh[i][j + 1][1] , INF) ;
	}
	for (int j = 0 ; j <= x ; ++j) ins(bh[n - 1][j][0] , bh[n - 1][j][1] , INF) ;
	for (int j = 0 ; j < x ; ++j) ins(bh[n - 1][j][1] , bh[n - 1][j + 1][0] , INF) ;

	return dinic() <= k ;
}

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

int main() {
	freopen("min.in" , "r" , stdin) ;
	freopen("min.out" , "w" , stdout) ;

	n = read() ; m = read() ; k = read() ;
	for (int i = 0 ; i < m ; ++i) {eg[i].x = read() ; eg[i].y = read() ;}

	for (int i = 0 ; i < n ; ++i)
		for (int j = 0 ; j <= (n << 1) ; ++j)
			bh[i][j][0] = ++tot , bh[i][j][1] = ++tot ;

	///

	int L = 0 , R = (n << 1) + 1 ;
	for (; L + 1 < R ;) {
		int mid = (L + R) >> 1 ;
		if (check(mid)) L = mid ;
		else R = mid ;
	}

	printf("%d\n" , L) ;

	fclose(stdin) ; fclose(stdout) ;

	return 0 ;
}