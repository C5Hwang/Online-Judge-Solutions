#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 30000 + 10 , MAX_M = 150000 + 10 , INF = 1e8 ;

struct Link {
	int num , v ; Link *next ;
}list[MAX_M] ;
struct Heap {
	int num , d ;
}hep[MAX_M] ;

bool ap[MAX_N] ;
Link *head[MAX_N] ;
int n , m , tot , cur , dis[MAX_N] ;

///

void exchange(int &x , int &y) {
	std::swap(hep[x] , hep[y]) ;
	std::swap(x , y) ;
}

void up(int &p) {
	int fa ;
	while ((fa = p / 2) > 0 && hep[fa].d > hep[p].d) exchange(fa , p) ;
}

void push(int f , int a) {
	int p = ++tot ;
	hep[p].num = f ; hep[p].d = a ;
	up(p) ;
}

int GetMinSon(int p) {
	int lson = p * 2 , rson = p * 2 + 1 ;
	if (rson > tot) return lson ;

	if (hep[lson].d > hep[rson].d) return rson ;
	else return lson ;
}

void pop() {
	hep[1] = hep[tot--] ;
	int p = 1 ;
	while(p * 2 <= tot) {
		int sp = GetMinSon(p) ;

		if (hep[sp].d < hep[p].d) exchange(sp , p) ;
		else break ;
	}
}

///

void ins(int x , int y , int c) {
	list[cur].v = c ;
	list[cur].num = y ;
	list[cur].next = head[x] ;

	head[x] = &list[cur++] ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 0 ; i < m ; ++i) {
		int x , y , c ;
		scanf("%d %d %d" , &x , &y , &c) ;
		ins(x , y , c) ;
	}

	///
	
	dis[1] = 0 ; push(1 , 0) ;
	for (int i = 2 ; i <= n ; ++i) dis[i] = INF , push(i , dis[i]) ;

	///

	while (tot) {
		int x = hep[1].num ;
		pop() ;

		if (ap[x]) continue ;

		ap[x] = 1 ;
		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ;
			if (ap[nx]) continue ;

			if (dis[nx] > dis[x] + h->v) {dis[nx] = dis[x] + h->v ; push(nx , dis[nx]) ;}
		}
	}

	printf("%d\n" , dis[n]) ;

	return 0 ;
}
