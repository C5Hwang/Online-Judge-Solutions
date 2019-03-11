#include <queue>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 100 + 10 , MAX_M = 1e4 + 10 , INF = 0x3f3f3f3f ;

struct data {int num , cap , val , reg ;} ;
struct Link {
	int num ;
	Link *next ;
}list[MAX_M] ;

std::queue<int> que ;
std::vector<data> eg[MAX_N] ;

bool vis[MAX_N] ;
Link *head[MAX_N] ;
int n , cur , v[MAX_N] , dep[MAX_N] , in[MAX_N] ;
int T , dis[MAX_N] , flow[MAX_N] , pre[MAX_N] , id[MAX_N] ;

///

bool bfs() {
	for (int i = 1 ; i <= T ; ++i) dis[i] = INF ;
	que.push(0) ; dis[0] = 0 ; vis[0] = 1 ; flow[0] = INF ;

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

///

void topo() {
	for (int i = 1 ; i <= n ; ++i) if (!in[i]) que.push(i) , dep[i] = 1 ;

	for (; !que.empty() ;) {
		int x = que.front() ; que.pop() ;

		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ; --in[nx] ;

			if (!in[nx]) que.push(nx) , dep[nx] = dep[x] + 1 ;
		}
	}
}

void add_edge(int x , int y) {
	++in[y] ;
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
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

///

int main() {
	n = read() ; T = n + 1 ;
	for (int i = 1 ; i <= n ; ++i) {
		int m = read() ;

		for (; m-- ;) {
			int j = read() ; --v[i] ; ++v[j] ;
			ins(i , j , INF , 0) ; add_edge(i , j) ;
		}
	}

	///

	topo() ;
	for (int i = 1 ; i <= n ; ++i) {
		if (v[i] > 0) ins(0 , i , v[i] , 0) ;
		else ins(i , T , -v[i] , 0) ;

		for (int j = 1 ; j <= n ; ++j) if (dep[i] < dep[j]) ins(j , i , INF , 1) ;
	}

	printf("%d\n" , work()) ;

	return 0 ;
}