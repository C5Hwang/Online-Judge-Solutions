#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std ;

#define eps 1e-7
#define MAX_N 1000 + 10

int n , k ;
double a[MAX_N] , b[MAX_N] , sc[MAX_N] ;

bool check(double ans) {
	for (int i = 0 ; i < n ; ++i)
		sc[i] = a[i] - b[i] * ans ;
	
	sort(sc + 0 , sc + n) ;
	
	double sum = 0 ;
	for (int i = k ; i < n ; ++i)
		sum += sc[i] ;
	
	return sum < 0 ;
}

int main() {
	scanf("%d %d" , &n , &k) ;
	while (n != 0 || k != 0) {
		for (int i = 0 ; i < n ; ++i)
			scanf("%lf" , &a[i]) ;
		for (int i = 0 ; i < n ; ++i)
			scanf("%lf" , &b[i]) ;
		
		///
		
		double L = 0.0 , R = 1.0 ;
		while (R - L > eps) {
			double mid = (L + R) / 2.0 ;
			if (check(mid)) R = mid ;
			else L = mid ;
		}
		
		printf("%.0f\n" , L * 100) ;
		
		scanf("%d %d" , &n , &k) ;
	}
	
	return 0 ;
}
