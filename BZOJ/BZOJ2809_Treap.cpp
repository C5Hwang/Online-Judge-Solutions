#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 100000 + 10 , lgN = 20 ;

struct Node {
	long long sumc ;
	int cost , sum , r ;
	Node *ch[2] ;

	int cmp(int x) {
		if (x <= cost) return 0 ;
		else return 1 ;
	}
}tre[MAX_N * lgN] ;
struct Link_List {
	int num ;
	Link_List *next ;
}list[MAX_N] ;
struct DFSbh {
	int num , bh ;
}dfn[MAX_N] ;

long long res ;
Node *root[MAX_N] ;
Link_List *head[MAX_N] ;
int n , allc , cur1 , cur2 , lenum[MAX_N] ;

void update(Node *rt) {
	int s1 = 1 ; long long s2 = rt->cost ;

	for (int i = 0 ; i < 2 ; ++i)
		if (rt->ch[i]) {s1 += rt->ch[i]->sum ; s2 += rt->ch[i]->sumc ;}

	rt->sum = s1 ; rt->sumc = s2 ;
}

void rotate(Node *&rt , int d) {
	Node *son = rt->ch[d^1] ;
	rt->ch[d^1] = son->ch[d] ; son->ch[d] = rt ; rt = son ;
	update(rt->ch[d]) ; update(rt) ;
}

void ins(Node *&rt , int co) {
	if (!rt) {
		rt = &tre[++cur2] ;
	 	rt->cost = rt->sumc = co ; rt->sum = 1 ; rt->r = rand() ;
		rt->ch[0] = rt->ch[1] = NULL ;

		return ;
	}

	int d = rt->cmp(co) ;
	ins(rt->ch[d] , co) ; update(rt) ;
	if (rt->ch[d]->r < rt->r) rotate(rt , d^1) ;
}

int query(Node *rt , int valc) {
	if (!rt || valc <= 0) return 0 ;

	int ls = rt->ch[0] ? rt->ch[0]->sum + 1 : 1 ;
	long long lc = rt->ch[0] ? rt->ch[0]->sumc + rt->cost : rt->cost ;

	if (lc > valc) return query(rt->ch[0] , valc) ;
	else return query(rt->ch[1] , valc - lc) + ls ;
}

///

void add(Node *rt , Node *&root) {
	if (!rt) return ;

	ins(root , rt->cost) ;

	add(rt->ch[0] , root) ;
	add(rt->ch[1] , root) ;
}

void merge(Node *&r1 , Node *&r2) {
	if (r1->sum < r2->sum) std::swap(r1 , r2) ;

	add(r2 , r1) ;
}

bool cmp(DFSbh a , DFSbh b) {
	return a.bh > b.bh ;
}

void insEdge(int x , int y) {
	list[cur1].num = y ;
	list[cur1].next = head[x] ;
	head[x] = &list[cur1++] ;
}

int main() {
	res = 0 ;

	scanf("%d %d" , &n , &allc) ;
	for (int i = 1; i <= n ; ++i) {
		int fa , c ;
		scanf("%d %d %d" , &fa , &c , &lenum[i]) ;
		
		ins(root[i] , c) ; insEdge(fa , i) ;
		dfn[i].bh = dfn[fa].bh + 1 ; dfn[i].num = i ;
	}

	///
	
	std::sort(dfn + 1 , dfn + 1 + n , cmp) ;
	
	///
	
	for (int i = 1 ; i <= n ; ++i) {
		int t = dfn[i].num ;

		Link_List *h = head[t] ;
		for (; h ; h = h->next) {
			int nt = h->num ;
			merge(root[t] , root[nt]) ;
		}
		
		long long s = query(root[t] , allc) ;
		
		res = std::max(res , s * lenum[t]) ;
	}

	printf("%lld\n" , res) ;

	return 0 ;
}
