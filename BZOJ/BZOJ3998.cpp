#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 5e5 + 10 ;

struct Node {
    int len , cnt[2] ; ll f[2] ;
    Node *ch[26] , *fail ;
}sam[MAX_N << 1] ;
struct Link {
    Node *p ;
    Link *next ;
}list[MAX_N << 1] ;

Node *last ;
char s[MAX_N] ;
Link *head[MAX_N] ;
int n , T , k , tot , cur ;

void extend(int c) {
    Node *cur = &sam[tot++] , *p = last ;
    cur->len = last->len + 1 ; cur->cnt[0] = cur->cnt[1] = 1 ;

    for (; p && !p->ch[c] ; p = p->fail) p->ch[c] = cur ;
    if (!p) cur->fail = &sam[0] ;
    else {
        Node *q = p->ch[c] ;
        if (q->len == p->len + 1) cur->fail = q ;
        else {
            Node *clone = &sam[tot++] ;
            *clone = *q ; clone->len = p->len + 1 ; clone->cnt[1] = 0 ;

            for (; p && p->ch[c] == q ; p = p->fail) p->ch[c] = clone ;
            q->fail = cur->fail = clone ;
        }
    }
    last = cur ;
}

void ins(int x , Node *y) {
    list[cur].p = y ;
    list[cur].next = head[x] ;
    head[x] = &list[cur++] ;
}

int main() {
    scanf("%s %d %d" , s , &T , &k) ;
    n = strlen(s) ;

    last = &sam[tot++] ; last->fail = NULL ;
    for (int i = 0 ; i < n ; ++i) extend(s[i] - 'a') ;

    ///

    for (int i = 0 ; i < tot ; ++i) ins(sam[i].len , &sam[i]) ;
    for (int L = n ; L >= 0 ; --L)
    	for (Link *h = head[L] ; h ; h = h->next) {
    		Node *p = h->p ;
    		if (p->fail) p->fail->cnt[1] += p->cnt[1] ;
    		else for (int i = 0 ; i < 2 ; ++i) p->cnt[i] = 0 ;

    		for (int i = 0 ; i < 2 ; ++i) p->f[i] = p->cnt[i] ;
    		for (int i = 0 ; i < 26 ; ++i) {
    			if (!p->ch[i]) continue ;
    			for (int j = 0 ; j < 2 ; ++j) p->f[j] += p->ch[i]->f[j] ;
    		}
    	}

    if (sam[0].f[T] < k) {
        printf("-1\n") ;
        return 0 ;
    }

    ///

    Node *p = &sam[0] ;
    for (; ;) {
        if (k <= p->cnt[T]) {k = 0 ; break ;}

        k -= p->cnt[T] ;
        for (int i = 0 ; i < 26 ; ++i) {
            if (!p->ch[i]) continue ;

            if (p->ch[i]->f[T] >= k) {
                printf("%c" , i + 'a') ;
                p = p->ch[i] ; break ;
            }
            else k -= p->ch[i]->f[T] ;
        }
    }

    printf("\n") ;

    return 0 ;
}