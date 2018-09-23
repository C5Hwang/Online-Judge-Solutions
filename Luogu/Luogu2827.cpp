#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long

const int MAX_N = 1e5 + 10 , MAX_L = 8e6 + 10 , INF = 0x7FFFFFFF ;

struct data {
    int num , idx ;
} ;

ll q , u , v , ans[MAX_L] ;
int n , m , t , cnt , L[3] , R[3] , queue[3][MAX_L] ;

bool cmp(ll x , ll y) {return x > y ;}

int getmax() {
    data a[3] ;
    for (int i = 0 ; i < 3 ; ++i) a[i] = (data){L[i] <= R[i] ? queue[i][L[i]] : -INF , i} ;
    if (a[0].num < a[1].num) std::swap(a[0] , a[1]) ;
    if (a[0].num < a[2].num) std::swap(a[0] , a[2]) ;

    return a[0].idx ;
}

inline int read() {
    int n = 0 , f = 1 ;
    char c = getchar() ;

    while (c < '0' || c > '9') {if (c == '-') f = -f ; c = getchar() ;}
    while (c >= '0' && c <= '9') {n = n * 10 + c - '0' ; c = getchar() ;}

    return n * f ;
}

int main() {
    n = read() ; m = read() ; q = read() ; u = read() ; v = read() ; t = read() ;
    for (int i = 0 ; i < n ; ++i) queue[0][i] = read() ;
    std::sort(queue[0] + 0 , queue[0] + n , cmp) ;
    L[0] = L[1] = L[2] = 0 ;
    R[0] = n - 1 ; R[1] = R[2] = -1 ;

    ///
    
    for (int i = 0 ; i < m ; ++i) {
        int p = getmax() ;
        ll x = queue[p][L[p]++] + q * i , x1 = x * u / v , x2 = x - x1 ;
        if (x1 > x2) std::swap(x1 , x2) ;

        x1 -= q * (i + 1) ; x2 -= q * (i + 1) ;
        queue[1][++R[1]] = x1 ; queue[2][++R[2]] = x2 ;

        if (!((i + 1) % t)) {
            printf("%lld" , x) ;
            if (i + 1 + t <= m) printf(" ") ;
        }
    }
    printf("\n") ;

    ///

    while (L[0] <= R[0] || L[1] <= R[1] || L[2] <= R[2]) {
        int p = getmax() ;
        ans[cnt++] = queue[p][L[p]++] + m * q ;
    }
    for (int i = 0 ; i < cnt ; ++i)
        if (!((i + 1) % t)) {
            printf("%lld" , ans[i]) ;
            if (i + t + 1 <= cnt) printf(" ") ;
        }

    return 0 ;
}
