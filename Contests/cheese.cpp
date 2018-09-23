#include <queue>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long

const int MAX_N = 1e3 + 10 , MAX_M = 2e6 + 10 ;

struct data {
	ll x , y , z ;
}a[MAX_N] ;
struct Link {
	int num ;
	Link *next ;
}list[MAX_M] ;

std::queue<int> que ;

ll r , h ;
bool ap[MAX_N] ;
Link *head[MAX_N] ;
int n , Q , cur , S , T ;

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

ll sq(ll x) {return x * x ;}

bool check(int x , int y) {
	data *p = &a[x] , *q = &a[y] ;
	
	ll left = sq(p->x - q->x) + sq(p->y - q->y) , right = sq(r << 1) - sq(p->z - q->z) ;

	if (left <= right) return 1 ;
	else return 0 ;
}

void init() {
	cur = 0 ;
	memset(ap , 0 , sizeof(ap)) ;
	memset(head , 0 , sizeof(head)) ;
}

int main() {
	freopen("cheese.in" , "r" , stdin) ;
	freopen("cheese.out" , "w" , stdout) ;
	
	scanf("%d" , &Q) ;
	while (Q--) {
		init() ;
		
		scanf("%d %lld %lld" , &n , &h , &r) ;
		for (int i = 1 ; i <= n ; ++i)
			scanf("%lld %lld %lld" , &a[i].x , &a[i].y , &a[i].z) ;
		
		///
		
		S = 0 ; T = n + 1 ;
		for (int i = 1 ; i <= n ; ++i) {
			data *p = &a[i] ;
			if (p->z - r <= 0) ins(S , i) , ins(i , S) ;
			if (p->z + r >= h) ins(T , i) , ins(i , T) ;
		}
		for (int i = 1 ; i <= n ; ++i)
			for (int j = 1 ; j <= n ; ++j) {
				if (i == j) continue ;
				
				if (check(i , j)) ins(i , j) ;
			}
		
		///
		
		que.push(S) ; ap[S] = 1 ;
		for (; !que.empty() ;) {
			int x = que.front() ; que.pop() ;
			for (Link *h = head[x] ; h ; h = h->next) {
				int nx = h->num ;
				if (ap[nx]) continue ;
				ap[nx] = 1 ; que.push(nx) ;
			}
		}
		
		if (ap[T]) printf("Yes\n") ;
		else printf("No\n") ;
	}
	
	fclose(stdin) ; fclose(stdout) ;
	
	return 0 ;
}
