#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 5e4 + 10 ;

struct data {
	long long w , h ;
}t[MAX_N] ;
struct Queue {
	long long x , y ;
}q[MAX_N] ;

int L , R , n ;
long long f[MAX_N] ;

double GetK(long long a , long long b) {return a * 1.0 / b ;}

void pop(long long h) {
	while (L < R && GetK(q[L].y - q[L + 1].y ,q[L].x - q[L + 1].x) >= -h) ++L ;
}

void ins(int x) {
	while (L < R && GetK(f[x - 1] - q[R].y , t[x].w - q[R].x) > GetK(q[R].y - q[R - 1].y , q[R].x - q[R - 1].x)) --R ;

	if (x > 0) q[++R] = (Queue){t[x].w , f[x - 1]} ;
	else q[++R] = (Queue){t[x].w , 0} ;
}

bool cmp(data a , data b) {
	return a.w > b.w || (a.w == b.w && a.h > b.h) ;
}

int main() {
	scanf("%d" , &n) ;
	for (int i = 0 ; i < n ; ++i)
		scanf("%lld %lld" , &t[i].w , &t[i].h) ;

	///

	std::sort(t + 0 , t + n , cmp) ;
	int sum = 1 ;
	for (int i = 1 ; i < n ; ++i) {
		if (t[i].h <= t[sum - 1].h) continue ;
		t[sum++] = t[i] ;
	}
	n = sum ;

	///
	
	L = 0 ; R = -1 ;
	for (int i = 0 ; i < n ; ++i) {
		ins(i) ; pop(t[i].h) ;

		f[i] = q[L].y + q[L].x * t[i].h ;
	}

	printf("%lld\n" , f[n - 1]) ;

	return 0 ;
}
