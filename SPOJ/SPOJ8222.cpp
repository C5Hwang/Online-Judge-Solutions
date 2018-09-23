#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 25e4 + 10 ;

struct state {
	int len , cnt ;
	state *next[30] , *link ;
}sam[MAX_N << 1] ;

struct Link {
	int num ;
	Link *next ;
}list[MAX_N << 1] ;

state *last ;
char s[MAX_N] ;
Link *head[MAX_N << 1] ;
int tot , n , cur , f[MAX_N] ;

void extend(int c) {
	state *cur = &sam[++tot] , *p = last ;
	cur->len = p->len + 1 ; cur->cnt = 1 ;

	for (; p && !p->next[c] ; p = p->link) p->next[c] = cur ;
	if (!p) cur->link = &sam[0] ;
	else {
		state *q = p->next[c] ;
		if (p->len + 1 == q->len) cur->link = q ;
		else {
			state *clone = &sam[++tot] ;
			*clone = *q ;
			clone->len = p->len + 1 ; clone->cnt = 0 ;

			for (; p && p->next[c] == q ; p = p->link) p->next[c] = clone ;
			q->link = cur->link = clone ;
		}
	}
	last = cur ;
}

///

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

void dfs(int x) {
	state *p = &sam[x] ;
	for (Link *h = head[x] ; h ; h = h ->next) {
		dfs(h->num) ;

		state *q = &sam[h->num] ;
		p->cnt += q->cnt ;
	}
	f[p->len] = std::max(f[p->len] , p->cnt) ;
}

///

int main() {
	scanf("%s" , s) ;
	n = strlen(s) ;
	
	///
	
	last = &sam[0] ;
	last->len = 0 ; last->link = NULL ;
	for (int i = 0 ; i < n ; ++i)
		extend(s[i] - 'a') ;
	for (int i = 1 ; i <= tot ; ++i) {
		state *p = &sam[i] ;
		ins(p->link - &sam[0] , i) ;
	}

	///
	
	dfs(0) ;
	for (int i = n - 1 ; i > 0 ; --i)
		f[i] = std::max(f[i] , f[i + 1]) ;
	for (int i = 1 ; i <= n ; ++i)
		printf("%d\n" , f[i]) ;

	return 0 ;
}
