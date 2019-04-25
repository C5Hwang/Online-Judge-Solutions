#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 3e5 + 10 , lgN = 30 + 5 , mod = 19921228 ;

struct Query {int op , x , y ;}qry[MAX_N] ; //op1 : add & op2 : del & op3: query
struct Node {
	int sum ;
	Node *ch[2] ;

	void init() {sum = 0 ; ch[0] = ch[1] = NULL ;}
	void update() {
		sum = 0 ;
		for (int i = 0 ; i < 2 ; ++i)
			if (ch[i]) sum += ch[i]->sum ;
	}
}tre[MAX_N * lgN] ;

Node *root ;
int cur , tot , p[MAX_N] , c[MAX_N] , l[MAX_N] , r[MAX_N] ;
int n , m , padd , pfirst , pmod , pprod , cadd , cfirst , cmod , cprod , ladd , lfirst , lmod , lprod,  radd , rfirst , rmod , rprod ;

bool cmp(Query a , Query b) {
	return a.x < b.x || (a.x == b.x && a.op < b.op) ;
}

void modify(Node *&rt , int x , int y , int f , int a) {
	if (f < x || y < f) return ;

	if (!rt) (rt = &tre[cur++])->init() ;
	if (x == y) {rt->sum += a ; return ;}

	int mid = (x + y) >> 1 ;
	modify(rt->ch[0] , x , mid , f , a) ;
	modify(rt->ch[1] , mid + 1 , y , f , a) ;

	rt->update() ;
}

int find(Node *rt , int x , int y , int a) {
	if (!rt) return 0 ;
	if (x == y) return x ;

	int mid = (x + y) >> 1 , r = rt->ch[1] ? rt->ch[1]->sum : 0 ;
	if (a <= r) return find(rt->ch[1] , mid + 1 , y , a) ;
	else return find(rt->ch[0] , x , mid , a - r) ;
}

int main() {
	scanf("%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d" , &n , &padd , &pfirst , &pmod , &pprod , &cadd , &cfirst , &cmod , &cprod , &ladd , &lfirst , &lmod , &lprod , &radd , &rfirst , &rmod , &rprod) ;

	p[1] = pfirst % pmod ; c[1] = cfirst % cmod ;
	l[1] = lfirst % lmod ; r[1] = rfirst % rmod ;
	m = c[1] ;

	for (int i = 2 ; i <= n ; ++i) {
		p[i] = ((ll)p[i - 1] * pprod + padd + i) % pmod ;
		c[i] = ((ll)c[i - 1] * cprod + cadd + i) % cmod ;
		l[i] = ((ll)l[i - 1] * lprod + ladd + i) % lmod ;
		r[i] = ((ll)r[i - 1] * rprod + radd + i) % rmod ;

		m = std::max(m , c[i]) ;
	}

	///

	for (int i = 1 ; i <= n ; ++i) {
		if (l[i] > r[i]) std::swap(l[i] , r[i]) ;

		qry[tot++] = (Query){1 , l[i] , c[i]} ;
		qry[tot++] = (Query){2 , r[i] + 1 , c[i]} ;
		qry[tot++] = (Query){3 , p[i] , i} ;
	}

	std::sort(qry + 0 , qry + tot , cmp) ;

	///

	int ans = 0 ; root = NULL ;
	for (int i = 0 ; i < tot ; ++i) {
		Query *p = &qry[i] ;

		if (p->op == 1) modify(root , 0 , m , p->y , 1) ;
		else if (p->op == 2) modify(root , 0 , m , p->y , -1) ;
		else (ans += find(root , 0 , m , p->y)) %= mod ;
	}

	printf("%d\n" , ans) ;

	return 0 ;
}