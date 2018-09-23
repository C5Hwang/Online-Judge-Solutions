#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 1e3 + 10 , MAX_E = 1e4 + 10 ;

struct Link {
	int num , val ;
	Link *next ;
}list[2 * MAX_E] ;

bool ap[MAX_N] ;
Link *head[MAX_N] ;
int n , m , k , cur , dis[MAX_N] , queue[MAX_N] ;

bool check(int mf) {
	int L = 0 , R = 1 ;

	memset(ap , 0 , sizeof(ap)) ;
	memset(dis , -1 , sizeof(dis)) ;
	queue[1] = 1 ; ap[1] = 1 ; dis[1] = 0 ;

	while (L < R) {
		int x = queue[(++L) % n] ; ap[x] = 0 ;

		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num , nd = dis[x] + (h->val > mf ? 1 : 0) ;

			if (dis[nx] != -1 && dis[nx] <= nd) continue ;
			if (ap[nx]) {dis[nx] = std::min(dis[nx] , nd) ; continue ;}

			queue[(++R) % n] = nx ;
			dis[nx] = nd ; ap[nx] = 1 ;
		}
	}

	return dis[n] != -1 && dis[n] <= k ;
}

void ins(int x , int y , int l) {
	list[cur].num = y ;
	list[cur].val = l ;
	list[cur].next = head[x] ;

	head[x] = &list[cur++] ;
}

int main() {
	int maxL = 0 ;

	scanf("%d %d %d" , &n , &m , &k) ;
	for (int i = 0 ; i < m ; ++i) {
		int x , y , l ;
		scanf("%d %d %d" , &x , &y , &l) ;

		ins(x , y , l) ; ins(y , x , l) ; maxL = std::max(maxL , l) ;
	}

	///
	
	++maxL ;
	int L = -1 , R = maxL ;
	while (L + 1 < R) {
		int mid = (L + R) >> 1 ;

		if (check(mid)) R = mid ;
		else L = mid ;
	}

	if (R == maxL) printf("-1\n") ;
	else printf("%d\n" , R) ;

	return 0 ;
}
