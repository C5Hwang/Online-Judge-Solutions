#include <queue>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 300 + 10 , INF = 0x3f3f3f3f ;

struct data {int num , cap , val , reg ;} ;

std::queue<int> que ;
std::vector<data> eg[MAX_N] ;

bool vis[MAX_N] ;
int n , sum , v[MAX_N] ;
int T , flow[MAX_N] , pre[MAX_N] , id[MAX_N] , dis[MAX_N] ;

bool bfs() {
	for (int i = 1 ; i <= T ; ++i) dis[i] = INF ;

	que.push(0) ;
	dis[0] = 0 ; flow[0] = INF ; vis[0] = 1 ;

	for (; !que.empty() ;) {
		int x = que.front() , siz = eg[x].size() ;
		que.pop() ; vis[x] = 0 ;

		for (int i = 0 ; i < siz ; ++i) {
			int nx = eg[x][i].num ;
			if (!eg[x][i].cap || dis[nx] <= dis[x] + eg[x][i].val) continue ;

			dis[nx] = dis[x] + eg[x][i].val ;
			id[nx] = i ; pre[nx] = x ; flow[nx] = std::min(eg[x][i].cap , flow[x]) ;

			if (!vis[nx]) que.push(nx) , vis[nx] = 1 ;
		}
	}

	return dis[T] < INF ;
}

int work() {
	int sum = 0 ;
	for (; bfs() ;) {
		sum += dis[T] * flow[T] ;

		for (int x = T ; x ;) {
			int nx = x , p = id[nx] ; x = pre[x] ;

			eg[x][p].cap -= flow[T] ; eg[nx][eg[x][p].reg].cap += flow[T] ;
		}
	}

	return sum ;
}

void ins(int x , int y , int f , int c) {
	int p1 = eg[x].size() , p2 = eg[y].size() ;

	eg[x].push_back((data){y , f , c , p2}) ;
	eg[y].push_back((data){x , 0 , -c , p1}) ;
}

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

int main() {
	n = read() ; sum = 0 ;
	for (int i = 1 ; i <= n ; ++i) {
		int k = read() ;
		if (i > 1) ins(i , 1 , INF , 0) ;

		for (; k-- ;) {
			int j , t ; j = read() ; t = read() ;
			sum += t ; --v[i] ; ++v[j] ; ins(i , j , INF , t) ;
		}
	}

	T = n + 1 ;
	for (int i = 1 ; i <= n ; ++i)
		if (v[i] > 0) ins(0 , i , v[i] , 0) ;
		else ins(i , T , -v[i] , 0) ;

	printf("%d\n" , sum + work()) ;

	return 0 ;
}