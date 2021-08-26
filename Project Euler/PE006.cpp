#include <bits/stdc++.h>

int N = 100 ;

int main() {
	int s1 = N * (N + 1) * (2 * N + 1) / 6 , s2 = N * (N + 1) / 2 ;
	s2 *= s2 ;

	printf("%d\n" , abs(s1 - s2)) ;

	return 0 ;
}