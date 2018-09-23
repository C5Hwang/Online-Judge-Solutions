#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 2e3 + 10 , MAX_V = 4e3 + 10 , MAX_E = 3e4 + 10 , INF = 0x3f3f3f3f ;

std::queue<int> q ;

struct Link {
    int num , cost , cap ;
    Link *next , *reg ;
}list[MAX_E] ;

bool vis[MAX_V] ;
Link *head[MAX_V] , *id[MAX_V] ;
int n , p , d1 , c1 , d2 , c2 , r[MAX_N] ;
int S , T , tot , cur , bh[MAX_N] , pre[MAX_V] , dis[MAX_V] , flow[MAX_V] ;

///

bool spfa() {
    for (int i = S ; i <= T ; ++i) dis[i] = INF , vis[i] = 0 ;
    q.push(S) ; dis[S] = 0 ; vis[S] = 1 ; flow[S] = INF ;

    while (!q.empty()) {
        int x = q.front() ; q.pop() ; vis[x] = 0 ;

        for (Link *h = head[x] ; h ; h = h->next) {
            int nx = h->num ;
            if (dis[nx] <= dis[x] + h->cost || !h->cap) continue ;

            dis[nx] = dis[x] + h->cost ;
            pre[nx] = x ; id[nx] = h ; flow[nx] = std::min(flow[x] , h->cap) ;

            if (!vis[nx]) {vis[nx] = 1 ; q.push(nx) ;}
        }
    }

    return dis[T] < INF ;
}

long long MinCostMaxFlow() {
    long long sum = 0 ;
    for (; spfa() ;) {
        sum += (long long)flow[T] * dis[T] ;
        
        int x = T ;
        for (; x != S ; x = pre[x]) 
            {id[x]->cap -= flow[T] ; id[x]->reg->cap += flow[T] ;}
    }

    return sum ;
}

///

void ins(int x , int y , int c , int f) {
    list[cur].num = y ;
    list[cur].cap = f ;
    list[cur].cost = c ;
    list[cur].next = head[x] ;
    list[cur].reg = &list[cur + 1] ;
    head[x] = &list[cur++] ;

    list[cur].num = x ;
    list[cur].cap = 0 ;
    list[cur].cost = -c ;
    list[cur].next = head[y] ;
    list[cur].reg = &list[cur - 1] ;
    head[y] = &list[cur++] ;
}

int read() {
    int a = 0 , f = 1 ;
    char c = getchar() ;
    while (c < '0' || '9' < c) {if (c == '-') f = -f ; c = getchar() ;}
    while (c >= '0' && c <= '9') {a = a * 10 + c - '0' ; c = getchar() ;}

    return a * f ;
}

int main() {
    n = read() ;
    for (int i = 1 ; i <= n ; ++i) r[i] = read() , bh[i] = (tot += 2) ;
    p = read() ; d1 = read() ; c1 = read() ; d2 = read() ; c2 = read() ;

    ///
    
    S = 0 ; T = (tot += 2) ;
    for (int i = 1 ; i <= n ; ++i) {
        ins(S , bh[i] , p , INF) ;
        ins(S , bh[i]^1 , 0 , r[i]) ;
        ins(bh[i] , T , 0 , r[i]) ;

        if (i + d1 <= n) ins(bh[i]^1 , bh[i + d1] , c1 , INF) ;
        if (i + d2 <= n) ins(bh[i]^1 , bh[i + d2] , c2 , INF) ;
        if (i + 1 <= n) ins(bh[i] , bh[i + 1] , 0 , INF) ;
    }

    ///
    
    long long res = MinCostMaxFlow() ;

    printf("%lld\n" , res) ;

    return 0 ;
}
