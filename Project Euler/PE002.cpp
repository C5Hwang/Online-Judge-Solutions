#include <bits/stdc++.h>

const int INF = 4e6 ;

int p1 , p2 , res ;

int main() {
	p1 = 1 ; p2 = 2 ; res = 2 ;
	for (; ;) {
		int nw = p1 + p2 ;
		if (nw > INF) break ;

		if (!(nw & 1)) res += nw ;
		p1 = p2 ; p2 = nw ;
	}

	printf("%d\n" , res) ;

	return 0 ;
}