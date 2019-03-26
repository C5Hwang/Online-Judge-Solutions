#include <queue>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e3 + 10 , MAX_P = 2e3 + 10 , INF = 0x3f3f3f3f ;

struct data {int num , cap , val , reg ;} ;

std::queue<int> que ;
std::vector<data> eg[MAX_P] ;

bool vis[MAX_P] ;
int n , P , M , F , N , S , tot , bh[MAX_N][2] ;
int SS , TT , flow[MAX_P] , dis[MAX_P] , pre[MAX_P] , id[MAX_P] ;

bool bfs() {
	for (int i = 0 ; i <= tot ; ++i) dis[i] = INF ;

	que.push(SS) ;
	dis[SS] = 0 ; vis[SS] = 1 ; flow[SS] = INF ;

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

	return dis[TT] < INF ;
}

inline int work() {
	int sum = 0 ;
	for (; bfs() ;) {
		sum += flow[TT] * dis[TT] ;

		for (int x = TT ; x != SS ;) {
			int nx = x , p = id[nx] ; x = pre[x] ;

			eg[x][p].cap -= flow[TT] ; eg[nx][eg[x][p].reg].cap += flow[TT] ;
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
	tot = 1 ; SS = ++tot ; TT = ++tot ;
	scanf("%d %d %d %d %d %d" , &n , &P , &M , &F , &N , &S) ;
	for (int i = 1 ; i <= n ; ++i) bh[i][0] = ++tot , bh[i][1] = ++tot ;

	///

	ins(1 , 0 , INF , 0) ;
	for (int i = 1 ; i <= n ; ++i) {
		int v ; scanf("%d" , &v) ;

		ins(0 , bh[i][0] , INF , P) ; ins(bh[i][1] , 1 , INF , 0) ;
		ins(SS , bh[i][1] , v , 0) ; ins(bh[i][0] , TT , v , 0) ;

		if (i < n) ins(bh[i][0] , bh[i + 1][0] , INF , 0) ;
		if (i + M <= n) ins(bh[i][1] , bh[i + M][0] , INF , F) ;
		if (i + N <= n) ins(bh[i][1] , bh[i + N][0] , INF , S) ;
	}

	printf("%d\n" , work()) ;

	return 0 ;
}