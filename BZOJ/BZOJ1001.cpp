#include <queue>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1000 + 10 , MAX_P = 2e6 + 10 , MAX_M = 6e6 + 10 , INF = 0x3f3f3f3f ;

struct data {
	int idx , num ;

	friend bool operator <(data x , data y) {return x.num > y.num ;}
} ;
struct Link {
	int num , val ;
	Link *next ;
}list[MAX_M] ;

std::priority_queue<data> que ;

bool vis[MAX_P] ;
Link *head[MAX_P] ;
int n , m , T , cur , tot , miv , bh[MAX_N][MAX_N][2] , dis[MAX_P] ;

int work() {
	for (int i = 1 ; i <= tot ; ++i) dis[i] = INF ;
	dis[0] = 0 ; que.push((data){0 , 0}) ;

	for (; ;) {
		data x ;
		for (; !que.empty() && vis[(x = que.top()).idx] ; que.pop()) ;
		if (que.empty()) return dis[T] ;

		for (Link *h = head[x.idx] ; h ; h = h->next) {
			int nx = h->num ;

			if (dis[nx] > dis[x.idx] + h->val) {
				dis[nx] = dis[x.idx] + h->val ;
				que.push((data){nx , dis[nx]}) ;
			}
		}

		vis[x.idx] = 1 ;
	}

	return dis[T] ;
}

void ins(int x , int y , int v) {
	list[cur].num = y ;
	list[cur].val = v ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
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
	for (int i = 1 ; i < n ; ++i)
		for (int j = 1 ; j < m ; ++j) bh[i][j][0] = ++tot , bh[i][j][1] = ++tot ;
	T = ++tot ;

	///

	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j < m ; ++j) {
			int t = read() , id1 , id2 ;

			if (i == 1) id1 = bh[i][j][0] , id2 = 0 ;
			else if (i == n) id1 = bh[i - 1][j][1] , id2 = T ;
			else id1 = bh[i][j][0] , id2 = bh[i - 1][j][1] ;

			ins(id1 , id2 , t) ; ins(id2 , id1 , t) ;
		}
	for (int i = 1 ; i < n ; ++i)
		for (int j = 1 ; j <= m ; ++j) {
			int t = read() , id1 , id2 ;

			if (j == 1) id1 = bh[i][j][1] , id2 = T ;
			else if (j == m) id1 = bh[i][j - 1][0] , id2 = 0 ;
			else id1 = bh[i][j][1] , id2 = bh[i][j - 1][0] ;

			ins(id1 , id2 , t) ; ins(id2 , id1 , t) ;
		}
	for (int i = 1 ; i < n ; ++i)
		for (int j = 1 ; j < m ; ++j) {
			int t = read() , id1 = bh[i][j][0] , id2 = bh[i][j][1] ;

			ins(id1 , id2 , t) ; ins(id2 , id1 , t) ;
		}

	printf("%d\n" , work()) ;

	return 0 ;
}