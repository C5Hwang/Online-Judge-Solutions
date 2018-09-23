#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std ;

const int MAX_N = 20000 + 10 , MAX_M = 60000 + 10 , MAX_Q = 600000 + 10 ;

struct Edge {
	int x , y ;
}e[MAX_M] ;
struct Query {
	char q ; int x , y ;
}que[MAX_Q] ;
struct Node {
	int num , s , r ;
	Node *ch[2] ;

	int cmp(int x) {
		if (x <= num) return 0 ;
		else return 1 ;
	}
}tre[2 * MAX_N + MAX_Q] ;

long long skth ;
Node *root[MAX_N] ;
bool addedge[MAX_M] ;
int n , m , sque , sQ , cur , v[MAX_N] , fa[MAX_N] ;

void update(Node *rt) {
	int sum = 1 ;

	for (int i = 0 ; i < 2 ; ++i)
		if (rt->ch[i]) sum += rt->ch[i]->s ;

	rt->s = sum ;
}

void rotate(Node *&rt , int d) {
	Node *son = rt->ch[d^1] ;

	rt->ch[d^1] = son->ch[d] ; son->ch[d] = rt ; rt = son ;

	update(rt->ch[d]) ; update(rt) ;
}

void ins(Node *&rt , int a) {
	if (!rt) {
		rt = &tre[++cur] ;
		rt->num = a ; rt->s = 1 ; rt->r = rand() ;
		rt->ch[0] = rt->ch[1] = NULL ;

		return ;
	}

	int d = rt->cmp(a) ;

	ins(rt->ch[d] , a) ; update(rt) ;
	if (rt->ch[d]->r < rt->r) rotate(rt , d^1) ;
}

void init() {
	sque = cur = sQ = skth = 0 ;
	
	memset(fa , -1 , sizeof(fa)) ;	
	memset(root , 0 , sizeof(root)) ;
	memset(addedge , 0 , sizeof(addedge)) ;
}

void del(Node *&rt , int a) {
	if (rt->num == a) {
		if (!rt->ch[0]) rt = rt->ch[1] ;
		else if (!rt->ch[1]) rt = rt->ch[0] ;
		else {
			int d = rt->ch[0]->r > rt->ch[1]->r ? 0 : 1 ;

			rotate(rt , d) ; del(rt->ch[d] , a) ;
		}
 		
 		if (rt) update(rt) ;
 		
		return ;
	}

	int d = rt->cmp(a) ;

	del(rt->ch[d] , a) ;
	update(rt) ;
}

int kth(Node *rt , int a) {
	if (!rt) return 0 ;
	
	int k = rt->ch[1] ? rt->ch[1]->s + 1 : 1 ;

	if (k == a) return rt->num ;
	else if (k > a) return kth(rt->ch[1] , a) ;
	else return kth(rt->ch[0] , a - k) ;
}

///

int findset(int f) {
	if (fa[f] == -1) return f ;
	fa[f] = findset(fa[f]) ;

	return fa[f] ;
}

void dfs(Node *rt , Node *&newrt) {
	if (!rt) return ;
	
	ins(newrt , rt->num) ;
	dfs(rt->ch[0] , newrt) ; dfs(rt->ch[1] , newrt) ;
}

void merge(int x , int y) {
	int fx = findset(x) , fy = findset(y) ;
	
	if (fx == fy) return ;
	if (root[fx]->s < root[fy]->s) swap(fx , fy) ;
	
	fa[fy] = fx ;
	dfs(root[fy] , root[fx]) ;
}

int main() {
	scanf("%d %d" , &n , &m) ;

	for(int querynumber = 1 ; n != 0 || m != 0 ; ++querynumber) {
		init() ;

		for (int i = 1 ; i <= n ; ++i) {
			scanf("%d" , &v[i]) ;

			fa[i] = -1 ;
		}
		for (int i = 1 ; i <= m ; ++i)
			scanf("%d %d" , &e[i].x , &e[i].y) ;

		///

		char q ;
		getchar() ; scanf("%c" , &q) ;
		while (q != 'E') {
			int x , y = -1 ;
			if (q == 'D') {scanf("%d" , &x) ; addedge[x] = 1 ;}
			else scanf("%d %d" , &x , &y) ;

			if (q == 'C') swap(v[x] , y) ;

			que[++sque].q = q ; que[sque].x = x ; que[sque].y = y ;

			getchar() ; scanf("%c" , &q) ;
		}

		for (int i = 1 ; i <= n ; ++i)
			ins(root[i] , v[i]) ;
		for (int i = 1 ; i <= m ; ++i)
			if (!addedge[i]) merge(e[i].x , e[i].y) ;
		
		///
		
		for (int i = sque ; i > 0 ; --i) {
			q = que[i].q ;
			int x = que[i].x , y = que[i].y ;

			if (q == 'D')
				merge(e[x].x , e[x].y) ;
			else if (q == 'Q')
				{int f = findset(x) ; skth += kth(root[f] , y) ; ++sQ ;}
			else if (q == 'C') {
					int f = findset(x) ;
					del(root[f] , v[x]) ;
					v[x] = y ;
					ins(root[f] , v[x]) ;
				}
		}
		
		printf("Case %d: %0.6lf\n" , querynumber , skth / (double)sQ) ;

		scanf("%d %d" , &n , &m) ;
	}
	
	return 0 ;
}
