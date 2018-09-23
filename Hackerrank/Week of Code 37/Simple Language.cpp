#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 2e5 + 10 ;

struct oper {
	bool ty ; ll num ;
}list[MAX_N] ;

int n ;
char t[10] ;
ll ans , sum ;

int main() {
	ans = sum = 0 ;
	scanf("%d" , &n) ;
	for (int i = 0 ; i < n ; ++i) {
		int a ; scanf("%s %d" , t , &a) ;

		if (t[0] == 'a') list[i].ty = 0 ;
		else list[i].ty = 1 ;

		list[i].num = (ll)a ;
	}

	///

	for (int i = n - 1 ; i >= 0 ; --i) {
		oper *p = &list[i] ;
		if (p->ty) ans = std::max(p->num + sum , ans) ;
		else if (p->num >= 0) sum += p->num ;
	}

	ans = std::max(ans , sum) ;

	printf("%lld\n" , ans) ;

	return 0 ;
}