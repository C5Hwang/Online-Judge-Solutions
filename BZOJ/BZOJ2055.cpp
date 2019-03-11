#include <queue>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 200 + 20 , INF = 0x3f3f3f3f ;

struct data {int num , cap , val , reg ;} ;

std::queue<int> que ;
std::vector<data> eg[MAX_N] ;

bool vis[MAX_N] ;
int n , m , tot , bh[MAX_N][2] ;
int S , T , dis[MAX_N] , flow[MAX_N] , pre[MAX_N] , id[MAX_N] ;

bool bfs() {
	for (int i = 1 ; i <= tot ; ++i) dis[i] = INF ;

	que.push(S) ;
	dis[S] = 0 ; vis[S] = 1 ; flow[S] = INF ;

	for (; !que.empty() ;) {
		int x = que.front() , siz = eg[x].size() ;
		que.pop() ; vis[x] = 0 ;

		for (int i = 0 ; i < siz ; ++i) {
			int nx = eg[x][i].num ;
			if (!eg[x][i].cap || dis[nx] <= dis[x] + eg[x][i].val) continue ;

			dis[nx] = dis[x] + eg[x][i].val ;
			flow[nx] = std::min(flow[x] , eg[x][i].cap) ; pre[nx] = x ; id[nx] = i ;

			if (!vis[nx]) que.push(nx) , id[nx] = i ;
		}
	}

	return dis[T] < INF ;
}

int work() {
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

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

int main() {
	n = read() ; m = read() ;
	for (int i = 0 ; i <= n ; ++i) bh[i][0] = ++tot , bh[i][1] = ++tot ;

	bh[n + 1][0] = bh[n + 1][1] = ++tot ; S = ++tot ; T = ++tot ;
	ins(bh[0][0] , bh[0][1] , m , 0) ; ins(bh[n + 1][0] , bh[0][0] , INF , 0) ;

	///

	for (int i = 1 ; i <= n ; ++i) {
		int v = read() ;
		ins(bh[0][1] , bh[i][0] , INF , 0) ; ins(bh[i][1] , bh[n + 1][0] , INF , 0) ;
		ins(S , bh[i][1] , v , 0) ; ins(bh[i][0] , T , v , 0) ;
	}
	for (int i = 1 ; i <= n ; ++i)
		for (int j = i + 1 ; j <= n ; ++j) {
			int v = read() ;
			if (v == -1) continue ;

			ins(bh[i][1] , bh[j][0] , INF , v) ;
		}

	printf("%d\n" , work()) ;

	return 0 ;
}