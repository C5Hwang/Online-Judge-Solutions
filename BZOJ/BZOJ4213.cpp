#include <queue>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int dx[4] = {0 , 0 , 1 , -1} , dy[4] = {1 , -1 , 0 , 0} ;
const int MAX_N = 12 + 5 , MAX_P = 150 + 10 , MAX_M = 1100 + 10 , INF = 0x3f3f3f3f ;

struct Link {
	int num , cap ;
	Link *next , *reg ;
}list[MAX_M << 1] ;

std::queue<int> que ;

Link *head[MAX_P] ;
char s[MAX_N][MAX_N] ;
int n , m , sum , tot , cur , bh[MAX_N][MAX_N] ;
int S , T , SS , TT , ti , dep[MAX_P] , ap[MAX_P] ;

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
	que.push(S) ;
	dep[S] = 1 ; ap[S] = ++ti ;

	for (; !que.empty() ;) {
		int x = que.front() ; que.pop() ;

		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ;
			if (!h->cap || ap[nx] == ti) continue ;

			que.push(nx) ;
			dep[nx] = dep[x] + 1 ; ap[nx] = ti ;
		}
	}

	return ap[T] == ti ;
}

inline int dinic() {
	std::swap(S , SS) ; std::swap(T , TT) ;

	int sum = 0 ;
	for (; bfs() ; sum += dfs(S , INF)) ;

	return sum ;
}

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

void add_edge(int x , int y , int L , int R) {
	sum += L ;
	ins(SS , y , L) ; ins(x , TT , L) ;
	if (L < R) ins(x , y , R - L) ;
}

int main() {
	for (; scanf("%s" , s[n++]) != EOF ;) ;
	m = strlen(s[0]) ; --n ;

	S = 0 ; T = ++tot ; SS = ++tot ; TT = ++tot ;
	ins(T , S , INF) ;
	for (int i = 0 ; i < n ; ++i)
		for (int j = 0 ; j < m ; ++j)
			if (s[i][j] != '#') bh[i][j] = ++tot ;

	for (int i = 0 ; i < n ; ++i)
		for (int j = 0 ; j < m ; ++j) {
			if (s[i][j] == '#') continue ;

			int idx = bh[i][j] , L = 2 , R = 2 ;
			if (!i || !j || i == n - 1 || j == m - 1) L = 1 ;

			if ((i + j) & 1) add_edge(idx , T , L , R) ;
			else {
				add_edge(S , idx , L , R) ;
				for (int k = 0 ; k < 4 ; ++k) {
					int ni = i + dx[k] , nj = j + dy[k] ;
					if (ni < 0 || nj < 0 || ni >= n || nj >= m || s[ni][nj] == '#') continue ;

					ins(idx , bh[ni][nj] , 1) ;
				}
			}
		}

	///

	int s1 = dinic() ; dinic() ;

	if (s1 != sum) printf("-1\n") ;
	else {
		int s2 = 0 ;
		for (Link *h = head[S] ; h ; h = h->next)
			if (h->cap && h->num != T && h->num != SS && h->num != TT) ++s2 ;
		for (Link *h = head[T] ; h ; h = h->next)
			if (h->reg->cap && h->num != T && h->num != SS && h->num != TT) ++s2 ;

		printf("%d\n" , s2 >> 1) ;
	}

	return 0 ;
}