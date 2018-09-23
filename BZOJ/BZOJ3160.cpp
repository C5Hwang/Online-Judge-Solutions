#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

const double pi = acos(-1) ;
const int MAX_N = 4e5 + 10 , MOD = 1e9 + 7 ;

struct CP {
	double x , y ;

	friend CP operator +(CP a , CP b) {return (CP){a.x + b.x , a.y + b.y} ;}
	friend CP operator -(CP a , CP b) {return (CP){a.x - b.x , a.y - b.y} ;}
	friend CP operator *(CP a , CP b) {return (CP){a.x * b.x - a.y * b.y , a.x * b.y + a.y * b.x} ;}
} ;

CP f[MAX_N] , g[MAX_N] ;
char st[MAX_N] , ms[MAX_N] ;
int n , m , len , ans , rev[MAX_N] , pw[MAX_N] , cir[MAX_N] ;

void fft(CP *a , int ty) {
	for (int i = 0 ; i < n ; ++i) if (i < rev[i]) std::swap(a[i] , a[rev[i]]) ;

	for (int L = 2 ; L <= n ; L <<= 1) {
		int hf = L >> 1 ;
		CP wn = (CP){cos(2 * pi * ty / L) , sin(2 * pi * ty / L)} ;

		for (int i = 0 ; i < n ; i += L) {
			CP w = (CP){1 , 0} ;
			for (int j = 0 ; j < hf ; ++j , w = w * wn) {
				CP t = a[i + j + hf] * w ;
				a[i + j + hf] = a[i + j] - t ;
				a[i + j] = a[i + j] + t ;
			}
		}
	}
}

int main() {
	scanf("%s" , st) ;
	m = strlen(st) - 1 ; len = 0 ;
	for (int i = 0 ; i <= m ; ++i) ms[len++] = '#' , ms[len++] = st[i] ;
	ms[len++] = '#' ;

	///

	for (int i = 0 ; i <= m ; ++i)
		if (st[i] == 'a') f[i].x = 1 ;
		else g[i].x = 1 ;

	int L ; m <<= 1 ;
	for (L = 0 , n = 1 ; n <= m ; n <<= 1 , ++L) ;
	for (int i = 1 ; i < n ; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1)) ;

	pw[0] = 1 ;
	for (int i = 1 ; i <= m ; ++i) (pw[i] = pw[i - 1] << 1) %= MOD ;

	///

	int p = 1 ; cir[1] = 1 ; ans = 0 ;

	for (int i = 0 ; i < len ; ++i) {
		int u = cir[p] + p , t = std::min(cir[(p << 1) - i] , u - i) ;
		for (; i - t - 1 >= 0 && i + t + 1 < len && ms[i + t + 1] == ms[i - t - 1] ; ++t) ;
		if (i + t > u) p = i ;

		cir[i] = t ;
	}

	for (int i = 0 ; i < len ; ++i) ans = (ans + MOD - ((cir[i] + 1) >> 1)) % MOD ;

	///

	fft(f , 1) ; fft(g , 1) ;
	for (int i = 0 ; i < n ; ++i) f[i] = f[i] * f[i] , g[i] = g[i] * g[i] ;
	fft(f , -1) ; fft(g , -1) ;

	for (int i = 0 ; i <= m ; ++i) {
		int tf = (int)(f[i].x / n + 0.5) , tg = (int)(g[i].x / n + 0.5) , tmp ;
		tmp = (tf + tg + 1) >> 1 ;
		tmp = (pw[tmp] + MOD - 1) % MOD ;

		(ans += tmp) %= MOD ;
	}

	printf("%d\n" , ans) ;

	return 0 ;
}