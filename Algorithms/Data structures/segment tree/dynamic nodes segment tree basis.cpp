//Author:xianrui5891
//Problem:dynamic nodes segment tree basis
//Time:2023-01-20 21:43:07
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

template <typename mytp> struct default_empty{
    inline mytp operator ()(const mytp &a,const mytp &b)const{return mytp();}
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

template<typename answer_type,typename input_type
,class pushup_oper=default_pushup_oper<answer_type>
,class pushdown_oper=default_pushdown_oper<input_type>
,class assignment_oper=default_assignment_oper<answer_type,input_type> >
class segment_tree_d{
protected:
    vector<input_type> 
public:


}

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
    
    return 0;
}