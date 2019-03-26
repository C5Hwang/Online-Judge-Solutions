#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 2e5 + 10 , mod = 1e9 + 7 ;

struct Node {
	int len , minr , maxr ;
	Node *ch[10] , *fail ;

	void init() {
		fail = NULL ;
		for (int i = 0 ; i < 10 ; ++i) ch[i] = NULL ;
	}
}sam[MAX_N << 1] ;
struct Link {
	Node *p ;
	Link *next ;
}list[MAX_N << 1] ;

Node *last ;
char s[MAX_N] ;
Link *head[MAX_N << 1] ;
int n , m , cur , tot , num[MAX_N] ;
ll f[MAX_N] , g[MAX_N] , s1[MAX_N] , s2[MAX_N] ;

void ins(int x , Node *y) {
	list[cur].p = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

void extend(int c , int pl) {
	Node *cur = &sam[tot++] , *p = last ;
	cur->init() ; cur->minr = cur->maxr = pl ; cur->len = last->len + 1 ;

	for (; p && !p->ch[c] ; p = p->fail) p->ch[c] = cur ;
	if (!p) cur->fail = &sam[0] ;
	else {
		Node *q = p->ch[c] ;
		if (p->len + 1 == q->len) cur->fail = q ;
		else {
			Node *clone = &sam[tot++] ;
			*clone = *q ; clone->minr = n + 1 ; clone->maxr = 0 ; clone->len = p->len + 1 ;

			for (; p && p->ch[c] == q ; p = p->fail) p->ch[c] = clone ;
			cur->fail = q->fail = clone ;
		}
	}
	last = cur ;
}

void build(int x , int y , int a) {
	tot = 0 ; (last = &sam[tot++])->init() ;
	for (int i = x ; i != y ; i += a) {
		extend(s[i] - '0' , i) ;

		if (a < 0) s1[i] = s1[i + 1] + last->len - last->fail->len ;
		else s2[i] = s2[i - 1] + last->len - last->fail->len ;
	}

	if (a > 0) {
		cur = 0 ;
		memset(head , 0 , sizeof(head)) ;

		for (int i = 1 ; i < tot ; ++i) ins(sam[i].len , &sam[i]) ;
		for (int i = n ; i ; --i)
			for (Link *h = head[i] ; h ; h = h->next)
				h->p->fail->minr = std::min(h->p->minr , h->p->fail->minr) ,
				h->p->fail->maxr = std::max(h->p->maxr , h->p->fail->maxr) ;
	}
}

void add(int x , int y) {
	int l = y - x + 1 ;
	++g[x + 1] ; --g[y + 2] ;
	g[x] -= l ; g[x + 1] += l ;
}

int main() {
	int T ; scanf("%d" , &T) ;
	for (; T-- ;) {
		scanf("%d %s" , &n , s) ;
		for (int i = n ; i ; --i) s[i] = s[i - 1] ;

		///

		for (int i = 0 ; i <= n + 1 ; ++i) s1[i] = s2[i] = f[i] = g[i] = 0 ;
		build(n , 0 , -1) ; build(1 , n + 1 , 1) ;

		int a = 100013 ; num[0] = 1 ;
		for (int i = 1 ; i <= n ; ++i) num[i] = num[i - 1] * (ll)a % mod ;

		///

		for (int i = 1 ; i < tot ; ++i) {
			Node *p = &sam[i] ;
			int minl = p->fail->len + 1 , maxl = p->len , L = p->minr , R = p->maxr - minl ;

			if (L > R) continue ;
			int nR = p->maxr - maxl , sum = maxl - minl + 1 ;

			if (L > nR) add(L , R) ;
			else {
				f[L] -= sum ; f[nR + 1] += sum ;
				L = nR + 1 ; if (L <= R) add(L , R) ;
			}
		}

		for (int i = 1 ; i <= n ; ++i) g[i] += g[i - 1] ;
		for (int i = 1 ; i <= n ; ++i) g[i] += g[i - 1] ;
		for (int i = 1 ; i <= n ; ++i) f[i] += f[i - 1] ;

		int ans = 0 ;
		for (int i = 1 ; i < n ; ++i) {
			f[i] += g[i] ;
			int res = (s2[i] + s1[i + 1] + f[i]) % mod ;

			ans = (ans + (ll)res * num[n - i - 1]) % mod ;
		}

		printf("%d\n" , ans) ;
	}

	return 0 ;
}