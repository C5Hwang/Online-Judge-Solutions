#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 4e4 + 10 ;

struct Link {
	int num , val ;
	Link *next ;
}list[MAX_N << 1] ;
struct Node {
	int num , s , r ;
	Node *ch[2] ;

	int getrank() {return ch[0] ? ch[0]->s + 1 : 1 ;}
	void newnode(int a) {num = a ; s = 1 ; r = rand() ; ch[0] = ch[1] = NULL ;}
	void update() {
		s = 1 ;
		for (int i = 0 ; i < 2 ; ++i) if (ch[i]) s += ch[i]->s ;
	}
}tre[MAX_N] ;

Node *RT ;
bool vis[MAX_N] ;
Link *head[MAX_N] ;
int n , K , root , msiz , tot , cur , cnt , ans , siz[MAX_N] , dis[MAX_N] ;

///

void ins(int x , int y , int v) {
	list[cur].num = y ;
	list[cur].val = v ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

void rotate(Node *&rt , int d) {
	Node *son = rt->ch[d^1] ;

	rt->ch[d^1] = son->ch[d] ; son->ch[d] = rt ;
	rt->update() ; son->update() ; rt = son ;
}

int cal(Node *rt , int a) {
	if (!rt) return 0 ;

	if (rt->num > a) return cal(rt->ch[0] , a) ;
	else return rt->getrank() + cal(rt->ch[1] , a) ;
}

void add(Node *&rt , int a) {
	if (!rt) {
		rt = &tre[cnt++] ;
		rt->newnode(a) ;
		return ;
	}

	int d = rt->num > a ? 0 : 1 ;
	add(rt->ch[d] , a) ;

	if (rt->ch[d]->r > rt->r) rotate(rt , d^1) ;
	rt->update() ;
}

///

void findroot(int x , int fa) {
	int mx = 0 ; siz[x] = 1 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa || vis[nx]) continue ;

		findroot(nx , x) ;
		siz[x] += siz[nx] ; mx = std::max(mx , siz[nx]) ;
	}
	mx = std::max(mx , tot - siz[x]) ;

	if (msiz > mx) msiz = mx , root = x ;
}

void update(int x , int fa , int d , int ty) {
	if (!ty) ans += cal(RT , K - d) ;
	else add(RT , d) ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa || vis[nx]) continue ;

		update(nx , x , d + h->val , ty) ;
	}
}

void work(int x) {
	vis[x] = 1 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (vis[nx]) continue ;

		update(nx , nx , h->val , 0) ; update(nx , nx , h->val , 1) ;
	}

	cnt = 0 ; RT = NULL ; add(RT , 0) ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (vis[nx]) continue ;

		msiz = tot = siz[nx] ; root = 0 ;
		findroot(nx , nx) ;

		work(root) ;
	}
}

///

int main() {
	scanf("%d" , &n) ;
	for (int i = 1 ; i < n ; ++i) {
		int x , y , v ;
		scanf("%d %d %d" , &x , &y , &v) ;
		ins(x , y , v) ; ins(y , x , v) ;
	}
	scanf("%d" , &K) ;

	///

	root = 0 ; msiz = tot = n ;
	findroot(1 , 1) ;

	cnt = 0 ; RT = NULL ;
	add(RT , 0) ; work(root) ;

	printf("%d\n" , ans) ;

	return 0 ;
}