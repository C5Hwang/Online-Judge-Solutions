#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

const int MAX_N = 100000 + 10 , MAX_C = 1000000 + 10 ;

struct Node {
	int num , s , r ;
	Node *ch[2] ;

	int cmp(int x) {
		if (x == num) return -1 ;
		else if (x < num) return 0 ;
		else return 1 ;
	}
}tre[2 * MAX_N] ;

Node *root[MAX_C] ;
int n , m , cur , sum , fa[MAX_N] ;

void update(Node *rt) {
	int sum = 1 ;
	for (int i = 0 ; i < 2 ; ++i)
		sum += rt->ch[i] ? rt->ch[i]->s : 0 ;
		
	rt->s = sum ;
}

void rotate(Node *&rt , int d) {
	Node *son = rt->ch[d^1] ;
	
	rt->ch[d^1] = son->ch[d] ; son->ch[d] = rt ; rt = son ;
	update(rt->ch[d]) ; update(rt) ;
}

void ins(Node *&rt , int x) {
	if (!rt) {
		rt = &tre[++cur] ;
		rt->num = x ; rt->r = rand() ;
		rt->ch[0] = rt->ch[1] = NULL ;

		return ;
	}

	int d = rt->cmp(x) ;

	ins(rt->ch[d] , x) ; update(rt) ;
	if (rt->ch[d]->r < rt->r) rotate(rt , d^1) ;
}

///

int findset(int x) {
	if (fa[x] == -1) return x ;
	fa[x] = findset(fa[x]) ;
	
	return fa[x] ;
}

bool find(Node *rt , int x) {
	if (!rt) return 0 ;

	int d = rt->cmp(x) ;

	if (d == -1) return 1 ;
	else return find(rt->ch[d] , x) ;
}

void mergeEdge(int x , int y) {
	int fx = findset(x) , fy = findset(y) ;
	
	if (fx == fy) return ;
	
	fa[fx] = fy ;
	--sum ;
}

void add(int color , int a) {
	int la = a - 1 , ra = a + 1 ;

	bool lb = find(root[color] , la) ,
	     rb = find(root[color] , ra) ;
	
	ins(root[color] , a) ;
	if (lb) mergeEdge(a , la) ;
	if (rb) mergeEdge(a , ra) ;
}

void dfs(Node *rt , int color) {
	if (!rt) return ;

	add(color , rt->num) ;

	dfs(rt->ch[0] , color) ;
	dfs(rt->ch[1] , color) ;
}

void mergeTreap(int c1 , int c2) {
	int s1 = root[c1] ? root[c1]->s : 0 ,
	    s2 = root[c2] ? root[c2]->s : 0 ;

	if (s1 > s2) std::swap(root[c1] , root[c2]) ;

	dfs(root[c1] , c2) ;
	root[c1] = 0 ;
}

int main() {
	scanf("%d %d" , &n , &m) ; sum = n ;
	memset(fa , -1 , sizeof(fa)) ;
	memset(root , 0 , sizeof(root)) ;

	///

	for (int i = 1 ; i <= n ; ++i) {
		int color ;
		scanf("%d" , &color) ;

		add(color , i) ;
	}

	///
	
	for (int i = 0 ; i < m ; ++i) {
		int q ; int x , y ;
		scanf("%d" , &q) ;
		if (q == 2) printf("%d\n" , sum) ;
		else {
			scanf("%d %d" , &x , &y) ;

			if (x != y) mergeTreap(x , y) ;
		}
	}

	return 0 ;
}
