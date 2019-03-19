#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e6 + 10 ;

struct Node {
    int len , cnt ;
    Node *ch[26] , *link ;
}sam[MAX_N << 1] ;
struct Link {
    int num ;
    Link *next ;
}list[MAX_N << 1] ;

Node *last ;
char s[MAX_N] ;
int n , tot , cur ;
Link *head[MAX_N << 1] ;

void extend(int c) {
    Node *cur = &sam[tot++] ;
    cur->len = last->len + 1 ; cur->cnt = 1 ;

    Node *p = last ;
    for (; p && !p->ch[c] ; p = p->link) p->ch[c] = cur ;
    if (!p) cur->link = &sam[0] ;
    else {
        Node *q = p->ch[c] ;
        if (q->len == p->len + 1) cur->link = q ;
        else {
            Node *clone = &sam[tot++] ;
            *clone = *q ; clone->len = p->len + 1 ; clone->cnt = 0 ;

            for (; p && p->ch[c] == q ; p = p->link) p->ch[c] = clone ;
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
    for (Link *h = head[x] ; h ; h = h->next) {
        int nx = h->num ;
        dfs(nx) ; sam[x].cnt += sam[nx].cnt ;
    }
}

int main() {
    scanf("%s" , s) ;
    n = strlen(s) ; last = &sam[tot++] ;

    for (int i = 0 ; i < n ; ++i) extend(s[i] - 'a') ;
    for (int i = 1 ; i < tot ; ++i) ins(sam[i].link - &sam[0] , i) ;

    ///

    dfs(0) ;

    ll ans = 0 ;
    for (int i = tot - 1 ; i ; --i)
    	if (sam[i].cnt > 1) ans = std::max(ans , (ll)sam[i].cnt * sam[i].len) ;
    printf("%lld\n" , ans) ;

    return 0 ;
}