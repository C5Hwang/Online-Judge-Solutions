#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std ;

const int MAX_L = 1000000 + 10 ;

int Q , v['z' + 10] , Next[MAX_L] , val[MAX_L] ;
char st[MAX_L] , s1[MAX_L] ;

int find(int x , int y) {
	return val[y] - val[x - 1] ;
}

int main() {
	scanf("%d" , &Q) ;
	while (Q--) {
		for (int i = 'a' ; i <= 'z' ; ++i)
			scanf("%d" , &v[i]) ;
		scanf("%s" , &s1) ;
		
		///
		
		memset(st , 0 , sizeof(st)) ;
		memset(Next , 0 , sizeof(Next)) ;
		
		int p = 2 , len = strlen(s1) ;
		st[0] = '+' ; st[1] = '#' ;
		for (int i = 0 ; i < len ; ++i) {
			st[p] = s1[i] ; ++p ;
			st[p] = '#' ; ++p ;
		}
		st[p] = '-' ; ++p ;
		len = p ;
		
		///
		
		p = 1 ;
		Next[0] = 0 ; Next[1] = 0 ;
		int bor = len - 2 ;
		
		for (int i = 2 ; i < len ; ++i)	{
			int u = p + Next[p] , r = max(0 , min(u - i , Next[p * 2 - i])) ;
			
			for (; st[i + r + 1] == st[i - r - 1] ; ++r) ;
			
			Next[i] = r ;
			
			if (i + r > u) p = i ;
		}
		
		///
		
		val[0] = 0 ;
		for (int i = 1 ; i < len ; ++i)	{
			int anum = 0 ;
			if (st[i] != '#' && st[i] != '+' && st[i] != '-') anum = v[st[i]] ;
			
			val[i] = val[i - 1] + anum ;
		}
		
		///
		
		int res = 0 ;
		for (int i = 2 ; i < bor ; ++i)	{
			int L = i - Next[i] , R = i + Next[i] , Rp = (R + bor) / 2 , Lp = (1 + L) / 2 ;
			if (L == 1 && R == bor) continue ;
			if (L != 1 && R != bor) continue ;
			
			int sum = 0 ;
			if (L == 1) {
				sum += find(L , R) ;
				if (Next[Rp] == bor - R)
					sum += find(R , bor) ;
			}
			else if (R == bor) {
				sum += find(L , R) ;
				if (Next[Lp] == L - Lp)
					sum += find(1 , L) ;
			}
			
			res = max(res , sum) ;
		}
		
		printf("%d\n" , res) ;
	}
	
	return 0 ;
}
