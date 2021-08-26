#include <bits/stdc++.h>

#define ll long long

ll gcd(ll x , ll y) {return y ? gcd(y , x % y) : x ;}

inline ll lcm(ll x , ll y) {return x / gcd(x , y) * y ;}

int main() {
	ll res = 1 ;
	for (ll i = 1 ; i <= 20 ; ++i) res = lcm(res , i) ;
	printf("%lld\n" , res) ;

	return 0 ;
}