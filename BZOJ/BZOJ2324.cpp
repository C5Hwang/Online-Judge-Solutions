#include <queue>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 150 + 10 , MAX_P = 300 + 10 , INF = 0x3f3f3f3f ;

struct data {int num , cap , val , reg ;} ;

std::queue<int> que ;
std::vector<data> eg[MAX_P] ;

bool vis[MAX_P] ;
int n , m , k , tot , f[MAX_N][MAX_N] , bh[MAX_N][2] ;
int T , dis[MAX_P] , flow[MAX_P] , pre[MAX_P] , id[MAX_P] ;

bool bfs() {
	for (int i = 0 ; i <= tot ; ++i) dis[i] = INF ;

	que.push(0) ;
	vis[0] = 1 ; dis[0] = 0 ; flow[0] = INF ;

	for (; !que.empty() ;) {
		int x = que.front() , siz = eg[x].size() ;
		que.pop() ; vis[x] = 0 ;

		for (int i = 0 ; i < siz ; ++i) {
			int nx = eg[x][i].num ;
			if (!eg[x][i].cap || dis[nx] <= dis[x] + eg[x][i].val) continue ;

			dis[nx] = dis[x] + eg[x][i].val ;
			flow[nx] = std::min(flow[x] , eg[x][i].cap) ; pre[nx] = x ; id[nx] = i ;

			if (!vis[nx]) que.push(nx) , vis[nx] = 1 ;
		}
	}

	return dis[T] < INF ;
}

inline int work() {
	int sum = 0 ;
	for (; bfs() ;) {
		sum += flow[T] * dis[T] ;

		for (int x = T ; x ;) {
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
	n = read() ; m = read() ; k = read() ;
	for (int i = 0 ; i <= n ; ++i)
		for (int j = 0 ; j <= n ; ++j)
			if (i != j) f[i][j] = INF ;
			else f[i][j] = 0 ;

	for (int i = 0 ; i < m ; ++i) {
		int x , y , v ;
		x = read() ; y = read() ; v = read() ;
		if (x > y) std::swap(x , y) ;

		f[x][y] = f[y][x] = std::min(f[x][y] , v) ;
	}

	for (int k = 0 ; k <= n ; ++k)
		for (int i = 0 ; i <= n ; ++i)
			for (int j = 0 ; j <= n ; ++j)
				if (k <= i) f[i][j] = std::min(f[i][j] , f[i][k] + f[k][j]) ;

	///

	T = ++tot ;
	for (int i = 0 ; i <= n ; ++i) {
		bh[i][0] = ++tot ; bh[i][1] = ++tot ;

		if (i) {
			ins(0 , bh[i][1] , 1 , 0) , ins(bh[i][0] , T , 1 , 0) ;
			ins(bh[i][1] , bh[0][0] , INF , 0) ; ins(bh[i][0] , bh[i][1] , INF , 0) ;
		}
		else ins(bh[i][0] , bh[i][1] , k , 0) ;
	}

	for (int i = 0 ; i <= n ; ++i)
		for (int j = i + 1 ; j <= n ; ++j) {
				int v = f[i][j] ;
				if (v >= INF) continue ;

				ins(bh[i][1] , bh[j][0] , INF , v) ;
			}

	printf("%d\n" , work()) ;

	return 0 ;
}