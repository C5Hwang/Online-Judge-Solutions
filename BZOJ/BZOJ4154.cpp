#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 , mod = 1e9 + 7 ;

struct data {int x , y , idx ;}pt[MAX_N] ;
struct Link {
	int num ;
	Link *next ;
}list[MAX_N] ;
struct Node {
	Node *ch[2] ;
	int mi[2] , ma[2] , p[2] , col , lazy ;

	void init() {
		ch[0] = ch[1] = NULL ;
		for (int i = 0 ; i < 2 ; ++i) mi[i] = ma[i] = p[i] = 0 ;
		lazy = 0 ; col = 1 ;
	}
	void down() {
		if (!lazy) return ;
		for (int i = 0 ; i < 2 ; ++i)
			if (ch[i]) ch[i]->lazy = ch[i]->col = lazy ;
		lazy = 0 ;
	}
	void update() {
		mi[0] = ma[0] = p[0] ; mi[1] = ma[1] = p[1] ;
		for (int i = 0 ; i < 2 ; ++i)
			if (ch[i]) for (int j = 0 ; j < 2 ; ++j)
				mi[j] = std::min(mi[j] , ch[i]->mi[j]) , ma[j] = std::max(ma[j] , ch[i]->ma[j]) ;
	}
}tre[MAX_N] ;

Node *root ;
Link *head[MAX_N] ;
int xl , xr , yl , yr , E ;
int T , n , c , q , ti , tot , cur , ed[MAX_N] ;

///

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

void init() {
	ti = tot = cur = 0 ;
	memset(head , 0 , sizeof(head)) ;
}

bool cmp(data a , data b) {return a.idx < b.idx ;}

bool cmp1(data a , data b) {
	if (E) return a.y < b.y ;
	else return a.x < b.x ;
}

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

void dfs(int x , int dep) {
	pt[++n] = (data){++ti , dep , x} ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		dfs(nx , dep + 1) ;
	}

	ed[x] = ti ;
}

///

void build(Node *&rt , int x , int y , int ty) {
	if (x > y) return ;
	(rt = &tre[tot++])->init() ;

	int mid = (x + y) >> 1 ; E = ty ;
	std::nth_element(pt + x , pt + mid , pt + y + 1 , cmp1) ;
	rt->mi[0] = rt->ma[0] = rt->p[0] = pt[mid].x ;
	rt->mi[1] = rt->ma[1] = rt->p[1] = pt[mid].y ;

	build(rt->ch[0] , x , mid - 1 , ty^1) ; build(rt->ch[1] , mid + 1 , y , ty^1) ;
	rt->update() ;
}

int find(Node *rt) {
	if (!rt) return 0 ;
	if (xl < rt->mi[0] || rt->ma[0] < xl || yl < rt->mi[1] || rt->ma[1] < yl) return 0 ;
	if (rt->p[0] == xl && rt->p[1] == yl) return rt->col ;
	rt->down() ;

	int c1 = find(rt->ch[0]) , c2 = find(rt->ch[1]) ;
	return std::max(c1 , c2) ;
}

void modify(Node *rt , int c) {
	if (!rt) return ;
	if (xr < rt->mi[0] || rt->ma[0] < xl || yr < rt->mi[1] || rt->ma[1] < yl) return ;
	if (xl <= rt->mi[0] && rt->ma[0] <= xr && yl <= rt->mi[1] && rt->ma[1] <= yr) {
		rt->col = rt->lazy = c ;
		return ;
	}

	rt->down() ;
	if (xl <= rt->p[0] && rt->p[0] <= xr && yl <= rt->p[1] && rt->p[1] <= yr) rt->col = c ;
	modify(rt->ch[0] , c) ; modify(rt->ch[1] , c) ;
}

///

int main() {
	scanf("%d" , &T) ;
	for (; T-- ;) {
		init() ;

		n = read() ; c = read() ; q = read() ;
		for (int i = 2 ; i <= n ; ++i) {int a = read() ; ins(a , i) ;}
		n = 0 ; dfs(1 , 1) ;

		///


		build(root , 1 , n , 0) ;
		std::sort(pt + 1 , pt + 1 + n , cmp) ;

		int ans = 0 ;
		for (int i = 1 ; i <= q ; ++i) {
			int a , l , c ;
			a = read() ; l = read() ; c = read() ;

			if (!c) {
				xl = pt[a].x ; yl = pt[a].y ;
				(ans += (ll)i * find(root) % mod) %= mod ;
			}
			else {
				xl = pt[a].x ; xr = ed[a] ; yl = pt[a].y ; yr = pt[a].y + l ;
				modify(root , c) ;
			}
		}

		printf("%d\n" , ans) ;
	}

	return 0 ;
}