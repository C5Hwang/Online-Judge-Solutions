#include <stdio.h>
#include <stdlib.h>

int n , k , res ;

void dfs(int x) {
	int left = x - k ;
	if (left <= 0 || left % 2) {++res ; return ;}

	dfs(left / 2) ; dfs(left / 2 + k) ;
}

int main() {
	res = 0 ;
	scanf("%d %d" , &n , &k) ;
	dfs(n) ;
	printf("%d\n" , res) ;

	return 0 ;
}
