//Author:xianrui5891
//Problem:functions
//Time:2022-12-18 11:42:19
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define lll __int128
#define db double
#define gc getchar
#define pc putchar
#define it iterator
#define pb push_back
using namespace std;

template <typename _type_> struct maximize{
    constexpr inline _type_ operator()(const _type_ &x,const _type_ &y)const{return x<y?y:x;}
};

template <typename _type_> struct minimize{
    constexpr inline _type_ operator()(const _type_ &x,const _type_ &y)const{return x<y?x:y;}
};

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
    
    return 0;
}