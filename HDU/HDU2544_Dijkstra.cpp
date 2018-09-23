#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std ;

const int MAX_N = 100 + 10 , MAX_M = 100000 + 10 , INF = 0x3f3f3f3f ;

struct Link {
	int num , val ;
	Link *next ;
}list[MAX_M * 2] ;

bool ap[MAX_N] ;
Link *head[MAX_N] ;
int n , m , cur , dis[MAX_N] ;

void Dij() {
	for (int i = 0 ; i < n ; ++i) {
		int mdis = INF , mp = -1 ;
		for (int j = 1 ; j <= n ; ++j)
			if (mdis > dis[j] && !ap[j]) mdis = dis[j] , mp = j ;

		for (Link *h = head[mp] ; h ; h = h->next) {
			int np = h->num ;
			dis[np] = min(dis[mp] + h->val , dis[np]) ;
		}

		ap[mp] = 1 ;
	}
}

void ins(int x , int y , int v) {
	list[cur].val = v ;
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

void init() {
	cur = 0 ;
	memset(ap , 0 , sizeof(ap)) ;
	memset(head , 0 , sizeof(head)) ;

	for (int i = 0 ; i < MAX_N ; ++i)
		dis[i] = INF ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	while (n != 0 || m != 0) {
		init() ;
		for (int i = 0 ; i < m ; ++i) {
			int a , b , v ;
			scanf("%d %d %d" , &a , &b , &v) ;

			ins(a , b , v) ; ins(b , a , v) ;
		}

		///

		dis[1] = 0 ; Dij() ;
		
		printf("%d\n" , dis[n]) ;

		scanf("%d %d" , &n , &m) ;
	}

	return 0 ;
}
