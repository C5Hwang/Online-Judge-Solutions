#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 2e6 + 10 ;

struct Link {
	int num ;
	Link *next ;
}list[MAX_N] ;

Link *head[MAX_N] ;
int n , m , res , sum , cur , f[MAX_N] , queue[MAX_N] ; ;

void dfs(int x) {
	for (Link *h = head[x] ; h ; h = h->next) dfs(h->num) ;
	sum = 0 ;
	for (Link *h = head[x] ; h ; h = h->next) queue[sum++] = f[h->num] ;
	std::sort(queue + 0 , queue + sum) ;

	for (int i = 0 ; i < sum ; ++i)
		if (queue[i] + f[x] - 1 <= m) f[x] += queue[i] - 1 , ++res ;
		else break ;
}

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 0 ; i < n ; ++i) scanf("%d" , &f[i]) ;
	for (int i = 0 ; i < n ; ++i) {
		int t , a ;
		scanf("%d" , &t) ; f[i] += t ;
		for (int j = 0 ; j < t ; ++j) {
			scanf("%d" , &a) ;
			ins(i , a) ;
		}
	}

	///
	
	dfs(0) ;

	printf("%d\n" , res) ;

	return 0 ;
}
