#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 100 + 10 , MAX_P = 1e4 + 10 , MAX_M = 1e5 + 10 , INF = 0x3f3f3f3f ;

struct Link {
	int num , cap ;
	Link *next , *reg ;
}list[MAX_M << 1] ;

std::queue<int> que ;

Link *head[MAX_P] ;
int A[2][MAX_N][MAX_N] , B[2][MAX_N][MAX_N] , C[2][MAX_N][MAX_N] ;   // 0->art 1->science
int n , m , sum , ti , cur , tot , T , bh[MAX_N][MAX_N] , ap[MAX_P] , dep[MAX_P] ;

void ins(int x , int y , int v) {
	list[cur].num = y ;
	list[cur].cap = v ;
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

	int sum = 0 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (dep[nx] != dep[x] + 1) continue ;

		int nf = dfs(nx , std::min(f , h->cap)) ;
		sum += nf ; h->reg->cap += nf ;
		f -= nf ; h->cap -= nf ;
	}
	if (f) dep[x] = -1 ;

	return sum ;
}

bool bfs() {
	que.push(0) ;
	ap[0] = ++ti ; dep[0] = 1 ;

	for (; !que.empty() ;) {
		int x = que.front() ; que.pop() ;

		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ;
			if (ap[nx] == ti || !h->cap) continue ;

			dep[nx] = dep[x] + 1 ;
			que.push(nx) ; ap[nx] = ti ;
		}
	}

	return ap[T] == ti ;
}

inline int dinic() {
	int sum = 0 ;
	for (; bfs() ; sum += dfs(0 , INF)) ;

	return sum ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int t = 0 ; t < 2 ; ++t)
		for (int i = 1 ; i <= n ; ++i)
			for (int j = 1 ; j <= m ; ++j) scanf("%d" , &A[t][i][j]) , A[t][i][j] <<= 1 ;
	for (int t = 0 ; t < 2 ; ++t)
		for (int i = 1 ; i < n ; ++i)
			for (int j = 1 ; j <= m ; ++j) scanf("%d" , &B[t][i][j]) ;
	for (int t = 0 ; t < 2 ; ++t)
		for (int i = 1 ; i <= n ; ++i)
			for (int j = 1 ; j < m ; ++j) scanf("%d" , &C[t][i][j]) ;

	///

	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= m ; ++j) bh[i][j] = ++tot ;
	T = ++tot ;

	for (int i = 1 ; i < n ; ++i)
		for (int j = 1 ; j <= m ; ++j) {
			int ni = i + 1 , t1 = B[0][i][j] , t2 = B[1][i][j] ;

			ins(bh[i][j] , bh[ni][j] , t1 + t2) ;
			ins(bh[ni][j] , bh[i][j] , t1 + t2) ;
			
			A[0][i][j] += t1 ; A[1][i][j] += t2 ; A[0][ni][j] += t1 ; A[1][ni][j] += t2 ;
		}

	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j < m ; ++j) {
			int nj = j + 1 , t1 = C[0][i][j] , t2 = C[1][i][j] ;

			ins(bh[i][j] , bh[i][nj] , t1 + t2) ;
			ins(bh[i][nj] , bh[i][j] , t1 + t2) ;

			A[0][i][j] += t1 ; A[1][i][j] += t2 ; A[0][i][nj] += t1 ; A[1][i][nj] += t2 ;
		}

	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= m ; ++j) {
			int t1 = A[0][i][j] , t2 = A[1][i][j] ;

			sum += t1 + t2 ;
			ins(0 , bh[i][j] , t1) ;
			ins(bh[i][j] , T , t2) ;
		}

	printf("%d\n" , (sum - dinic()) >> 1) ;

	return 0 ;
}