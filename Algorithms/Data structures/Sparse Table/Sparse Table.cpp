//Author:xianrui5891
//Problem:Sparse Table
//Time:2022-12-11 18:19:47
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

template<typename _type_,class _operator=maximize<_type_> > class sparse_table{
protected:
    std::vector<std::vector<_type_> > st;
    int msz,_size;
    _operator oper;
public:
    inline _type_& operator [](int x){return st[0][x];}
    inline const _type_ operator [](int x)const{return st[0][x];}
    inline _type_& at(int x){return st.at(0).at(x);}
    inline const _type_ at(int x)const{return st.at(0).at(x);}
    inline void clear(){std::vector<std::vector<_type_> >().swap(st),st.resize(1),st[0].resize(_size),msz=0;}
    inline void resize(int size__){_size=size__,clear();}
    inline void set_operator(_operator _oper){oper=_oper;}

    inline void init(std::vector<_type_> val){
        st[0]=val,st[0].resize(_size);
        int len=val.size();
        msz=31-__builtin_clz(len);
        st.resize(msz+1);
        for(int j=1,k;j<=msz;++j){
            st[j].resize(k=len-(1<<j)+1);
            for(int i=0;i<k;++i) st[j][i]=oper(st[j-1][i],st[j-1][i+(1<<(j-1))]);
        }
    }
    inline void init(int len){
        msz=31-__builtin_clz(len);
        st.resize(msz+1);
        for(int j=1,k;j<=msz;++j){
            st[j].resize(k=len-(1<<j)+1);
            for(int i=0;i<k;++i) st[j][i]=oper(st[j-1][i],st[j-1][i+(1<<(j-1))]);
        }
    }
    inline void init(){init(_size);}

    inline sparse_table(){msz=0,_size=0,st.resize(1);}
    inline sparse_table(_operator the_oper):oper(the_oper){msz=0,_size=0,st.resize(1);}
    inline sparse_table(std::vector<_type_> val){st.resize(1),init(val);}
    inline sparse_table(std::vector<_type_> val,_operator the_oper):oper(the_oper){st.resize(1),init(val);}
    inline sparse_table(int size__):msz(0),_size(size__){st.resize(1),st[0].resize(_size);}
    inline sparse_table(int size__,_operator the_oper):oper(the_oper),msz(0),_size(size__){st.resize(1),st[0].resize(_size);}

    inline _type_ qry(int l,int r){assert(l<=r);int k=31-__builtin_clz(r-l+1);return oper(st[k][l],st[k][r-(1<<k)+1]);}
};

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
    int n,m;
    cin>>n>>m;
    vector<int> in;
    in.resize(n);
    for(int &e:in) cin>>e;
    sparse_table<int> st(in);
    while(m--){
        int l,r;
        cin>>l>>r;
        cout<<st.qry(l-1,r-1)<<'\n';
    }
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