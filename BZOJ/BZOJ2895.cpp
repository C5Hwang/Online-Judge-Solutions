#include <queue>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 5e3 + 10 , MAX_P = 3e3 + 10 , INF = 0x3f3f3f3f ;

struct data {int num , cap , val , reg ;} ;

std::queue<int> que ;
std::vector<data> eg[MAX_P] ;

bool vis[MAX_P] ;
int T , dis[MAX_P] , flow[MAX_P] , pre[MAX_P] , id[MAX_P] ;
int n , m , tot , sum , a[MAX_N] , b[MAX_N] , C[MAX_N] , D[MAX_N] , tm[MAX_N] , in[MAX_N] , t[MAX_N][2] ;

bool bfs() {
	for (int i = 0 ; i <= tot ; ++i) dis[i] = INF ;

	que.push(0) ;
	dis[0] = 0 ; vis[0] = 1 ; flow[0] = INF ;

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

		for (int x = T ; x ;) {
			int nx = x , p = id[x] ; x = pre[x] ;

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
	n = read() ; m = read() ; T = ++tot ;
	for (int i = 1 ; i <= n ; ++i)
		{a[i] = read() ; b[i] = read() ; C[i] = read() ; D[i] = read() ;}
	for (int i = 1 ; i <= m ; ++i) {
		int x , y ; x = read() ; y = read() ;
		t[i][0] = x ; t[i][1] = y ; ++in[x] ; ++in[y] ;
	}

	///

	for (int i = 1 ; i <= n ; ++i) {
		b[i] += in[i] ; sum += a[i] * a[i] * C[i] + b[i] * b[i] * D[i] ;

		for (int j = 0 ; j < in[i] ; ++j) {
			int idx = ++tot ;

			ins(idx , T , 1 , C[i] * ((a[i] + j) << 1) - D[i] * ((b[i] - j) << 1) + C[i] + D[i]) ;
			if (j) ins(idx - 1 , idx , INF , 0) ;
			else tm[i] = idx ;
		}
	}
	for (int i = 1 ; i <= m ; ++i) {
		int x = t[i][0] , y = t[i][1] , idx = ++tot ;

		ins(0 , idx , 1 , 0) ;
		ins(idx , tm[x] , INF , 0) ; ins(idx , tm[y] , INF , 0) ;
	}

	printf("%d\n" , sum + work()) ;

	return 0 ;
}