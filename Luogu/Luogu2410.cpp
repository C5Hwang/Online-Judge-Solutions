#include <queue>
#include <math.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define db double
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const db eps = 1e-7 ;
const int MAX_N = 100 + 10 , MAX_P = 200 + 10 , INF = 0x3f3f3f3f ;

struct data {int num , cap , reg ; db val ;} ;

std::queue<int> que ;
std::vector<data> eg[MAX_P] ;

bool vis[MAX_P] ;
db dis[MAX_P] , dt[MAX_N] ;
int T , tot , pre[MAX_P] , flow[MAX_P] , id[MAX_P] ;
int n , m , cur , r[MAX_N] , c[MAX_N] , P[MAX_N][MAX_N] , ans[MAX_N][MAX_N] ;

void ins(int x , int y , int f , db v) {
	int p1 = eg[x].size() , p2 = eg[y].size() ;

	eg[x].push_back((data){y , f , p2 , v}) ;
	eg[y].push_back((data){x , 0 , p1 , -v}) ;
}

bool spfa() {
    for (int i = 0 ; i <= tot ; ++i) dis[i] = INF ;

    que.push(0) ;
    dis[0] = flow[T] = 0 ; vis[0] = 1 ; flow[0] = INF ;

    for (; !que.empty() ;) {
        int x = que.front() , siz = eg[x].size() ;
        que.pop() ; vis[x] = 0 ;

        for (int i = 0 ; i < siz ; ++i) {
            int nx = eg[x][i].num ;
            if (!eg[x][i].cap || dis[nx] - dis[x] - eg[x][i].val < eps) continue ;

            dis[nx] = dis[x] + eg[x][i].val ;
            flow[nx] = std::min(flow[x] , eg[x][i].cap) ; pre[nx] = x ; id[nx] = i ;

            if (!vis[nx]) que.push(nx) , vis[nx] = 1 ;
        }
    }

    return flow[T] ;
}

void work() {
    for (; spfa() ;) {
        int f = flow[T] ;
        for (int x = T ; x ;) {
        	int p = id[x] , y = x ; x = pre[x] ;
        	eg[x][p].cap -= f ; eg[y][eg[x][p].reg].cap += f ;
        }
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

    dt[0] = INF ;
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
    for (int x = 1 ; x <= n ; ++x) {
    	int siz = eg[x].size() ;
        for (int i = 0 ; i < siz ; ++i) {
            int nx = eg[x][i].num ;
            if (!nx) continue ;
            else if (!eg[x][i].cap) ans[x][nx - n] = 1 ;
        }
    }

    for (int i = 1 ; i <= n ; ++i , putchar('\n'))
        for (int j = 1 ; j <= m ; ++j) putchar('0' + ans[i][j]) ;

    return 0 ;
}