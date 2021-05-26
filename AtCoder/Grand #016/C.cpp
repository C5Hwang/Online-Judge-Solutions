#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int N = 1e9 ;

ll x , y ;
int h , w , H , W ;

int main() {
	scanf("%d %d %d %d" , &H , &W , &h , &w) ;
	if (h * w == 1) {printf("No\n") ; return 0 ;}

	x = (N - 1) / (h * w - 1) ; y = (h * w - 1) * x + 1 ;
	ll c = (H / h) * (W / w) , s1 = (H * W - c) * x , s2 = c * y ;

	if (s1 > s2) {
		printf("Yes\n") ;

		for (int i = 1 ; i <= H ; ++i , printf("\n"))
			for (int j = 1 ; j <= W ; ++j)
				if (!(i % h) && !(j % w)) printf("%lld " , -y) ;
				else printf("%lld " , x) ;
	}
	else printf("No\n") ;

	return 0 ;
}