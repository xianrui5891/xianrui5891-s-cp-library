//Author:xianrui5891
//Problem:basic data structures operators
//Time:2024-07-17 10:51:03
#include <bits/stdc++.h>
#define uint unsigned int
#define ll long long
#define ull unsigned ll
#define lll __int128
#define db double
#define gc getchar
#define pc putchar
#define it iterator
#define pb push_back
#define all(x) x.begin(),x.end()
using namespace std;

template <typename mytp> struct default_empty{
    inline mytp operator ()([[maybe_unused]]const mytp &a,[[maybe_unused]]const mytp &b)const{return mytp();}
};

template <typename mytp> struct default_pushup_oper{
    inline mytp operator ()(const mytp &a,const mytp &b)const{return a+b;}
};

template <typename mytp> struct default_pushdown_oper{
    inline mytp operator ()(const mytp &a,const mytp &b)const{return a+b;}
};

template <typename answer_type,typename input_type> struct default_assignment_oper{
    inline answer_type operator ()(const answer_type &a,const input_type &b)const{return a+b;}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
    
    return 0;
}
/*
Storms don't scare me
No not anymore
It's been pain and lately worse than before
I'm feeling that a strong restart
I wake up to see the sunrise
And storms don't scare me
'Cause the flowers never gonna bloom
If they don't get a little rain
I've got a lot of stories now
From pushin' through the pain
And every time I'm fallin' down
I've learn from my mistakes
I think there's something beautiful
In knowing how to break
--from Knowing How to Break by Last Heroes and RUNN
*/