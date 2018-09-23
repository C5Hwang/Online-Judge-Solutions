#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
 
const int MAX_N = 1e4 + 10 ;
 
int cur , tot ;
long long x , y , ans , a[MAX_N] , b[MAX_N] ;

void find(long long num) {
    if (num > y) return ;
    if (num) a[cur++] = num ;
 
    find(num * 10 + 6) ;
    find(num * 10 + 8) ;
}
 
long long gcd(long long a , long long b) {
    return b ? gcd(b , a % b) : a ;
}
 
void GetAns(int n , int num , long long sum) {
    if (n == tot) {
		if (num & 1) ans += y / sum - (x - 1) / sum ;
		else if (num) ans -= y / sum - (x - 1) / sum ;

		return ;
    }
 
    GetAns(n + 1 , num , sum) ;

	long long temp = sum / gcd(sum , b[n]) ;
    if ((double)temp * b[n] <= y) GetAns(n + 1 , num + 1 , temp * b[n]) ;
}
 
bool cmp(long long x , long long y) {
    return x > y ;
}
 
int main() {
    scanf("%lld %lld" , &x , &y) ;
    find(0) ;
 
    std::sort(a + 0 , a + cur) ;
    for (int i = 0 ; i < cur ; ++i) {
        bool ok = 1 ;
        for (int j = 0 ; j < i && ok ; ++j)
            if (!(a[i] % a[j])) ok = 0 ;
        if (ok) b[tot++] = a[i] ;
    }
    std::sort(b + 0 , b + tot , cmp) ;
 
    ///
    
	GetAns(0 , 0 , 1) ;	
    printf("%lld\n" , ans) ;
 
    return 0 ;
}
