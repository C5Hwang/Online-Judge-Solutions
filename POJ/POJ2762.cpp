#include <stack>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std ;

const int MAX_N = 1000 + 10 , MAX_M = 6000 + 10 ;

struct Edge {
	int x , y ;
}t[MAX_M] ;
struct Link {
	int num ;
	Link *next ;
}list[MAX_M] ;

stack<int> sta ;
Link *head[MAX_N] ;
int n , m , cur , tcol , tim , dfn[MAX_N] , low[MAX_N] , state[MAX_N] , col[MAX_N] , in[MAX_N] , queue[MAX_N] ;

void tarjan(int x) {
	dfn[x] = low[x] = ++tim ;
	state[x] = 1 ; sta.push(x) ;
	
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (state[nx] == 2) continue ;
		if (!state[nx]) tarjan(nx) ;
		
		low[x] = min(low[x] , low[nx]) ;
	}
	
	if (dfn[x] == low[x]) {
		while (sta.top() != x) {
			int nx = sta.top() ; sta.pop() ;
			
			state[nx] = 2 ; col[nx] = tcol ;
		}
		
		state[x] = 2 ; col[x] = tcol++ ; sta.pop() ;
	}
}

void init() {
	tcol = cur = tim = 0 ;
	memset(in , 0 , sizeof(in)) ;
	memset(col , 0 , sizeof(col)) ;
	memset(head , 0 , sizeof(head)) ;
	memset(state , 0 , sizeof(state)) ;
}

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

int main() {
	int Q ; scanf("%d" , &Q) ;
	while (Q--) {
		init() ;
		
		scanf("%d %d" , &n , &m) ;
		for (int i = 0 ; i < m ; ++i) {
			int x , y ;
			scanf("%d %d" , &x , &y) ; ins(x , y) ;
			
			t[i].x = x ; t[i].y = y ;
		}
		
		for (int i = 1 ; i <= n ; ++i)
			if (!state[i]) tarjan(i) ;
		
		///

		cur = 0 ; memset(head , 0 , sizeof(head)) ;
		
		for (int i = 0 ; i < m ; ++i) {
			int x = t[i].x , y = t[i].y ,
				cx = col[x] , cy = col[y] ;
			if (cx == cy) continue ;
			
			++in[cy] ;
			ins(cx , cy) ;
		}
		
		///
		
		bool res = 1 ;
		int L = 0 , R = 0 ;
		for (int i = 0 ; i < tcol ; ++i)
			if (!in[i]) queue[++R] = i ;
		if (R > 1) res = 0 ;

		for (; L < R && res ;) {
			int sum = 0 , x = queue[++L] ;

			for (Link *h = head[x] ; h ; h = h->next) {
				int nx = h->num ;
				--in[nx] ;
				if (!in[nx]) queue[++R] = nx , ++sum ;
			}

			if (sum > 1) res = 0 ;
		}

		if (res) printf("Yes\n") ; else printf("No\n") ;
	}
	
	return 0 ;
}
