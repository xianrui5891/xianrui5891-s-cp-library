//Author:xianrui5891
//Problem:fenwick
//Time:2024-07-10 11:51:06
#include <bits/stdc++.h>
#define ll long long
#define uint unsigned int
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

template <typename _type_,class pushup_oper=default_pushup_oper<_type_>> class fenwick{
protected://自行定义 answer 减法以作区间操作用;
    pushup_oper pushup;
    _type_ _type_e;
    uint size_;
    vector<_type_> nodes;    
public://从1开始;
    inline void clear(){nodes=std::vector<_type_>(size_,_type_e);}
    inline void resize(int x){size_=x,clear();}
    inline void set_answer_type_e(_type_ answer_type_e_){_type_e=answer_type_e_;}
    inline void set_pushup_oper(pushup_oper _oper){pushup=_oper;}
    inline uint size(){return size_-1;}

    inline void modify(int pos,_type_ x){
        if(pos>0&&pos<size_)
            for(;pos<size_;pos+=pos&-pos) nodes[pos]=pushup(nodes[pos],assign(x));
    }
    inline void modify(int l,int r,_type_ x){modify(l,x),modify(r+1,-x);}
    inline _type_ query(int pos){
        assert(pos>=0&&pos<size_);
        if(pos==0) return 0;
        _type_ res=_type_e;
        for(;pos;pos^=pos&-pos) res=pushup(res,nodes[pos]);
        return res;
    }
    inline _type_ query(int l,int r){return query(r)-query(l-1);}

    constexpr inline void build_frq(vector<_type_> in){
        assert(in.size()==size_-1);
        for(uint i=0;i<in.size();++i) modify(i+1,in[i]);
    }//对应区间查询的构建
    constexpr inline void build_frm(vector<_type_> in){
        assert(in.size()==size_-1);
        for(uint i=0;i<in.size();++i) modify(i+1,i+1,in[i]);
    }//对于区间修改构建
    explicit inline fenwick():size_(1),_type_e(),nodes(1){}
    explicit inline fenwick(int n):size_(n+1),nodes(n+1),_type_e(){}
    explicit inline fenwick(int n,_type_ e1):size_(n+1),nodes(n+1),_type_e(e1){}
    explicit inline fenwick(int n,_type_ e1,pushup_oper _oper):size_(n+1),nodes(n+1),_type_e(e1){pushup=_oper;}
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