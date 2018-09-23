#include <map>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 25e4 + 10 ;

struct state {
	int len ;
	state *link , *next[30] ;
}sam[MAX_N << 1] ;

state *last ;
int tot , l1 , l2 ;
char s1[MAX_N] , s2[MAX_N] ;

void extend(int c) {
	state *cur = &sam[++tot] , *p = last ;

	for (; p && !p->next[c] ; p = p->link) p->next[c] = cur ;
	if (!p) cur->link = &sam[0] ;
	else {
		state *q = p->next[c] ;
		if (p->len + 1 == q->len) cur->link = q ;
		else {
			state *clone = &sam[++tot] ;
			*clone = *q ;
			clone->len = p->len + 1 ;

			for (; p && p->next[c] == q ; p = p->link) 
				p->next[c] = clone ;
			q->link = cur->link = clone ;
		}
	}

	last = cur ;
}

int main() {
	scanf("%s" , s1) ;
	scanf("%s" , s2) ;
	l1 = strlen(s1) ; l2 = strlen(s2) ;

	///
	
	last = &sam[0] ;
	sam[0].len = 0 ; sam[0].link = NULL ;
	for (int i = 0 ; i < l1 ; ++i)
		extend(s1[i] - 'a') ;

	///
	
	int l = 0 , res = 0 ;
	state *v = &sam[0] ;
	for (int i = 0 ; i < l2 ; ++i) {
		int c = s2[i] - 'a' ;
		for (; v && !v->next[c] ; v = v->link , l = v ? v->len : 0) ;

		if (!v) v = &sam[0] ;
		else v = v->next[c] , ++l ;

		res = std::max(res , l) ;
	}

	printf("%d\n" , res) ;

	return 0 ;
}
