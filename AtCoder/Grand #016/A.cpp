#include <vector>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 100 + 10 , MAX_M = 'z' + 10 ;

std::vector<int> pl[MAX_M] ;

int n , ans ;
char s[MAX_N] ;

void work(int x) {
	int m = pl[x].size() , ma = 0 ;

	for (int i = 1 ; i < m ; ++i) {
		ma = std::max(ma , pl[x][i] - pl[x][i - 1] - 1) ;
		ans = std::min(ans , std::max(ma , n - pl[x][i])) ;
	}
}

int main() {
	scanf("%s" , s) ;
	n = strlen(s) ;

	///

	ans = n + 1 ;
	for (int i = 'a' ; i <= 'z' ; ++i) pl[i].push_back(0) ;
	for (int i = 0 ; i < n ; ++i) pl[s[i]].push_back(i + 1) ;

	for (int i = 'a' ; i <= 'z' ; ++i) work(i) ;

	printf("%d\n" , ans) ;

	return 0 ;
}