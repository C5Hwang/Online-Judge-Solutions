#include <queue>
#include <stack>
#include <bitset>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 2e3 + 10 ;

std::queue<int> que ;
std::stack<int> sta , topo ;
std::bitset<MAX_N> f[MAX_N] ;

struct Link {
	int num ;
	Link *next ;
}list[MAX_N * MAX_N] ;

bool ap[MAX_N] ;
Link *head[MAX_N] ;
char s[MAX_N][MAX_N] ;
int n , tot , cur , ti , dfn[MAX_N] , low[MAX_N] , state[MAX_N] , pt[MAX_N] , in[MAX_N] ;

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

void tarjan(int x) {
	state[x] = 1 ; sta.push(x) ;
	dfn[x] = low[x] = ++ti ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (state[nx] == 2) continue ;
		if (!state[nx]) tarjan(nx) ;

		low[x] = std::min(low[x] , low[nx]) ;
	}

	if (low[x] == dfn[x]) {
		++tot ;
		while (sta.top() != x) {
			int nx = sta.top() ; sta.pop() ;
			pt[nx] = tot ; state[nx] = 2 ; f[tot][nx] = 1 ;
		}
		pt[x] = tot ; state[x] = 2 ; f[tot][x] = 1 ; sta.pop() ;
	}
}

int main() {
	scanf("%d" , &n) ;
	for (int i = 1 ; i <= n ; ++i) {
		scanf("%s" , s[i]) ;

		for (int j = 1 ; j <= n ; ++j)
			if (s[i][j - 1] == '1') ins(i , j) ;
	}

	///

	for (int i = 1 ; i <= n ; ++i)
		if (!state[i]) tarjan(i) ;

	cur = 0 ;
	memset(head , 0 , sizeof(head)) ;
	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= n ; ++j)
			if (s[i][j - 1] == '1' && pt[i] != pt[j]) ins(pt[i] , pt[j]) , ++in[pt[j]] ;

	///

	for (int i = 1 ; i <= tot ; ++i)
		if (!in[i]) ap[i] = 1 , que.push(i) , topo.push(i) ;
	while (!que.empty()) {
		int x = que.front() ; que.pop() ;

		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ; --in[nx] ;
			if (!in[nx]) {que.push(nx) ; topo.push(nx) ; ap[nx] = 1 ;}
		}
	}

	int res = 0 ;
	while (!topo.empty()) {
		int x = topo.top() , siz = f[x].count() ;
		topo.pop() ;

		for (Link *h = head[x] ; h ; h = h->next)
			f[x] |= f[h->num] ;
		res += siz * f[x].count() ;
	}

	printf("%d\n" , res) ;

	return 0 ;
}
