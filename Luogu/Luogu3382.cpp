#include <stdio.h>
#include <stdlib.h>

const int MAX_N = 13 + 10 ;

int n ;
double a[MAX_N] , L , R ;

double getf(double x) {
	double sum = 0 , t = 1 ;
	for (int i = n ; i >= 0 ; --i , t *= x)
		sum += a[i] * t ;

	return sum ;
}

int main() {
	scanf("%d %lf %lf" , &n , &L , &R) ;
	for (int i = 0 ; i <= n ; ++i) scanf("%lf" , &a[i]) ;

	for (int i = 0 ; i < 200 ; ++i) {
		double len = (R - L) / 3.0 , nl = L + len , nr = R - len ;
		double fl = getf(nl) , fr = getf(nr) ;

		if (fl > fr) R = nr ;
		else L = nl ;
	}
	if (getf(L) > getf(R)) printf("%0.5lf\n" , L) ;
	else printf("%0.5lf\n" , R) ;

	return 0 ;
}
