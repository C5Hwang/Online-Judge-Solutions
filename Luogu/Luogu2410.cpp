#include <queue>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define db double
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const db eps = 1e-7 ;
const int MAX_N = 100 + 10 , MAX_P = 200 + 10 , MAX_M = 2e4 + 10 , INF = 0x3f3f3f3f ;

struct Link {
    int num , cap ; db val ;
    Link *next , *reg ;
}list[MAX_M << 1] ;

std::queue<int> que ;

bool vis[MAX_P] ;
db dis[MAX_P] , dt[MAX_N] ;
Link *head[MAX_P] , *id[MAX_P] ;
int T , tot , pre[MAX_P] , flow[MAX_P] ;
int n , m , cur , r[MAX_N] , c[MAX_N] , P[MAX_N][MAX_N] , ans[MAX_N][MAX_N] ;

void ins(int x , int y , int f , db v) {
    list[cur].num = y ;
    list[cur].cap = f ;
    list[cur].val = v ;
    list[cur].next = head[x] ;
    list[cur].reg = &list[cur^1] ;
    head[x] = &list[cur++] ;

    list[cur].num = x ;
    list[cur].cap = 0 ;
    list[cur].val = -v ;
    list[cur].next = head[y] ;
    list[cur].reg = &list[cur^1] ;
    head[y] = &list[cur++] ;
}

bool spfa() {
    for (int i = 0 ; i <= tot ; ++i) dis[i] = INF ;

    que.push(0) ;
    dis[0] = flow[T] = 0 ; vis[0] = 1 ; flow[0] = INF ;

    for (; !que.empty() ;) {
        int x = que.front() ;
        que.pop() ; vis[x] = 0 ;

        for (Link *h = head[x] ; h ; h = h->next) {
            int nx = h->num ;
            if (!h->cap || dis[nx] - dis[x] - h->val < eps) continue ;

            dis[nx] = dis[x] + h->val ;
            flow[nx] = std::min(flow[x] , h->cap) ; pre[nx] = x ; id[nx] = h ;

            if (!vis[nx]) que.push(nx) , vis[nx] = 1 ;
        }
    }

    return flow[T] ;
}

void work() {
    for (; spfa() ;) {
        int f = flow[T] ;
        for (int x = T ; x ; x = pre[x])
            id[x]->cap -= f , id[x]->reg->cap += f ;
    }
}

inline int read() {
    char c = getchar() ;
    int num = 0 , f = 1 ;

    for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
    for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

    return num * f ;
}

int main() {
    n = read() ; m = read() ;
    for (int i = 1 ; i <= n ; ++i)
        for (int j = 1 ; j <= m ; ++j) P[i][j] = read() ;

    ///

    dt[0] = MAX_M ;
    for (int i = 1 ; i < 100 ; ++i) dt[i] = -log(i) ;
    for (int i = 1 ; i <= n ; ++i) r[i] = ++tot ;
    for (int i = 1 ; i <= m ; ++i) c[i] = ++tot ;

    T = ++tot ;
    for (int i = 1 ; i <= n ; ++i) {
        int t ; t = read() ;
        ins(0 , r[i] , t , 0) ;
    }
    for (int i = 1 ; i <= m ; ++i) {
        int t ; t = read() ;
        ins(c[i] , T , t , 0) ;
    }

    ///

    for (int i = 1 ; i <= n ; ++i)
        for (int j = 1 ; j <= m ; ++j)
        	ins(r[i] , c[j] , 1 , dt[P[i][j]]) ;

    work() ;
    for (int x = 1 ; x <= n ; ++x)
        for (Link *h = head[x] ; h ; h = h->next) {
            int nx = h->num ;
            if (!nx) continue ;
            else if (!h->cap) ans[x][nx - n] = 1 ;
        }

    for (int i = 1 ; i <= n ; ++i , putchar('\n'))
        for (int j = 1 ; j <= m ; ++j) putchar('0' + ans[i][j]) ;

    return 0 ;
}