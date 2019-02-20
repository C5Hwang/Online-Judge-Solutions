#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int dx[4] = {1 , -1 , 0 , 0} , dy[4] = {0 , 0 , 1 , -1} ;
const int MAX_N = 100 + 10 , MAX_P = 1e4 + 10 , MAX_M = 6e4 + 10 , INF = 0x3f3f3f3f ;

struct Link {
	int num , cap ;
	Link *next , *reg ;
}list[MAX_M << 1] ;

std::queue<int> que ;

Link *head[MAX_P] ;
int T , ti , cur , ap[MAX_P] , dep[MAX_P] ;
int n , m , tot , a[MAX_N][MAX_N] , bh[MAX_N][MAX_N] ;

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

			que.push(nx) ;
			ap[nx] = ti ; dep[nx] = dep[x] + 1 ;
		}
	}

	return ap[T] == ti ;
}

int dinic() {
	int sum = 0 ;
	for (; bfs() ;) sum += dfs(0 , INF) ;

	return sum ;
}

int main() {
	scanf("%d %d" , &n , &m) ;

	tot = 0 ;
	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= m ; ++j)
			scanf("%d" , &a[i][j]) , bh[i][j] = ++tot ;
	T = ++tot ;

	///

	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= m ; ++j) {
			for (int k = 0 ; k < 4 ; ++k) {
				int ni = i + dx[k] , nj = j + dy[k] ;
				if (ni < 1 || nj < 1 || ni > n || nj > m) continue ;

				ins(bh[i][j] , bh[ni][nj] , 1) ;
			}

			if (a[i][j] == 1) ins(0 , bh[i][j] , INF) ;
			else if (a[i][j] == 2) ins(bh[i][j] , T , INF) ;
		}

	printf("%d\n" , dinic()) ;

	return 0 ;
}