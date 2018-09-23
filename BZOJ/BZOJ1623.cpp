#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
 
const int MAX_N = 5e4 + 10 ;
 
int n , m , d , l , s[MAX_N] ;
 
int main() {
    scanf("%d %d %d %d" , &n , &m , &d , &l) ;
    for (int i = 0 ; i < n ; ++i) scanf("%d" , &s[i]) ;
     
    ///
     
    std::sort(s + 0 , s + n) ;
 
    int k = 0 , sum = 0 , res = 0 ;
    for (int i = 0 ; i < n ; ++i) {
        int v = s[i] - k * d ;
        if (v < l) continue ;
 
        ++sum ; ++res ;
        if (sum >= m) {++k ; sum = 0 ;}
    }
    printf("%d\n" , res) ;
 
    return 0 ;
}
