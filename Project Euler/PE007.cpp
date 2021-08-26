#include <bits/stdc++.h>

const int N = 1e6 , MAX_N = N + 10 ;

bool ap[MAX_N] ;

int main() {
	for (int i = 2 ; i <= N ; ++i)
		if (!ap[i]) for (int j = i + i ; j <= N ; j += i) ap[j] = 1 ;

	int cnt = 10001 , r ;
	for (r = 2 ; r <= N ; ++r)
		if (!ap[r]) {if (!(--cnt)) break ;}
	printf("%d\n" , r) ;

	return 0 ;
}