#include <queue>
#include <stack>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 1000 + 10 , MAX_M = 50000 + 10 ;

struct Link {
	int num ; Link *next ;
}list[MAX_M] ;
struct Edge {
	int x , y ;
}e[MAX_M] ;

std::queue<int> q ;
std::stack<int> sta ;

Link *head[MAX_N] ;
int col[MAX_N] , sum[MAX_N] , f[MAX_N] , in[MAX_N] ;
int n , m , tot , cur , time , state[MAX_N] , dfn[MAX_N] , low[MAX_N] ;

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

void dfs(int x) {
	dfn[x] = low[x] = ++time ;
	state[x] = 1 ; sta.push(x) ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;

		if (state[nx] == 2) continue ;
		if (!state[nx]) dfs(nx) ;

		low[x] = std::min(low[x] , low[nx]) ;
	}

	if (dfn[x] == low[x]) {
		++tot ;
		int nx , s = 1 ;
		while ((nx = sta.top()) != x)
			col[nx] = tot , state[nx] = 2 , sta.pop() , ++s ;

		sta.pop() ; col[x] = tot ; state[x] = 2 ; sum[tot] = s ;
	}
}

void init() {
	cur = tot = time = 0 ;
	memset(in , 0 , sizeof(in)) ;
	memset(head , 0 , sizeof(head)) ;
	memset(state , 0 , sizeof(state)) ;
}

int main() {
	int T ; scanf("%d" , &T) ;
	while (T--) {
		init() ;

		scanf("%d %d" , &n , &m) ;
		for (int i = 0 ; i < m ; ++i) {
			int x , y ;
			scanf("%d %d" , &x , &y) ;
			ins(x , y) ;

			e[i].x = x ; e[i].y = y ;
		}

		///

		for (int i = 1 ; i <= n ; ++i)
			if (!state[i]) dfs(i) ;

		cur = 0 ;
		memset(head , 0 , sizeof(head)) ;
		for (int i = 0 ; i < m ; ++i) {
			int a = col[e[i].x] , b = col[e[i].y] ;
			if (a == b) continue ;
			ins(a , b) ; ++in[b] ;
		}

		///
		
		for (int i = 1 ; i <= tot ; ++i) {
			f[i] = sum[i] ;
			if (!in[i]) q.push(i) ;
		}

		int res = 0 ;
		while (!q.empty()) {
			int x = q.front() ; q.pop() ;
			res = std::max(res , f[x]) ;

			for (Link *h = head[x] ; h ; h = h->next) {
				int nx = h->num ;
				f[nx] = std::max(f[nx] , f[x] + sum[nx]) ;

				--in[nx] ;
				if (!in[nx]) q.push(nx) ;
			}
		}

		printf("%d\n" , res) ;
	}

	return 0 ;
}
