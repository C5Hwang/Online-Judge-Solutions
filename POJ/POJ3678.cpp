#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std ;

const int MAX_N = 1000 + 10 , MAX_M = 1000000 + 10 ;

struct Link {
	int num ;
	Link *next ;
}list[4 * MAX_M] ;

stack<int> sta ;
Link *head[2 * MAX_N] ;
int n , m , dft , cur , tot , state[2 * MAX_N] , col[2 * MAX_N] , dfn[2 * MAX_N] , low[2 * MAX_N] ;

int id(int x) {return x * 2 ;}

void tarjan(int x) {
	state[x] = 1 ;
	dfn[x] = low[x] = ++dft ; sta.push(x) ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (state[nx] == 2) continue ;
		if (!state[nx]) tarjan(nx) ;

		low[x] = min(low[x] , low[nx]) ;
	}

	if (dfn[x] == low[x]) {
		while (sta.top() != x) {
			int nx = sta.top() ; sta.pop() ;
			col[nx] = tot ; state[nx] = 2 ;
		}

		sta.pop() ; col[x] = tot++ ; state[x] = 2 ;
	}
}

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

bool check() {
	for (int i = 0 ; i < n ; ++i)
		if (col[id(i)] == col[id(i)^1]) return 0 ;
	return 1 ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 0 ; i < m ; ++i) {
		int x , y , c ; char op[5] ;
		scanf("%d %d %d %s" , &x , &y , &c , op) ;

		if (op[0] == 'A') {
			if (c) ins(id(x) , id(x)^1) , ins(id(y) , id(y)^1) ;
			else ins(id(x)^1 , id(y)) , ins(id(y)^1 , id(x)) ;
		}
		else if (op[0] == 'O') {
			if (c) ins(id(x) , id(y)^1) , ins(id(y) , id(x)^1) ;
			else ins(id(x)^1 , id(x)) , ins(id(y)^1 , id(y)) ;
		}
		else {
			if (c) {
				ins(id(x)^1 , id(y)) ; ins(id(x) , id(y)^1) ;
				ins(id(y)^1 , id(x)) ; ins(id(y) , id(x)^1) ;
			}
			else {
				ins(id(x)^1 , id(y)^1) ; ins(id(x) , id(y)) ;
				ins(id(y)^1 , id(x)^1) ; ins(id(y) , id(x)) ;
			}
		}
	}

	///
	
	for (int i = 0 ; i < 2 * n ; ++i)
		if (!state[i]) tarjan(i) ;
	if (check()) printf("YES\n") ;
	else printf("NO\n") ;

	return 0 ;
}
