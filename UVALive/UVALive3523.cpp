#include <stack>
#include <queue>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 1000 + 10 , MAX_M = 1000000 + 10 ;

struct Edge {int x , y ;} ;
struct Link {
	int num ; Link *next ;
}list[2][2 * MAX_M] ;

std::stack<Edge> sta ;
std::queue<int> queue ;

Link *head[2][MAX_N] ;
int tn[MAX_N] , col[MAX_N] ;
bool ed[MAX_N][MAX_N] , valu[MAX_N] ;
int n , m , cur[2] , time , tot , low[MAX_N] , dfn[MAX_N] ;

void ins(int type , int x , int y) {	
	list[type][cur[type]].num = y ;
	list[type][cur[type]].next = head[type][x] ;
	head[type][x] = &list[type][cur[type]++] ;
}

void dfs(int x , int fa) {
	low[x] = dfn[x] = ++time ;

	for (Link *h = head[0][x] ; h ; h = h->next) {
		int nx = h->num ;

		if (dfn[nx]) {
			if (nx != fa) low[x] = std::min(low[nx] , low[x]) ;
			continue ;
		}

		sta.push((Edge){x , nx}) ;
		dfs(nx , x) ;
		low[x] = std::min(low[x] , low[nx]) ;

		if (low[nx] >= dfn[x]) {
			++tot ;
			
			for (;;) {
				Edge e = sta.top() ; sta.pop() ;
				ins(1 , tot , e.x) ; ins(1 , tot , e.y) ;
				
				if (e.x == x && e.y == nx) break;
			}
		}
	}
}

bool check(int i) {
	for (Link *h = head[1][i] ; h ; h = h->next)
		tn[h->num] = i ;

	///

	int ind = 4 * i + 1 , num = head[1][i]->num ;
	queue.push(num) ; col[num] = 2 * i ;

	while (!queue.empty()) {
		int x = queue.front() ; queue.pop() ;

		for (Link *h = head[0][x] ; h ; h = h->next) {
			int nx = h->num ;

			if (tn[nx] != i) continue ;

			if (col[nx] != 2 * i && col[nx] != 2 * i + 1) col[nx] = ind - col[x] , queue.push(nx) ;
			else if (col[nx] == col[x]) return 1 ;
		}
	}

	return 0 ;
}

void init() {
	cur[0] = cur[1] = tot = time = 0 ;
	memset(tn , 0 , sizeof(tn)) ;
	memset(ed , 0 , sizeof(ed)) ;
	memset(dfn , 0 , sizeof(dfn)) ;
	memset(low , 0 , sizeof(low)) ;
	memset(col , 0 , sizeof(col)) ;
	memset(head , 0 , sizeof(head)) ;
	memset(valu , 0 , sizeof(valu)) ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	
	while (n != 0 && m != 0) {
		init() ;
		
		for (int i = 0 ; i < m ; ++i) {
			int x , y ;
			scanf("%d %d" , &x , &y) ;
			ed[x][y] = ed[y][x] = 1 ;
		}
		
		for (int i = 1 ; i <= n ; ++i)
			for (int j = 1 ; j <= n ; ++j)
				if (i != j && !ed[i][j]) ins(0 , i , j) ;
	
		///
		
		for (int i = 1 ; i <= n ; ++i)
			if (!dfn[i]) dfs(i , -1) ;
	
		///
		
		for (int i = 1 ; i <= tot ; ++i)
			if (check(i))
				for (Link *h = head[1][i] ; h ; h = h->next)
					valu[h->num] = 1 ;
		
		///
		
		int res = 0 ;
		
		for (int i = 1 ; i <= n ; ++i)
			if (!valu[i]) ++res ;
	
		printf("%d\n" , res) ;
		
		scanf("%d %d" , &n , &m) ;
	}

	return 0 ;
}
