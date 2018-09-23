#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_L = 1e5 + 10 , MAX_T = 10 + 10 ;

struct state {
	int len , ans[MAX_T] ;
	state *link , *next[30] ;
}sam[MAX_L << 1] ;
struct Link {
	int num ;
	Link *next ;
}list[MAX_L << 1] ;

state *last ;
char s[MAX_T][MAX_L] ;
Link *head[MAX_L << 1] ;
int len[MAX_T] , n , tot , cur ;

void extend(int c) {
	state *cur = &sam[++tot] , *p = last ;
	cur->len = last->len + 1 ;

	for (; p && !p->next[c] ; p = p->link) p->next[c] = cur ;
	if (!p) cur->link = &sam[0] ;
	else {
		state *q = p->next[c] ;
		if (p->len + 1 == q->len) cur->link = q ;
		else {
			state *clone = &sam[++tot] ;
			*clone = *q ; clone->len = p->len + 1 ;

			for (; p && p->next[c] == q ; p = p->link) p->next[c] = clone ;
			cur->link = q->link = clone ;
		}
	}

	last = cur ;
}

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

void dfs(int x) {
	state *p = &sam[x] ;
	for (Link *h = head[x] ; h ; h = h->next) dfs(h->num) ;

	if (!p->link) return ;
	for (int i = 1 ; i < n ; ++i)
		p->link->ans[i] = std::max(p->link->ans[i] , p->ans[i]) ;
}

int main() {
	for (; scanf("%s" , s[n]) != EOF ; ++n)
		len[n] = strlen(s[n]) ;

	///
	
	last = &sam[0] ;
	last->len = 0 ; last->link = NULL ;
	for (int i = 0 ; i < len[0] ; ++i)
		extend(s[0][i] - 'a') ;
	for (int i = 1 ; i <= tot ; ++i)
		ins(sam[i].link - &sam[0] , i) ;

	///
	
	for (int i = 1 ; i < n ; ++i) {
		int l = 0 ; state *p = &sam[0] ;
		
		for (int j = 0 ; j < len[i] ; ++j) {
			int c = s[i][j] - 'a' ;

			for (; p && !p->next[c] ; p = p->link , l = p ? p->len : 0) ;
			if (!p) p = &sam[0] ;
			else p = p->next[c] , ++l ;

			p->ans[i] = std::max(p->ans[i] , l) ;
		}
	}
	dfs(0) ;

	///
	
	int res = 0 ;
	for (int i = 1 ; i <= tot ; ++i) {
		state *p = &sam[i] ;
		int temp = p->len ;

		for (int j = 1 ; j < n ; ++j) temp = std::min(temp , p->ans[j]) ;
		res = std::max(res , temp) ;
	}
	printf("%d\n" , res) ;

	return 0 ;
}
