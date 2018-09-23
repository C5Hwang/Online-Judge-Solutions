#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 1000 + 10 ;

struct work {
	int ti , dl ;
}t[MAX_N] ;

int n ;

bool cmp(work x , work y) {
	return x.dl < y.dl ;
}

bool check(int x) {
	for (int i = 0 ; i < n ; ++i) {
		x += t[i].ti ;
		if (x > t[i].dl) return 0 ;
	}

	return 1 ;
}

int main() {
	int L = -1 , R = 0 ;
	scanf("%d" , &n) ;
	for (int i = 0 ; i < n ; ++i)
		scanf("%d %d" , &t[i].ti , &t[i].dl) , R = std::max(R , t[i].dl) ;

	///
	
	std::sort(t + 0 , t + n , cmp) ;
	while (L + 1 < R) {
		int mid = (L + R) >> 1 ;

		if (check(mid)) L = mid ;
		else R = mid ;
	}
	printf("%d\n" , L) ;

	return 0 ;
}
