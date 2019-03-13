#include <queue>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 800 + 10 , MAX_P = 1600 + 10 , INF = 0x3f3f3f3f ;

struct data {int num , cap , val , reg ;} ;

std::queue<int> que ;
std::vector<data> eg[MAX_P] ;

bool vis[MAX_P] ;
int n , m , tot , bh[MAX_N][2] ;
int S , T , dis[MAX_P] , pre[MAX_P] , id[MAX_P] , flow[MAX_P] ;

bool bfs() {
	for (int i = 0 ; i <= tot ; ++i) dis[i] = INF ;

	que.push(S) ;
	dis[S] = 0 ; flow[S] = INF ; vis[S] = 1 ;

	for (; !que.empty() ;) {
		int x = que.front() , siz = eg[x].size() ;
		vis[x] = 0 ; que.pop() ;

		for (int i = 0 ; i < siz ; ++i) {
			int nx = eg[x][i].num ;
			if (!eg[x][i].cap || dis[nx] <= dis[x] + eg[x][i].val) continue ;

			dis[nx] = dis[x] + eg[x][i].val ;
			flow[nx] = std::min(flow[x] , eg[x][i].cap) ; pre[nx] = x ; id[nx] = i ;

			if (!vis[nx]) vis[nx] = 1 , que.push(nx) ;
		}
	}

	return dis[T] < INF ;
}

inline int work() {
	int sum = 0 ;
	for (; bfs() ;) {
		sum += flow[T] * dis[T] ;

		for (int x = T ; x != S ;) {
			int nx = x , p = id[nx] ; x = pre[x] ;

			eg[x][p].cap -= flow[T] ; eg[nx][eg[x][p].reg].cap += flow[T] ;
		}
	}

	return sum ;
}

void ins(int x , int y , int f , int v) {
	int p1 = eg[x].size() , p2 = eg[y].size() ;

	eg[x].push_back((data){y , f , v , p2}) ;
	eg[y].push_back((data){x , 0 , -v , p1}) ;
}

int main() {
	scanf("%d %d" , &n , &m) ;

	S = ++tot ; T = ++tot ;
	for (int i = 1 ; i <= n ; ++i) bh[i][0] = ++tot , bh[i][1] = ++tot ;
	for (int i = 1 ; i <= n ; ++i) {
		int x ; scanf("%d" , &x) ;

		ins(S , bh[i][1] , 1 , 0) ; ins(bh[i][0] , T , 1 , 0) ;
		ins(0 , bh[i][0] , INF , x) ; ins(bh[i][1] , 0 , INF , 0) ;
	}

	for (; m-- ;) {
		int x , y , v ;
		scanf("%d %d %d" , &x , &y , &v) ;

		if (x > y) std::swap(x , y) ;
		ins(bh[x][1] , bh[y][0] , INF , v) ;
	}

	printf("%d\n" , work()) ;

	return 0 ;
}