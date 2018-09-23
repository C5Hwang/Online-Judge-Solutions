#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 1e5 + 10 ;

struct Link {
	int num ;
	Link *next ;
}list[MAX_N] ;
struct data {
	int num , idx ;
}a[MAX_N] ;

Link *head[MAX_N] ;
int n , cur , BIT[MAX_N] , ans[MAX_N] ;

///

bool cmp1(data x , data y) {return x.num < y.num ;}

bool cmp2(data x , data y) {return x.idx < y.idx ;}

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

///

int lowbit(int x) {return x & (-x) ;}

void add(int x) {
	for (; x <= n ; x += lowbit(x)) ++BIT[x] ;
}

int sum(int x) {
	int s = 0 ;
	for (; x > 0 ; x -= lowbit(x)) s += BIT[x] ;
	return s ;
}

///

void dfs(int x) {
	int s1 = sum(n) - sum(a[x].num) , s2 ;
	add(a[x].num) ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		dfs(nx) ;
	}

	s2 = sum(n) - sum(a[x].num) ;
	ans[x] = s2 - s1 ;
}

///

int main() {
	scanf("%d" , &n) ;
	for (int i = 1 ; i <= n ; ++i) {
		scanf("%d" , &a[i].num) ;
		a[i].idx = i ;
	}
	for (int i = 2 ; i <= n ; ++i) {
		int x ; scanf("%d" , &x) ;
		ins(x , i) ;
	}

	///
	
	std::sort(a + 1 , a + 1 + n , cmp1) ;
	int last = a[1].num , tot = 1 ; a[1].num = 1 ;
	for (int i = 2 ; i <= n ; ++i)
		if (last == a[i].num) a[i].num = tot ;
		else {
			last = a[i].num ;
			a[i].num = ++tot ;
		}
	std::sort(a + 1 , a + 1 + n , cmp2) ;

	///
	
	dfs(1) ;
	for (int i = 1 ; i <= n ; ++i)
		printf("%d\n" , ans[i]) ;

	return 0 ;
}
