#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std ;

const int MAX_N = 200000 + 10 ;

int Q , Next[MAX_N] ;
char st[MAX_N] ;

int main() {
	scanf("%d" , &Q) ;
	for (int q = 1 ; q <= Q ; ++q) {
		memset(Next , 0 , sizeof(Next)) ;
		
		scanf("%s" , &st) ;
		int len = strlen(st) ;
		
		strcat(st , st) ;

		///
		
		int p = 0 ;
		Next[0] = len * 2 ;
		for (; st[p] == st[p + 1] ; ++p) ;
		Next[1] = p ; p = 1 ;
		
		for (int i = 2 ; i < len * 2 ; ++i) {
			int u = p + Next[p] ;
			
			if (i + Next[i - p] < u) Next[i] = Next[i - p] ;
			else {
				int t = max(u - i , 0) ;
				for (; st[t] == st[i + t] ; ++t) ;
				
				Next[i] = t ;
			}
			
			if (i + Next[i] > u) p = i ;
		}
		
		///
		
		int L = 0 , E = 0 , G = 0 ;
		for (int i = 0 ; i < len ; ++i) {
			if (Next[i] >= len) {++E ; continue ;}
			
			int p = Next[i] ;
			if (st[i + p] > st[p]) ++G ;
			else ++L ;
		}
		
		printf("Case %d: %d %d %d\n" , q , L / E , E / E , G / E) ;
	}
	
	return 0 ;
}
