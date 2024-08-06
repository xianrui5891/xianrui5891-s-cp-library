//Author:xianrui5891
//Problem:modint
//Time:2022-12-18 21:11:58
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

template <typename _type_,typename std::make_unsigned<_type_>::type modnum> class default_modint{
    static_assert(std::is_integral<_type_>::value&&std::is_signed<_type_>::value,"This type is not supplied");
protected:
    typedef typename std::make_unsigned<_type_>::type ntp;
    ntp a;
public:
    #define tp default_modint<_type_,modnum>
    template <typename T,typename std::enable_if<std::is_integral<T>::value>::type* =nullptr> 
        inline static tp raw(T x){tp ta;ta.a=x;return ta;}

    inline default_modint():a(0){}
    template <typename T,typename std::enable_if<is_integral<T>::value&&std::is_signed<T>::value>::type* =nullptr> 
        inline default_modint(T x){x%=modnum,a=(x<0?x+modnum:x);}
    template <typename T,typename std::enable_if<is_integral<T>::value&&std::is_unsigned<T>::value>::type* =nullptr> 
        inline default_modint(T x){a=x%modnum;}
    constexpr inline ntp val(){return a;}
    
    constexpr inline tp& operator ++(){return ((++a)==modnum?a=0:0),*this;}
    constexpr inline tp& operator --(){return ((!a)?a=modnum:0),--a,*this;}
    constexpr inline tp operator ++(int){tp res=*this;++*this;return res;}
    constexpr inline tp operator --(int){tp res=*this;--*this;return res;}
    constexpr inline tp& operator +=(const tp& x){return a+=x.a,(a>=modnum?a-=modnum:0),*this;}
    constexpr inline tp& operator -=(const tp& x){return a-=x.a,(a>=modnum?a+=modnum:0),*this;}
    template<class T> constexpr inline tp& operator *=(const T& x){}
    template<class T,typename std::enable_if<std::is_same<default_modint<T,modnum>,tp>::value&&std::is_same<_type_,long long>::value>::type* =nullptr>
        constexpr inline tp& operator *=(const default_modint<T,modnum>& x){return a=(a*x.a-(ntp)((long double)a/modnum*x.a+0.5L)*modnum),(a>=modnum?a+=modnum:0),*this;}
    template<class T,typename std::enable_if<std::is_same<default_modint<T,modnum>,tp>::value&&(!std::is_same<_type_,long long>::value)>::type* =nullptr>
        constexpr inline tp& operator *=(const default_modint<T,modnum>& x){return a=1ull*a*x.a%modnum,*this;}
    constexpr inline tp operator +(const tp& x)const{return tp(*this)+=x;}
    constexpr inline tp operator -(const tp& x)const{return tp(*this)-=x;}
    constexpr inline tp operator +()const{return *this;}
    constexpr inline tp operator -()const{return tp()-*this;}
    constexpr inline tp operator *(const tp& x)const{return tp(*this)*=x;}

    template <typename T> constexpr inline tp pow(T y){tp res(1),x=*this;for(;y;y>>=1,x*=x) if(y&1) res*=x;return res;}
    constexpr inline tp inv()const{
        _type_ x=modnum,y=a,r1=1,r2=0;
        if(a!=0){
            while(y){
                _type_ u=x/y;
                x-=y*u,r2-=r1*u,swap(x,y),swap(r1,r2);
            }
            if(r2<0) r2+=modnum/x;
        }
        assert(x==1);
        return raw(r2);
    }
    constexpr inline tp& operator /=(const tp& x){return *this*=x.inv();}
    constexpr inline tp operator /(const tp& x)const{return tp(*this)/=x;}
    constexpr inline bool operator ==(const tp& x){return a==x.a;}
    constexpr inline bool operator !=(const tp& x){return a!=x.a;}
    friend inline istream &operator >> (istream &in,tp& x){ntp tmp;in>>tmp,x=tp(tmp);return in;}
    friend inline ostream &operator << (ostream &out,const tp& x){out<<x.a;return out;}
    #undef tp
};

template <typename _type_,int id> class static_modint{
    static_assert(std::is_integral<_type_>::value&&std::is_signed<_type_>::value,"This type is not supplied");
protected:
    typedef typename std::make_unsigned<_type_>::type ntp;
    ntp a;
    static ntp modnum;
public:
    #define tp static_modint<_type_,id>
    inline static void setmod(_type_ x){assert(x>0),modnum=x;}
    template <typename T,typename std::enable_if<std::is_integral<T>::value>::type* =nullptr> 
        inline static tp raw(T x){tp ta;ta.a=x;return ta;}

    inline static_modint():a(0){}
    template <typename T,typename std::enable_if<is_integral<T>::value&&std::is_signed<T>::value>::type* =nullptr> 
        inline static_modint(T x){x%=modnum,a=(x<0?x+modnum:x);}
    template <typename T,typename std::enable_if<is_integral<T>::value&&std::is_unsigned<T>::value>::type* =nullptr> 
        inline static_modint(T x){a=x%modnum;}
    constexpr inline ntp val(){return a;}
    
    constexpr inline tp& operator ++(){return ((++a)==modnum?a=0:0),*this;}
    constexpr inline tp& operator --(){return ((!a)?a=modnum:0),--a,*this;}
    constexpr inline tp operator ++(int){tp res=*this;++*this;return res;}
    constexpr inline tp operator --(int){tp res=*this;--*this;return res;}
    constexpr inline tp& operator +=(const tp& x){return a+=x.a,(a>=modnum?a-=modnum:0),*this;}
    constexpr inline tp& operator -=(const tp& x){return a-=x.a,(a>=modnum?a+=modnum:0),*this;}
    template<class T> constexpr inline tp& operator *=(const T& x){}
    template<class T,typename std::enable_if<std::is_same<static_modint<T,id>,tp>::value&&std::is_same<_type_,long long>::value>::type* =nullptr>
        constexpr inline tp& operator *=(const static_modint<T,id>& x){return a=(a*x.a-(ntp)((long double)a/modnum*x.a+0.5L)*modnum),(a>=modnum?a+=modnum:0),*this;}
    template<class T,typename std::enable_if<std::is_same<static_modint<T,id>,tp>::value&&(!std::is_same<_type_,long long>::value)>::type* =nullptr>
        constexpr inline tp& operator *=(const static_modint<T,id>& x){return a=1ull*a*x.a%modnum,*this;}
    constexpr inline tp operator +(const tp& x)const{return tp(*this)+=x;}
    constexpr inline tp operator -(const tp& x)const{return tp(*this)-=x;}
    constexpr inline tp operator +()const{return *this;}
    constexpr inline tp operator -()const{return tp()-*this;}
    constexpr inline tp operator *(const tp& x)const{return tp(*this)*=x;}

    template <typename T> constexpr inline tp pow(T y){tp res(1),x=*this;for(;y;y>>=1,x*=x) if(y&1) res*=x;return res;}
    constexpr inline tp inv()const{
        _type_ x=modnum,y=a,r1=1,r2=0;
        if(a!=0){
            while(y){
                _type_ u=x/y;
                x-=y*u,r2-=r1*u,swap(x,y),swap(r1,r2);
            }
            if(r2<0) r2+=modnum/x;
        }
        assert(x==1);
        return raw(r2);
    }
    constexpr inline tp& operator /=(const tp& x){return *this*=x.inv();}
    constexpr inline tp operator /(const tp& x)const{return tp(*this)/=x;}
    constexpr inline bool operator ==(const tp& x){return a==x.a;}
    constexpr inline bool operator !=(const tp& x){return a!=x.a;}
    friend inline istream &operator >> (istream &in,tp& x){ntp tmp;in>>tmp,x=tp(tmp);return in;}
    friend inline ostream &operator << (ostream &out,const tp& x){out<<x.a;return out;}
    #undef tp
};
template<typename _type_,int id> typename std::make_unsigned<_type_>::type static_modint<_type_,id>::modnum=0;

template <typename _type_> class dynamic_modint{
    static_assert(std::is_integral<_type_>::value&&std::is_signed<_type_>::value,"This type is not supplied");
protected:
    typedef typename std::make_unsigned<_type_>::type ntp;
    ntp a,modnum;
public:
    #define tp dynamic_modint<_type_>
    inline void setmod(_type_ x){assert(x>0),modnum=x;}
    template <typename T,typename std::enable_if<std::is_integral<T>::value>::type* =nullptr> 
        inline tp raw(T x){tp ta;ta.a=x,ta.modnum=modnum;return ta;}

    inline dynamic_modint():a(0){}
    template <typename T,typename std::enable_if<is_integral<T>::value&&std::is_signed<T>::value>::type* =nullptr> 
        inline dynamic_modint(T x){x%=modnum,a=(x<0?x+modnum:x);}
    template <typename T,typename std::enable_if<is_integral<T>::value&&std::is_unsigned<T>::value>::type* =nullptr> 
        inline dynamic_modint(T x){a=x%modnum;}
    constexpr inline ntp val(){return a;}

    constexpr inline tp& operator ++(){return ((++a)==modnum?a=0:0),*this;}
    constexpr inline tp& operator --(){return ((!a)?a=modnum:0),--a,*this;}
    constexpr inline tp operator ++(int){tp res=*this;++*this;return res;}
    constexpr inline tp operator --(int){tp res=*this;--*this;return res;}
    constexpr inline tp& operator +=(const tp& x){return assert(modnum==x.modnum),a+=x.a,(a>=modnum?a-=modnum:0),*this;}
    constexpr inline tp& operator -=(const tp& x){return assert(modnum==x.modnum),a-=x.a,(a>=modnum?a+=modnum:0),*this;}
    template<class T> constexpr inline tp& operator *=(const T& x){}
    template<class T,typename std::enable_if<std::is_same<T,_type_>::value&&std::is_same<_type_,long long>::value>::type* =nullptr>
        constexpr inline tp& operator *=(const dynamic_modint<T>& x){
            return assert(modnum==x.modnum),a=(a*x.a-(ntp)((long double)a/modnum*x.a+0.5L)*modnum),(a>=modnum?a+=modnum:0),*this;
        }
    template<class T,typename std::enable_if<std::is_same<T,_type_>::value&&(!std::is_same<_type_,long long>::value)>::type* =nullptr>
        constexpr inline tp& operator *=(const dynamic_modint<T>& x){return assert(modnum==x.modnum),a=1ull*a*x.a%modnum,*this;}
    constexpr inline tp operator +(const tp& x)const{return tp(*this)+=x;}
    constexpr inline tp operator -(const tp& x)const{return tp(*this)-=x;}
    constexpr inline tp operator +()const{return *this;}
    constexpr inline tp operator -()const{tp tmp=*this;return tmp.a=0,tmp-*this;}
    constexpr inline tp operator *(const tp& x)const{return tp(*this)*=x;}

    template <typename T> constexpr inline tp pow(T y){tp res(1),x=*this;for(;y;y>>=1,x*=x) if(y&1) res*=x;return res;}
    constexpr inline tp inv()const{
        _type_ x=modnum,y=a,r1=1,r2=0;
        if(a!=0){
            while(y){
                _type_ u=x/y;
                x-=y*u,r2-=r1*u,swap(x,y),swap(r1,r2);
            }
            if(r2<0) r2+=modnum/x;
        }
        assert(x==1);
        return raw(r2);
    }
    constexpr inline tp& operator /=(const tp& x){return *this*=x.inv();}
    constexpr inline tp operator /(const tp& x)const{return tp(*this)/=x;}
    constexpr inline bool operator ==(const tp& x){return a==x.a;}
    constexpr inline bool operator !=(const tp& x){return a!=x.a;}
    friend inline istream &operator >> (istream &in,tp& x){ntp tmp;in>>tmp,x=tp(tmp);return in;}
    friend inline ostream &operator << (ostream &out,const tp& x){out<<x.a;return out;}
    #undef tp
};
template<typename _type_> using mint=static_modint<_type_,-1>;
template<typename _type_,_type_ modnum> using modint=default_modint<_type_,modnum>;

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
    modint<ll,998244353> a(51),b(27),ans;
    ans=a/b;
    cout<<ans.val()<<'\n';
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