#include <vector>
#include <stdio.h>
#include <stdlib.h>

#define db double
#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const db eps = 1e-6 ;
const int MAX_N = 1e5 + 10 ;

struct data {ll x , y ;} ;

std::vector<data>sta[MAX_N] ;

ll f[MAX_N] ;
int n , a[MAX_N] , S[MAX_N] , tot[MAX_N] , cnt[MAX_N] ;

inline ll squ(int x) {return (ll)x * x ;}

db getk(data a , data b) {
	return (a.y - b.y) * 1.0 / (a.x - b.x) ;
}

void push(int ty , data a) {
	for (; cnt[ty] > 1 && getk(sta[ty][cnt[ty]] , sta[ty][cnt[ty] - 1]) - getk(sta[ty][cnt[ty]] , a) < eps ; --cnt[ty]) ;
	sta[ty][++cnt[ty]] = a ;
}

void pop(int ty , int k) {
	for (; cnt[ty] > 1 && getk(sta[ty][cnt[ty]] , sta[ty][cnt[ty] - 1]) - k < eps ; --cnt[ty]) ;
}

int main() {
	int maxa = 0 ;
	scanf("%d" , &n) ;
	for (int i = 1 ; i <= n ; ++i) {
		scanf("%d" , &a[i]) ;
		S[i] = ++tot[a[i]] ; maxa = std::max(maxa , a[i]) ;
	}
	for (int i = 1 ; i <= maxa ; ++i) sta[i].resize(tot[i] + 1) ;

	///

	for (int i = 1 ; i <= n ; ++i) {
		int ta = a[i] ;

		push(ta , (data){((ll)ta * (S[i] - 1)) << 1 , f[i - 1] + (ll)ta * squ(S[i] - 1)}) ;
		pop(ta , S[i]) ;
		f[i] = (ll)ta * squ(S[i]) + sta[ta][cnt[ta]].y - S[i] * sta[ta][cnt[ta]].x ;
	}

	printf("%lld\n" , f[n]) ;

	return 0 ;
}