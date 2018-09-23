#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std ;

const int MAX_N = 100 + 10 , MAX_M = 10000 + 10 , INF = 0x3f3f3f3f ;

struct Link {
	int num , val ;
	Link *next ;
}list[2 * MAX_M] ;

bool ap[MAX_N] ;
Link *head[MAX_N] ;
int n , m , cur , dis[MAX_N] , queue[2 * MAX_N] ;

void SPFA() {
	int L = 0 , R = 1 ; queue[1] = 1 ;
	dis[1] = 0 ; ap[1] = 1 ;
	
	while (L < R) {
		int x = queue[++L % MAX_N] ; ap[x] = 0 ;
		
		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ;
			
			if (dis[nx] > dis[x] + h->val) {
				dis[nx] = dis[x] + h->val ;
				if (!ap[nx]) queue[++R % MAX_N] = nx , ap[nx] = 1 ;
			}
		}
	}
}

void ins(int x , int y , int v) {
	list[cur].num = y ;
	list[cur].val = v ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

void init() {
	cur = 0 ;
	memset(head , 0 , sizeof(head)) ;
	
	for (int i = 0 ; i < MAX_N ; ++i)
		dis[i] = INF ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	while (n != 0 || m != 0) {
		init() ;
		
		for (int i = 0 ; i < m ; ++i) {
			int x , y , v ;
			scanf("%d %d %d" , &x , &y , &v) ;
			ins(x , y , v) ; ins(y , x , v) ;
		}
		
		SPFA() ;
		
		printf("%d\n" , dis[n]) ;
		scanf("%d %d" , &n , &m) ;
	}
	
	return 0 ;
}
