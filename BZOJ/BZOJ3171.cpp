#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const char ty[4] = {'R' , 'L' , 'D' , 'U'} ;
const int dx[4] = {0 , 0 , 1 , -1} , dy[4] = {1 , -1 , 0 , 0} ;
const int MAX_N = 15 + 5 , MAX_P = 500 + 10 , MAX_M = 3e3 + 10 , INF = 0x3f3f3f3f ;

struct Link {
	int num , cap , val ;
	Link *next , *reg ;
}list[MAX_M << 1] ;

std::queue<int> que ;

bool vis[MAX_P] ;
char s[MAX_N][MAX_N] ;
Link *head[MAX_P] , *id[MAX_P] ;
int n , m , tot , cur , bh[MAX_N][MAX_N][2] ;
int T , dis[MAX_P] , pre[MAX_P] , flow[MAX_P] ;

bool bfs() {
	for (int i = 0 ; i <= tot ; ++i) dis[i] = INF ;

	que.push(0) ;
	dis[0] = 0 ; flow[0] = INF ; vis[0] = 1 ;

	for (; !que.empty() ;) {
		int x = que.front() ;
		vis[x] = 0 ; que.pop() ;

		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ;
			if (!h->cap || dis[nx] <= dis[x] + h->val) continue ;

			dis[nx] = dis[x] + h->val ;
			flow[nx] = std::min(flow[x] , h->cap) ; pre[nx] = x ; id[nx] = h ;

			if (!vis[nx]) vis[nx] = 1 , que.push(nx) ;
		}
	}

	return dis[T] < INF ;
}

inline int work() {
	int sum = 0 ;
	for (; bfs() ;) {
		sum += flow[T] * dis[T] ;

		for (int x = T ; x ; x = pre[x])
			id[x]->cap -= flow[T] , id[x]->reg->cap += flow[T] ;
	}

	return sum ;
}

void ins(int x , int y , int f , int v) {
	list[cur].num = y ;
	list[cur].cap = f ;
	list[cur].val = v ;
	list[cur].next = head[x] ;
	list[cur].reg = &list[cur^1] ;
	head[x] = &list[cur++] ;

	list[cur].num = x ;
	list[cur].cap = 0 ;
	list[cur].val = -v ;
	list[cur].next = head[y] ;
	list[cur].reg = &list[cur^1] ;
	head[y] = &list[cur++] ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 0 ; i < n ; ++i) scanf("%s" , s[i]) ;

	T = ++tot ;
	for (int i = 0 ; i < n ; ++i)
		for (int j = 0 ; j < m ; ++j)
			bh[i][j][0] = ++tot , bh[i][j][1] = ++tot ;

	///

	for (int i = 0 ; i < n ; ++i)
		for (int j = 0 ; j < m ; ++j) {
			ins(0 , bh[i][j][0] , 1 , 0) ; ins(bh[i][j][1] , T , 1 , 0) ;

			for (int k = 0 ; k < 4 ; ++k) {
				int ni = (i + dx[k] + n) % n , nj = (j + dy[k] + m) % m ;

				ins(bh[i][j][0] , bh[ni][nj][1] , 1 , (s[i][j] == ty[k]) ^ 1) ;
			}
		}

	printf("%d\n" , work()) ;

	return 0 ;
}