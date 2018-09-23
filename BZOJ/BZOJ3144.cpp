#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int dx[4] = {1 , -1 , 0 , 0} , dy[4] = {0 , 0 , 1 , -1} ;
const int MAX_N = 40 + 5 , MAX_V = 7e4 + 10 , MAX_E = 7e5 + 10 , INF = 0x3f3f3f3f ;

struct Link {
	int num , cap ;
	Link *next , *reg ;
}list[MAX_E] ;

std::queue<int> que ;

Link *head[MAX_V] ;
int cur , ti , ap[MAX_V] , dep[MAX_V] ;
int p , q , r , d , tot , S , T , idx[MAX_N][MAX_N][MAX_N] ;

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

bool bfs() {
	que.push(S) ;
	ap[S] = ++ti ; dep[S] = 1 ;

	for (; !que.empty() ;) {
		int x = que.front() ; que.pop() ;

		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ;
			if (!h->cap || ap[nx] == ti) continue ;

			dep[nx] = dep[x] + 1 ; ap[nx] = ti ;
			que.push(nx) ;
		}
	}

	return ap[T] == ti ;
}

int dfs(int x , int flow) {
	if (x == T || !flow) return flow ;

	int sum = 0 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (dep[nx] != dep[x] + 1) continue ;

		int nf = dfs(nx , std::min(flow , h->cap)) ;
		flow -= nf ; h->cap -= nf ;
		sum += nf ; h->reg->cap += nf ;
	}
	if (flow) dep[x] = -1 ;

	return sum ;
}

int dinic() {
	int sum = 0 ;
	for (; bfs() ; sum += dfs(S , INF)) ;

	return sum ;
}

int main() {
	scanf("%d %d %d %d" , &p , &q , &r , &d) ;

	///

	for (int k = 1 ; k <= r ; ++k)
		for (int i = 1 ; i <= p ; ++i)
			for (int j = 1 ; j <= q ; ++j)
				idx[k][i][j] = ++tot ;

	S = 0 ; T = ++tot ;
	for (int k = 1 ; k <= r ; ++k)
		for (int i = 1 ; i <= p ; ++i)
			for (int j = 1 ; j <= q ; ++j) {
				int v ; scanf("%d" , &v) ;

				if (k == 1) ins(S , idx[k][i][j] , INF) ;

				if (k == r) ins(idx[k][i][j] , T , v) ;
				else ins(idx[k][i][j] , idx[k + 1][i][j] , v) ;

				///

				if (k <= d) continue ;

				for (int ty = 0 ; ty < 4 ; ++ty) {
					int ni = i + dx[ty] , nj = j + dy[ty] ;

					if (ni <= 0 || nj <= 0 || ni > p || nj > q) continue ;

					ins(idx[k][i][j] , idx[k - d][ni][nj] , INF) ;
				}
			}

	///

	int ans = dinic() ;
	printf("%d\n" , ans) ;

	return 0 ;
}