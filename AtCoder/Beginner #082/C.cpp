#include <map>
#include <stdio.h>
#include <stdlib.h>

const int MAX_N = 1e5 + 10 ;

std::map<int , int> cnt ;
std::map<int , bool> ap ;

int n , a[MAX_N] ;

int main() {
	scanf("%d" , &n) ;
	for (int i = 0 ; i < n ; ++i) {
		scanf("%d" , &a[i]) ;
		++cnt[a[i]] ;
	}

	///

	int ans = 0 ;
	for (int i = 0 ; i < n ; ++i) {
		if (ap[a[i]]) continue ;
		ap[a[i]] = 1 ;

		int tmp = cnt[a[i]] ;
		if (tmp >= a[i]) ans += tmp - a[i] ;
		else ans += tmp ;
	}

	printf("%d\n" , ans) ;

	return 0 ;
}