#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAX_N = 1000 + 10 , MAX_E = 1000000 + 10 ;

struct Link {
	int num ;
	Link *next ;
}list[MAX_E] ;

Link *head[MAX_N] ;
int r , c , n , cur , left[MAX_N] ;
bool S[MAX_N] , T[MAX_N] , pS[MAX_N] , pT[MAX_N] ;

bool match(int x) {
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (T[nx]) continue ;
		
		T[nx] = 1 ;
		if (!left[nx] || match(left[nx])) {
			S[x] = 1 ; left[nx] = x ;
			return 1 ;
		}
	}

	return 0 ;
}

void find(int x) {
	pS[x] = 1 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (pT[nx]) continue ;

		pT[nx] = 1 ; find(left[nx]) ;
	}
}

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

void init() {
	cur = 0 ;
	memset(S , 0 , sizeof(S)) ;
	memset(pS , 0 , sizeof(pS)) ;
	memset(pT , 0 , sizeof(pT)) ;
	memset(head , 0 , sizeof(head)) ;
	memset(left , 0 , sizeof(left)) ;
}

int main() {
	scanf("%d %d %d" , &r , &c , &n) ;
	while (r != 0 || c != 0 || n != 0) {
		init() ;
		
		for (int i = 0 ; i < n ; ++i) {
			int x , y ;
			scanf("%d %d" , &x , &y) ;
			ins(x , y) ;
		}

		///
		
		int res = 0 ;
		for (int i = 1 ; i <= r ; ++i) {
			for (int j = 1 ; j <= c ; ++j) T[j] = 0 ;

			if (match(i)) ++res ;
		}
		
		///
		
		for (int i = 1 ; i <= r ; ++i)
			if (!S[i]) find(i) ;

		printf("%d " , res) ;
		for (int i = 1 ; i <= r ; ++i)
			if (!pS[i]) printf("r%d " , i) ;
		for (int i = 1 ; i <= c ; ++i)
			if (pT[i]) printf("c%d " , i) ;
		printf("\n") ;

		scanf("%d %d %d" , &r , &c , &n) ;
	}

	return 0 ;
}
