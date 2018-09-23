#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

const double eps = 1e-6 ;
const int MAX_N = 18 + 10 , MAX_S = (1 << 18) + 10 ;

struct data {double x , y ;}pg[MAX_N] ;

int T , n , m , st[MAX_N][MAX_N] , f[MAX_S] ;

void init() {
	memset(f , 0 , sizeof(f)) ;
	memset(st , 0 , sizeof(st)) ;
}

int main() {
	scanf("%d" , &T) ;
	while (T--) {
		init() ;

		scanf("%d %d" , &n , &m) ;
		for (int i = 0 ; i < n ; ++i)
			scanf("%lf %lf" , &pg[i].x , &pg[i].y) ;

		for (int i = 0 ; i < n ; ++i)
			for (int j = 0 ; j < n ; ++j) {
				if (i == j) {st[i][j] = (1 << i) ; continue ;}
				data *p = &pg[i] , *q = &pg[j] ;

				if (p->x == q->x) continue ;
				double a = p->y / (p->x * p->x - p->x * q->x) - q->y / (p->x * q->x - q->x * q->x) ,
					   b = (p->y * q->x) / (p->x * q->x - p->x * p->x) - (q->y * p->x) / (q->x * q->x - p->x * q->x) ;

				if (a > 0 || fabs(a) <= eps) continue ;

				int s = 0 ;
				for (int k = 0 ; k < n ; ++k) {
					data *t = &pg[k] ;
					double ny = t->x * t->x * a + t->x * b ;
					if (fabs(ny - t->y) <= eps) s |= (1 << k) ;
				}

				st[i][j] = s ;
			}

		///

		int ts = (1 << n) - 1 ; f[0] = 0 ;
		for (int S = 1 ; S <= ts ; ++S) {
			int tot = 0 , fp = -1 ;
			for (int i = 0 ; i < n ; ++i)
				if ((1 << i) & S) {
					++tot ;
					if (fp < 0) fp = i ;
				}

			if (tot == 1) {f[S] = 1 ; continue ;}

			int ans = n ;
			for (int i = fp ; i < n ; ++i)
				if ((1 << i) & S) {
					if (!st[fp][i]) continue ;

					int cls = st[fp][i] & S ;
					ans = std::min(ans , f[S ^ cls] + 1) ;
				}
			f[S] = ans ;
		}

		printf("%d\n" , f[ts]) ;
	}

	return 0 ;
}
