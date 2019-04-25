#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
 
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;
 
const int MAX_N = 1e5 + 10 , MAX_Q = 5e5 + 10 , MAX_M = 42e5 + 10 , lgN = 20 + 5 ;
 
struct Link {
    int num ;
    Link *next ;
}list[MAX_N << 1] ;
struct data {
    int op , x , y , idx ; //op1:add & op2:query+ & op3:query-
}qry[MAX_M] ;
 
Link *head[MAX_N] ;
int n , m , q , ti , dep[MAX_N] , dfn[MAX_N] , ed[MAX_N] ;
int cur , tot , px[MAX_N] , py[MAX_N] , ans[MAX_Q] , BIT[MAX_N] , f[MAX_N][lgN] ;
 
inline int read() {
    char c = getchar() ;
    int num = 0 , f = 1 ;
 
    for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
    for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;
 
    return num * f ;
}
 
void ins(int x , int y) {
    list[cur].num = y ;
    list[cur].next = head[x] ;
    head[x] = &list[cur++] ;
}
 
void dfs(int x) {
    dfn[x] = ++ti ;
    for (Link *h = head[x] ; h ; h = h->next) {
        int nx = h->num ;
        if (nx == f[x][0]) continue ;
 
        f[nx][0] = x ; dep[nx] = dep[x] + 1 ;
        dfs(nx) ;
    }
    ed[x] = ti ;
}
 
int lca(int x , int y , int ty) {
    if (dep[x] < dep[y]) std::swap(x , y) ;
 
    for (int i = 20 ; i >= 0 ; --i) {
        if ((1 << i) > n) continue ;
        if (dep[f[x][i]] > dep[y]) x = f[x][i] ;
    }
 
    if (ty) return x ;
    else x = f[x][0] ;
 
    if (x == y) return x ;
    for (int i = 20 ; i >= 0 ; --i) {
        if ((1 >> i) > n) continue ;
        int tx = f[x][i] , ty = f[y][i] ;
        if (tx != ty) x = tx , y = ty ;
    }
 
    return f[x][0] ;
}
 
void addquery(int x , int y , int a , int pl) {
    int px = dfn[x] , py = dfn[y] , qx = ed[x] , qy = ed[y] ;
 
    qry[tot++] = (data){a > 0 ? 2 : 3 , qx , qy , pl} ;
    if (px > 1) qry[tot++] = (data){a > 0 ? 3 : 2 , px - 1 , qy , pl} ;
    if (py > 1) qry[tot++] = (data){a > 0 ? 3 : 2 , qx , py - 1 , pl} ;
    if (px > 1 && py > 1) qry[tot++] = (data){a > 0 ? 2 : 3 , px - 1 , py - 1 , pl} ;
}
 
bool cmp(data a , data b) {
    return a.x < b.x || (a.x == b.x && a.op < b.op) ;
}
 
inline int lowbit(int x) {return x & (-x) ;}
 
void add(int p) {
    for (; p <= n ; p += lowbit(p)) ++BIT[p] ;
}
 
int find(int p) {
    int s = 0 ;
    for (; p ; p -= lowbit(p)) s += BIT[p] ;
 
    return s ;
}
 
int main() {
    n = read() ;
    for (int i = 1 ; i < n ; ++i) {
        int x , y ;
        x = read() ; y = read() ;
 
        ins(x , y) ; ins(y , x) ;
    }
    m = read() ;
    for (int i = 0 ; i < m ; ++i) px[i] = read() , py[i] = read() ;
 
    ///
 
    f[1][0] = 1 ; dep[1] = 1 ;
    dfs(1) ;
 
    for (int j = 1 ; (1 << j) <= n ; ++j)
        for (int i = 1 ; i <= n ; ++i) f[i][j] = f[f[i][j - 1]][j - 1] ;
 
    for (int i = 0 ; i < m ; ++i) {
        qry[tot++] = (data){1 , dfn[px[i]] , dfn[py[i]] , 0} ;
        qry[tot++] = (data){1 , dfn[py[i]] , dfn[px[i]] , 0} ;
    }
    q = read() ;
    for (int i = 0 ; i < q ; ++i) {
        int x , y , d ;
        x = read() ; y = read() ; d = lca(x , y , 0) ;
 
        if (dep[x] > dep[y]) std::swap(x , y) ;
        if (d == x) {
            d = lca(x , y , 1) ;
            addquery(1 , y , 1 , i) ;
            addquery(d , y , -1 , i) ;
        }
        else addquery(x , y , 1 , i) ;
    }
 
    ///
 
    std::sort(qry + 0 , qry + tot , cmp) ;
    for (int i = 0 ; i < tot ; ++i) {
        data *p = &qry[i] ;
 
        if (p->op == 1) add(p->y) ;
        else if (p->op == 2) ans[p->idx] += find(p->y) ;
        else ans[p->idx] -= find(p->y) ;
    }
 
    for (int i = 0 ; i < q ; ++i) printf("%d\n" , ans[i] + 1) ;
 
    return 0 ;
}