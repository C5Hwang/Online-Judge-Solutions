#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int INF = 0x7FFFFFFF ;

struct data {
	int a , b , c ;
	void init() {
		if (a > b) std::swap(a , b) ;
		if (a > c) std::swap(a , c) ;
		if (b > c) std::swap(b , c) ;
	}
}p , q ;

int len , dep1 , dep2 ;

data jump(data x , int stp) {
	len = 0 ;
	for (; stp > 0 ;) {
		int l1 = x.b - x.a , l2 = x.c - x.b ;
		if (l1 == l2) return x ;

		int t ;
		if (l1 > l2) {
			t = std::min((l1 - 1) / l2 , stp) ;
			x.b -= t * l2 ; x.c -= t * l2 ;
		}
		else {
			t = std::min((l2 - 1) / l1 , stp) ;
			x.b += t * l1 ; x.a += t * l1 ;
		}

		stp -= t ; len += t ;
	}

	return x ;
}

bool equal(data x , data y) {
	return x.a == y.a && x.b == y.b && x.c == y.c ;
}

int main() {
	scanf("%d %d %d %d %d %d" , &p.a , &p.b , &p.c , &q.a , &q.b , &q.c) ;
	p.init() ; q.init() ;

	///

	data fp , fq ;
	fp = jump(p , INF) ; dep1 = len ;
	fq = jump(q , INF) ; dep2 = len ;
	if (!equal(fp , fq)) {
		printf("NO\n") ;

		return 0 ;
	}

	///

	printf("YES\n") ;	
	if (dep1 < dep2) std::swap(p , q) , std::swap(dep1 , dep2) ;

	int res = dep1 - dep2 ;
	p = jump(p , dep1 - dep2) ;

	if (!equal(p , q)) {
		for (int i = 31 ; i >= 0 ; --i) {
			int k = (1 << i) ;
			data tp = jump(p , k) , tq = jump(q , k) ;

			if (!equal(tp , tq)) p = tp , q = tq , res += (k << 1) ;
		}
		
		res += 2 ;
	}

	printf("%d\n" , res) ;

	return 0 ;
}
