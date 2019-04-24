#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int N = 30 , MAX_N = 1e5 + 10 , lgN = 30 + 5 ;

struct Node {
	Node *ch[2] ;
}tre[MAX_N * lgN] ;

ll sum ;
Node *root ;
int n , tot , a[MAX_N] ;

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

void ins(int a) {
	Node *rt = root ;
	for (int i = N ; i >= 0 ; --i) {
		int c = (1 << i) & a ? 1 : 0 ;

		if (!rt->ch[c]) rt->ch[c] = &tre[tot++] ;
		rt = rt->ch[c] ;
	}
}

int find(int d , Node *r1 , Node *r2) {
	if (!d) return 0 ;

	if (!r1->ch[0]) {
		if (!r2->ch[1]) return find(d - 1 , r1->ch[1] , r2->ch[0]) + (1 << (d - 1)) ;
		else return find(d - 1 , r1->ch[1] , r2->ch[1]) ;
	}
	else if (!r1->ch[1]) {
		if (!r2->ch[0]) return find(d - 1 , r1->ch[0] , r2->ch[1]) + (1 << (d - 1)) ;
		else return find(d - 1 , r1->ch[0] , r2->ch[0]) ;
	}
	else if (!r2->ch[0]) return find(d - 1 , r1->ch[1] , r2->ch[1]) ;
	else if (!r2->ch[1]) return find(d - 1 , r1->ch[0] , r2->ch[0]) ;
	else {
		int t1 = find(d - 1 , r1->ch[0] , r2->ch[0]) , t2 = find(d - 1 , r1->ch[1] , r2->ch[1]) ;

		return std::min(t1 , t2) ;
	}
}

void work(int d , Node *rt) {
	if (!d || !rt) return ;

	if (!rt->ch[0]) work(d - 1 , rt->ch[1]) ;
	else if (!rt->ch[1]) work(d - 1 , rt->ch[0]) ;
	else {
		work(d - 1 , rt->ch[0]) ; work(d - 1 , rt->ch[1]) ;

		sum += find(d - 1 , rt->ch[0] , rt->ch[1]) + (1 << (d - 1)) ;
	}
}

int main() {
	freopen("secret.in" , "r" , stdin) ;
	freopen("secret.out" , "w" , stdout) ;

	n = read() ;
	a[0] = 0 ; root = &tre[tot++] ;

	ins(a[0]) ;
	for (int i = 1 ; i <= n ; ++i) {
		a[i] = read() ;
		a[i] ^= a[i - 1] ; ins(a[i]) ;
	}

	///

	work(N + 1 , root) ;
	printf("%lld\n" , sum) ;

	fclose(stdin) ; fclose(stdout) ;

	return 0 ;
}