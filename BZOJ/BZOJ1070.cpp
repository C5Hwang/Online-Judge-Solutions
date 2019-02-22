#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 60 + 5 , MAX_P = 600 + 10 , MAX_M = 5e3 + 10 , INF = 0x3f3f3f3f ;

struct Link {
    int num , cap , val ;
    Link *next , *reg ;
}list[MAX_M << 1] ;

std::queue<int> que ;

bool vis[MAX_P] ;
Link *head[MAX_P] , *id[MAX_P] ;
int T , pre[MAX_P] , flow[MAX_P] , dis[MAX_P] ;
int n , m , tot , cur , t[MAX_N][MAX_N] , bh[MAX_N][MAX_N] , wk[MAX_P] , nk[MAX_N] ;

void ins(int x , int y , int f , int v) {
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
    vis[0] = 1 ; dis[0] = 0 ; flow[0] = INF ;

    for (; !que.empty() ;) {
        int x = que.front() ;
        que.pop() ; vis[x] = 0 ;

        for (Link *h = head[x] ; h ; h = h->next) {
            int nx = h->num ;
            if (!h->cap || dis[nx] <= dis[x] + h->val) continue ;

            flow[nx] = std::min(flow[x] , h->cap) ;
            dis[nx] = dis[x] + h->val ; pre[nx] = x ; id[nx] = h ;

            if (!vis[nx]) vis[nx] = 1 , que.push(nx) ;
        }
    }

    return dis[T] < INF ;
}

int work() {
    int s = 0 ;
    for (; spfa() ;) {
        s += flow[T] * dis[T] ;

        int x = wk[pre[T]] , k = ++nk[x] ;
        for (int i = T ; i ; i = pre[i])
            id[i]->cap -= flow[T] , id[i]->reg->cap += flow[T] ;

        if (k <= n) {
            for (int i = 1 ; i <= n ; ++i) ins(i , bh[x][k] , 1 , k * t[x][i]) ;
            ins(bh[x][k] , T , 1 , 0) ;
        }
    }

    return s ;
}

int main() {
    scanf("%d %d" , &m , &n) ;

    tot = n ;
    for (int i = 1 ; i <= n ; ++i)
        for (int j = 1 ; j <= m ; ++j) {
            scanf("%d" , &t[j][i]) ;
            bh[j][i] = ++tot ; wk[tot] = j ; nk[j] = 1 ;
        }

    ///

    T = ++tot ;
    for (int i = 1 ; i <= n ; ++i) ins(0 , i , 1 , 0) ;

    for (int i = 1 ; i <= n ; ++i)
        for (int j = 1 ; j <= m ; ++j) ins(i , bh[j][1] , 1 , t[j][i]) ;
    for (int i = 1 ; i <= m ; ++i) ins(bh[i][1] , T , 1 , 0) ;

    printf("%0.2lf\n" , work() * 1.0 / n) ;

    return 0 ;
}