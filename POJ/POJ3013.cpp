#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

const long long INF = 1e12 ;
const int MAX_N = 50000 + 10 ;

struct Link {
	int num ; long long v ; Link *next ;
}list[2 * MAX_N] ;
struct Heap {
	int num ; long long d ;
}hep[2 * MAX_N] ;

bool ap[MAX_N] ;
Link *head[MAX_N] ;
int n , m , tot , cur ;
long long dis[MAX_N] , v[MAX_N] ;

///

void exchange(int &x , int &y) {
	std::swap(hep[x] , hep[y]) ;
	std::swap(x , y) ;
}

void up(int p) {
	int fa ;
	while ((fa = p / 2) > 0 && hep[fa].d > hep[p].d) exchange(fa , p) ;
}

void push(int f , long long a) {
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

void ins(int x , int y , long long c) {
	list[cur].v = c ;
	list[cur].num = y ;
	list[cur].next = head[x] ;

	head[x] = &list[cur++] ;
}

void init() {
	cur = tot = 0 ;
	memset(ap , 0 , sizeof(ap)) ;
	memset(head , 0 , sizeof(head)) ;
}

int main() {
	int T ; scanf("%d" , &T) ;
	while (T--) {
		init() ;

		scanf("%d %d" , &n , &m) ;
		for (int i = 1 ; i <= n ; ++i) scanf("%lld" , &v[i]) ;
		for (int i = 0 ; i < m ; ++i) {
			int x , y ; long long c ;
			scanf("%d %d %lld" , &x , &y , &c) ;
			ins(x , y , c) ; ins(y , x , c) ;
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
				if (dis[nx] > dis[x] + h->v) {dis[nx] = dis[x] + h->v ; push(nx , dis[nx]) ;}
			}
		}

		///
	
		bool ans = 1 ;
		long long res = 0 ;
		for (int i = 1 ; i <= n ; ++i) {
			if (dis[i] == INF) {ans = 0 ; break ;}
			res += dis[i] * v[i] ;
		}

		if (ans) printf("%lld\n" , res) ;
		else printf("No Answer\n") ;
	}

	return 0 ;
}
