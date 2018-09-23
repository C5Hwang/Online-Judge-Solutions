#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 200 + 10 , MAX_NN = 40000 + 10 , INF = 0x3f3f3f3f ,
	  	  dx[4] = {0 , 0 , -1 , 1} ,
		  dy[4] = {-1 , 1 , 0 , 0} ;

struct Link {
	int num , f ;
	Link *next , *reg ;
}list[10 * MAX_NN] ;

std::queue<int> q ;

Link *head[MAX_NN] ;
int time , bft[MAX_NN] , dep[MAX_NN] ;
int n , m , S , T , cur , a[MAX_N][MAX_N] , bh[MAX_N][MAX_N] , col[MAX_N][MAX_N] ;

///

void ins(int x , int y , int v) {
	list[cur].f = v ;
	list[cur].num = y ;
	list[cur].next = head[x] ;
	list[cur].reg = &list[cur + 1] ;
	head[x] = &list[cur++] ;

	list[cur].f = 0 ;
	list[cur].num = x ;
	list[cur].next = head[y] ;
	list[cur].reg = &list[cur - 1] ;
	head[y] = &list[cur++] ;
}

///

bool bfs() {
	q.push(S) ;
	bft[S] = ++time ; dep[S] = 1 ;
	while (!q.empty()) {
		int x = q.front() ; q.pop() ;

		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ;
			if (!h->f || bft[nx] == time) continue ;

			q.push(nx) ;
			bft[nx] = time ; dep[nx] = dep[x] + 1 ;
		}
	}

	return bft[T] == time ;
}

int dfs(int x , int flow) {
	if (x == T || !flow) return flow ;

	int sum = 0 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (dep[nx] != dep[x] + 1) continue ;

		int nf = dfs(nx , std::min(flow , h->f)) ;
		sum += nf ; flow -= nf ;
		h->f -= nf ; h->reg->f += nf ;
	}

	return sum ;
}

int dinic() {
	int sum = 0 ;
	while (bfs())
		sum += dfs(S , INF) ;

	return sum ;
}

int main() {
	scanf("%d %d" , &n , &m) ;

	int sum = 0 ; col[0][1] = 0 ;
	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= m ; ++j) {
			scanf("%d" , &a[i][j]) ;
			sum += a[i][j] ; bh[i][j] = ++cur ;
			if (j == 1) col[i][j] = col[i - 1][j]^1 ;
			else col[i][j] = col[i][j - 1]^1 ;
		}

	///
	
	S = 0 ; T = cur + 1 ; cur = 0 ;
	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= m ; ++j) {
			if (col[i][j]) ins(S , bh[i][j] , a[i][j]) ;
			else {ins(bh[i][j] , T , a[i][j]) ; continue ;}

			for (int k = 0 ; k < 4 ; ++k) {
				int nx = i + dx[k] , ny = j + dy[k] ;

				if (nx < 1 || ny < 1 || nx > n || ny > m) continue ;

				ins(bh[i][j] , bh[nx][ny] , INF) ;
			}
		}

	///
	
	int ans = dinic() ;

	printf("%d\n" , sum - ans) ;

	return 0 ;
}
