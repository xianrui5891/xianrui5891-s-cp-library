//Author:xianrui5891
//Problem:matrix
//Time:2023-01-07 19:29:34
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

template<typename mytp,int sz> struct matrix{
    mytp mat[sz][sz];
    matrix(){memset(mat,0,sizeof mat);}
    
    inline mytp* operator[](int x){return mat[x];}
    inline const mytp* operator[](int x)const{return mat[x];}

    inline matrix<mytp,sz> operator +(matrix<mytp,sz> t){
        for(int i=0;i<sz;++i) for(int j=0;j<sz;++j) t[i][j]+=mat[i][j];
        return t;
    }

    inline matrix<mytp,sz> operator -(matrix<mytp,sz> t){
        for(int i=0;i<sz;++i) for(int j=0;j<sz;++j) t[i][j]-=mat[i][j];
        return t;
    }

    inline matrix<mytp,sz> operator *(const matrix<mytp,sz> &t){
        matrix<mytp,sz> res;mytp x;
        for(int i=0;i<sz;++i) for(int j=0;j<sz;++j){
            x=mat[i][j];
            if(x==0) continue;
            for(int k=0;k<sz;++k) res[i][k]+=x*t[j][k];
        }
        return res;
    }

    inline matrix<mytp,sz> inverse(){
        
    }

    inline matrix<mytp,sz> pow(ll y){
        matrix<mytp,sz> res,x=*this;
        for(int i=0;i<sz;++i) res[i][i]=1;
        for(;y;y>>=1,x=x*x) if(y&1) res=res*x;
        return res;
    }
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