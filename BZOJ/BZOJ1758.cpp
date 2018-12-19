#include <math.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
 
#define db double
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;
 
const db eps = 1e-4 ;
const int MAX_N = 1e5 + 10 , INF = 0x3f3f3f3f ;
 
struct Link {
    db val ;
    int num , v ;
    Link *next ;
}list[MAX_N << 1] ;
struct data {
    int pl ; db x ;
}que[MAX_N] ;
 
std::vector<int> srt[MAX_N] , tre[MAX_N] ;
 
bool vis[MAX_N] ;
Link *head[MAX_N] ;
db dis[MAX_N] , tmp[MAX_N] , d[MAX_N] ;
int n , qL , qR , minE , maxE , cur , tot , root , msiz , siz[MAX_N] ;
 
///
 
inline int read() {
    char c = getchar() ;
    int num = 0 , f = 1 ;
 
    for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
    for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;
 
    return num * f ;
}
 
void ins(int x , int y , int v) {
    list[cur].num = y ;
    list[cur].v = v ;
    list[cur].next = head[x] ;
    head[x] = &list[cur++] ;
}
 
///
 
void push(int x , db d) {
    for (; qL <= qR && que[qR].x - d < eps ; --qR) ;
 
    que[++qR] = (data){x , d} ;
}
 
void pop(int x) {
    if (que[qL].pl == x) ++qL ;
}
 
bool calc(int len) {
    qL = 1 ; qR = 0 ;
    int le = minE - 1 , ri = maxE - 1 ;
    for (int i = std::min(ri , len) ; i >= le ; --i) push(i , dis[i]) ;
 
    for (int i = 1 ; i <= len ; ++i) {
        if (ri < 0) break ;
 
        db nd = tmp[i] + que[qL].x ;
        if (qL <= qR && nd > eps) return 1 ;
 
        pop(ri) ; --le ; --ri ;
        if (le >= 0) push(le , dis[le]) ;
    }
 
    return 0 ;
}
 
///
 
void findroot(int x , int fa) {
    int mx = 0 ; siz[x] = 1 ;
    for (Link *h = head[x] ; h ; h = h->next) {
        int nx = h->num ;
        if (nx == fa || vis[nx]) continue ;
 
        findroot(nx , x) ;
        siz[x] += siz[nx] ; mx = std::max(mx , siz[nx]) ;
    }
    mx = std::max(mx , tot - siz[x]) ;
 
    if (msiz > mx) msiz = mx , root = x ;
}
 
int getdep(int x , int fa) {
    int md = 0 ;
    for (Link *h = head[x] ; h ; h = h->next) {
        int nx = h->num ;
        if (nx == fa || vis[nx]) continue ;
 
        md = std::max(getdep(nx , x) , md) ;
    }
 
    return md + 1 ;
}
 
void update(int x , int fa , int d , db dis) {
    tmp[d] = std::max(tmp[d] , dis) ;
 
    for (Link *h = head[x] ; h ; h = h->next) {
        int nx = h->num ;
        if (nx == fa || vis[nx]) continue ;
 
        update(nx , x , d + 1 , dis + h->val) ;
    }
}
 
bool work(int x) {
    bool ans = 0 ;
    int md = 0 ; vis[x] = 1 ;
 
    for (Link *h = head[x] ; h ; h = h->next) {
        int nx = h->num ;
        if (vis[nx]) continue ;
 
        int tmp = getdep(nx , nx) ;
        md = std::max(tmp , md) ;
        srt[tmp].push_back(nx) ; d[nx] = h->val ;
    }
 
    for (int i = 1 ; i <= md ; ++i) {
        int len = srt[i].size() ;
        for (int j = 0 ; j < len && !ans ; ++j) {
            int nx = srt[i][j] ;
            update(nx , nx , 1 , d[nx]) ;
            ans |= calc(i) ;
 
            for (int k = 1 ; k <= i ; ++k) dis[k] = std::max(dis[k] , tmp[k]) , tmp[k] = -INF ;
        }
 
        srt[i].clear() ;
    }
 
    for (int i = 1 ; i <= md ; ++i) dis[i] = -INF ;
    if (ans) return ans ;
 
    ///
 
    int len = tre[x].size() ;
    for (int i = 0 ; i < len ; ++i) {
        int nx = tre[x][i] ;
        ans |= work(nx) ;
 
        if (ans) return 1 ;
    }
 
    return 0 ;
}
 
///
 
bool check(db x) {
    for (int i = 1 ; i <= n ; ++i) dis[i] = tmp[i] = -INF , vis[i] = 0 ;
    for (int i = 0 ; i < cur ; ++i) list[i].val = list[i].v - x ;
 
    return work(root) ;
}
 
void build(int x) {
    vis[x] = 1 ;
 
    for (Link *h = head[x] ; h ; h = h->next) {
        int nx = h->num ;
        if (vis[nx]) continue ;
 
        root = 0 ; msiz = tot = siz[nx] ;
        findroot(nx , nx) ;
 
        tre[x].push_back(root) ;
        build(root) ;
    }
}
 
///
 
int main() {
    db L = 0 , R = 0 ;
 
    n = read() ; minE = read() ; maxE = read() ;
    for (int i = 1 ; i < n ; ++i) {
        int x , y , v ;
        x = read() ; y = read() ; v = read() ;
 
        ins(x , y , v) ; ins(y , x , v) ; R = std::max(R , (db)v) ;
    }
 
    ///
 
    int tmp ;
    root = 0 ; msiz = tot = n ;
    findroot(1 , 1) ; tmp = root ;
 
    build(root) ; root = tmp ;
 
    for (; fabs(L - R) > eps ;) {
        db mid = (L + R) * 0.5 ;
 
        if (check(mid)) L = mid ;
        else R = mid ;
    }
 
    printf("%0.3lf\n" , L) ;
 
    return 0 ;
}