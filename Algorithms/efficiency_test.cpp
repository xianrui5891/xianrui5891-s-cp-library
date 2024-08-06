//Author:xianrui5891
//Problem:test
//Time:2023-01-04 15:32:27
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

template<typename T> inline T read(){
    T t1=0,t2=1;
    char t3=gc();
    for(;!isdigit(t3);t3=gc()) if(t3=='-') t2=-1;
    while(isdigit(t3)) t1=(t1<<1)+(t1<<3)+(t3^48),t3=gc();
    return t2*t1;
}
template<typename T> inline void read(T &t1){t1=read<T>();}
template<typename T,typename ...arg> inline void read(T &t1,arg &...t2){read(t1),read(t2...);}

inline char cread(){
    char t3=gc();
    while(isspace(t3)) t3=gc();
    return t3;
}
inline int sread(char *t1){
    int t2=0;
    char t3=gc();
    while(isspace(t3)) t3=gc();
    while(!isspace(t3)) t1[++t2]=t3,t3=gc();
    return t1[t2+1]=0,t2;
}

template<typename T> inline void write(T t1){
    if(t1<0) t1=-t1,pc('-');
    if(t1>9) write(t1/10);
    pc(t1%10+'0');
}
inline void write(const char* t1){for(int tp=0;t1[tp]!=0;++tp) pc(t1[tp]);}
inline void write(char* t1){for(int tp=0;t1[tp]!=0;++tp) pc(t1[tp]);}
inline void write(char t1){pc(t1);}
template<typename T,typename ...arg> inline void write(T t1,arg ...t2){write(t1),write(t2...);}

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
    constexpr inline tp& operator +=(const tp& x){a+=x.a;if(a>=modnum) a-=modnum;return *this;}
    constexpr inline tp& operator -=(const tp& x){return a-=x.a,(a>=modnum?a+=modnum:0),*this;}
    template<class T> constexpr inline tp& operator *=(const T& x){}
    template<class T,typename std::enable_if<std::is_same<static_modint<T,id>,tp>::value&&std::is_same<_type_,long long>::value>::type* =nullptr>
        constexpr inline tp& operator *=(const static_modint<T,id>& x){return a=(a*x.a-(ntp)((long double)a/modnum*x.a+0.5L)*modnum),(a>=modnum?a+=modnum:0),*this;}
    template<class T,typename std::enable_if<std::is_same<static_modint<T,id>,tp>::value>::type* =nullptr>
        constexpr inline tp& operator *=(const static_modint<T,id>& x){return a=1ull*a*x.a%modnum,*this;}
    constexpr inline tp operator +(const tp& x)const{return tp(*this)+=x;}
    constexpr inline tp operator -(const tp& x)const{return tp(*this)-=x;}
    constexpr inline tp operator +()const{return *this;}
    constexpr inline tp operator -()const{return tp()-*this;}
    constexpr inline tp operator *(const tp& x)const{return tp(*this)*=x;}

    template <typename T> constexpr inline tp pow(T y){tp res(1),x=*this;for(;y;y>>=1,x*=x) if(y&1) res*=x;return res;}
    inline tp inv(){
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
    constexpr inline tp& operator /= (const tp& x){return *this*=x.inv(),*this;}
    constexpr inline tp operator / (const tp& x)const{return tp(*this)/=x;}

    constexpr inline bool operator ==(const tp& x){return a==x.a;}
    constexpr inline bool operator !=(const tp& x){return a!=x.a;}
    #undef tp
};
template<typename _type_,int id> typename std::make_unsigned<_type_>::type static_modint<_type_,id>::modnum=0;

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

template <typename answer_type,typename input_type
,class pushup_oper=default_pushup_oper<answer_type>
,class pushdown_oper=default_pushdown_oper<input_type>
,class assignment_oper=default_assignment_oper<answer_type,input_type> > class lazy_segment_tree{
protected:
    int size_,height;
    pushup_oper pushup;
    pushdown_oper pushdown;
    assignment_oper assign;
    answer_type answer_type_e;
    input_type input_type_e;
    std::vector<answer_type> nodes;
    std::vector<input_type> tags;

    inline int floor_log2(int x){return 32-__builtin_clz(x);}
    inline int ceil_log2(int x){return 32-__builtin_clz(x)+((x&-x)!=x);}

    inline void lazy_assign(int ind,input_type x){nodes[ind]=assign(nodes[ind],x),ind<size_?(tags[ind]=pushdown(tags[ind],x),void()):void();}
    inline void real_pushdown(int ind){lazy_assign(ind<<1,tags[ind]),lazy_assign(ind<<1|1,tags[ind]),tags[ind]=input_type_e;}
    inline void real_pushup(int ind){nodes[ind]=pushup(nodes[ind<<1],nodes[ind<<1|1]);}

    template<class unary_predicate_for_answer_t> inline void pushdown_until_all_true(int ind,unary_predicate_for_answer_t pred){
        if(ind>=size_||pred(nodes[ind])) return;
        if(!pred(nodes[ind<<1])) lazy_assign(ind<<1,tags[ind]);
        if(!pred(nodes[ind<<1|1])) lazy_assign(ind<<1|1,tags[ind]);
        tags[ind]=input_type_e,real_pushup(ind);
    }
    inline void all_pushdown(int lid,int rid){
        for(int i=height;i>=1;--i){
            if((lid>>i)==(rid>>i)) real_pushdown(lid>>i);
            else{
                if(((lid>>i)<<i)!=lid) real_pushdown(lid>>i);
                if(((rid>>i)<<i)!=rid) real_pushdown((rid-1)>>i);
            }
        }
    }
    inline void all_pushup(int lid,int rid){
        for(int i=1;i<=height;++i){
            if((lid>>i)==(rid>>i)) real_pushup(lid>>i);
            else{
                if(((lid>>i)<<i)!=lid) real_pushup(lid>>i);
                if(((rid>>i)<<i)!=rid) real_pushup((rid-1)>>i);
            }
        }
    }
public:
    inline answer_type& operator [](int x){return nodes[x+size_];}
    inline const answer_type operator [](int x)const{return nodes[x+size_];}
    inline answer_type& at(int x){return nodes.at(x+size_);}
    inline const answer_type at(int x)const{return nodes.at(x+size_);}
    inline void clear(){nodes=std::vector<answer_type>(size_*2,answer_type_e),tags=std::vector<input_type>(size_,input_type_e);}
    inline void resize(int x){size_=x,height=floor_log2(size_),clear();}
    inline void set_answer_type_e(answer_type answer_type_e_){answer_type_e=answer_type_e_;}
    inline void set_input_type_e(input_type input_type_e_){input_type_e=input_type_e_;}
    inline void set_pushup_oper(pushup_oper _oper){pushup=_oper;}
    inline void set_pushdown_oper(pushdown_oper _oper){pushdown=_oper;}
    inline void set_assignment_oper(assignment_oper _oper){assign=_oper;}
 
    inline void build(){
        for(int ind=size_-1;ind>0;--ind) nodes[ind]=pushup(nodes[ind<<1],nodes[ind<<1|1]);
    }
    inline void build(std::vector<input_type> in){
        int len=std::min((int)in.size(),size_);
        for(int i=0;i<len;++i) nodes[i+size_]=assign(nodes[i+size_],in[i]);
        build();
    }
    explicit inline lazy_segment_tree(){size_=0,height=0,answer_type_e=answer_type(),input_type_e=input_type();}
    explicit inline lazy_segment_tree(pushup_oper _oper1,pushdown_oper _oper2,assignment_oper _oper3):
    pushup(_oper1),pushdown(_oper2),assign(_oper3){
        size_=0,height=0,answer_type_e=answer_type(),input_type_e=input_type();
    }
    explicit inline lazy_segment_tree(int size__){size_=size__,height=floor_log2(size_),clear();}
    explicit inline lazy_segment_tree(std::vector<input_type> in){size_=in.size(),height=floor_log2(size_),clear(),build(in);}
    explicit inline lazy_segment_tree(int size__,answer_type answer_type_e_,input_type input_type_e_){
        size_=size__,height=floor_log2(size_),answer_type_e=answer_type_e_,input_type_e=input_type_e_,clear();
    }
    explicit inline lazy_segment_tree(std::vector<input_type> in,answer_type answer_type_e_,input_type input_type_e_){
        size_=in.size(),height=floor_log2(size_),answer_type_e=answer_type_e_,input_type_e=input_type_e_,clear(),build(in);
    }
    explicit inline lazy_segment_tree(int size__,answer_type answer_type_e_,input_type input_type_e_
    ,pushup_oper _oper1,pushdown_oper _oper2,assignment_oper _oper3):
    pushup(_oper1),pushdown(_oper2),assign(_oper3){
        size_=size__,height=floor_log2(size_),answer_type_e=answer_type_e_,input_type_e=input_type_e_,clear();
    }
    explicit inline lazy_segment_tree(std::vector<input_type> in,answer_type answer_type_e_,input_type input_type_e_
    ,pushup_oper _oper1,pushdown_oper _oper2,assignment_oper _oper3):
    pushup(_oper1),pushdown(_oper2),assign(_oper3){
        size_=in.size(),height=floor_log2(size_),answer_type_e=answer_type_e_,input_type_e=input_type_e_,clear(),build(in);
    }

    inline void update(int l,int r,input_type x){
        assert(l>=0&&r<size_&&l<=r);
        l+=size_,r+=size_+1,all_pushdown(l,r);
        int tl=l,tr=r;
        while(tl<tr){
            if(tl&1) lazy_assign(tl++,x);
            if(tr&1) lazy_assign(--tr,x);
            tl>>=1,tr>>=1;
        }
        all_pushup(l,r);
    }
    inline void update(int pos,input_type x){
        assert(pos>=0&&pos<size_);
        pos+=size_;
        for(int i=height;i>=1;--i) real_pushdown(pos>>i);
        nodes[pos]=assign(nodes[pos],x);
        while(pos>>=1) real_pushup(pos);
    }
    inline void default_update(int pos,answer_type x){
        assert(pos>=0&&pos<size_);
        pos+=size_;
        for(int i=height;i>=1;--i) real_pushdown(pos>>i);
        nodes[pos]=x;
        while(pos>>=1) real_pushup(pos);
    }
    template<class unary_predicate_for_answer_t> inline void beats_update(int l,int r,input_type x,unary_predicate_for_answer_t pred){
        assert(l>=0&&r<size_&&l<=r);
        l+=size_,r+=size_+1,all_pushdown(l,r);
        int tl=l,tr=r;
        while(tl<tr){
            if(tl&1) lazy_assign(tl,x),pushdown_until_all_true(tl++,pred);
            if(tr&1) lazy_assign(--tr,x),pushdown_until_all_true(tr,pred);
            tl>>=1,tr>>=1;
        }
        all_pushup(l,r);
    }

    constexpr inline answer_type query_all()const{return nodes[1];}
    inline answer_type query(int l,int r){
        assert(l>=0&&r<size_);
        if(r<l) return answer_type_e;
        l+=size_,r+=size_+1,all_pushdown(l,r);
        answer_type resl=answer_type_e,resr=answer_type_e;
        while(l<r){
            if(l&1) resl=pushup(resl,nodes[l++]);
            if(r&1) resr=pushup(nodes[--r],resr);
            l>>=1,r>>=1;
        }
        return pushup(resl,resr);
    }
    inline answer_type query(int pos){
        assert(pos>=0&&pos<size_);
        pos+=size_;
        for(int i=height;i>=1;--i) real_pushdown(pos>>i);
        return nodes[pos];
    }
};

#define lazy_segtree_template lazy_segment_tree<answer_type,input_type,pushup_oper,pushdown_oper,assignment_oper>
template <typename answer_type,typename input_type
,class pushup_oper=default_pushup_oper<answer_type>
,class pushdown_oper=default_empty<input_type>
,class assignment_oper=default_assignment_oper<answer_type,input_type> > class lazy_and_binary_search_segment_tree:
public lazy_segtree_template{
private:
    using p_=lazy_segtree_template;
    using p_::size_;
    using p_::height;
    using p_::pushup;
    using p_::pushdown;
    using p_::assign;
    using p_::answer_type_e;
    using p_::input_type_e;
    using p_::nodes;
    using p_::tags;
    using p_::real_pushdown;
    using p_::floor_log2;
    using p_::ceil_log2;
public:
    using p_::clear;
    using p_::build;
    inline void resize(int x){size_=1<<ceil_log2(x),height=floor_log2(size_),clear();}

    explicit inline lazy_and_binary_search_segment_tree(){size_=0,height=0,answer_type_e=answer_type(),p_::input_type_e=input_type();}
    explicit inline lazy_and_binary_search_segment_tree(pushup_oper _oper1,pushdown_oper _oper2,assignment_oper _oper3):p_(_oper1,_oper2,_oper3){
        size_=0,height=0,answer_type_e=answer_type(),input_type_e=input_type();
    }
    explicit inline lazy_and_binary_search_segment_tree(int size__){size_=1<<ceil_log2(size__),height=floor_log2(size_),clear();}
    explicit inline lazy_and_binary_search_segment_tree(std::vector<input_type> in){size_=1<<ceil_log2(in.size()),height=floor_log2(size_),clear(),build(in);}
    explicit inline lazy_and_binary_search_segment_tree(int size__,answer_type answer_type_e_,input_type input_type_e_){
        size_=1<<ceil_log2(size__),height=floor_log2(size_),answer_type_e=answer_type_e_,input_type_e=input_type_e_,clear();
    }
    explicit inline lazy_and_binary_search_segment_tree(std::vector<input_type> in,answer_type answer_type_e_,input_type input_type_e_){
        size_=1<<ceil_log2(in.size()),height=floor_log2(size_),answer_type_e=answer_type_e_,input_type_e=input_type_e_,clear(),build(in);
    }
    explicit inline lazy_and_binary_search_segment_tree(int size__,answer_type answer_type_e_,input_type input_type_e_
    ,pushup_oper _oper1,pushdown_oper _oper2,assignment_oper _oper3):p_(_oper1,_oper2,_oper3){
        size_=1<<ceil_log2(size__),height=floor_log2(size_),answer_type_e=answer_type_e_,input_type_e=input_type_e_,clear();
    }
    explicit inline lazy_and_binary_search_segment_tree(std::vector<input_type> in,answer_type answer_type_e_,input_type input_type_e_
    ,pushup_oper _oper1,pushdown_oper _oper2,assignment_oper _oper3):p_(_oper1,_oper2,_oper3){
        size_=1<<ceil_log2(in.size()),height=floor_log2(size_),answer_type_e=answer_type_e_,input_type_e=input_type_e_,clear(),build(in);
    }

    template<class unary_predicate_for_answer_t> inline int min_left(int pos,unary_predicate_for_answer_t pred){
        assert(pos>=0&&pos<size_);
        if(!pred(nodes[pos])) return -1;
        if(pos==0) return 0;
        pos+=size_;
        for(int i=height;i>=1;--i) real_pushdown(pos>>i);
        answer_type tmp=answer_type_e;
        while((pos&-pos)!=pos){
            while((pos&1)&&pos>1) pos>>=1;
            answer_type &&t1=pushup(nodes[pos],tmp);
            if(!pred(t1)){
                while(pos<size_){
                    real_pushdown(pos),pos=pos<<1|1;
                    answer_type &&t2=pushup(nodes[pos],tmp);
                    if(pred(t2)) tmp=t2,--pos;
                }
                return pos-size_+1;
            }
            tmp=t1,--pos;
        }
        return 0;
    }
    template<class unary_predicate_for_answer_t> inline int max_right(int pos,unary_predicate_for_answer_t pred){
        assert(pos>=0&&pos<size_);
        if(!pred(nodes[pos])) return -1;
        if(pos==size_-1) return size_-1;
        pos+=size_;
        for(int i=height;i>=1;--i) real_pushdown(pos>>i);
        answer_type tmp=answer_type_e;
        while(((~pos)&-(~pos))!=pos+1){
            while((pos&1)==0) pos>>=1;
            answer_type &&t1=pushup(tmp,nodes[pos]);
            if(!pred(t1)){
                while(pos<size_){
                    real_pushdown(pos),pos=pos<<1;
                    answer_type &&t2=pushup(tmp,nodes[pos]);
                    if(pred(t2)) tmp=t2,++pos;
                }
                return pos-size_-1;
            }
            tmp=t1,++pos;
        }
        return size_-1;
    }
};
#undef lazy_segtree_template

int main(){
    int n,m,p;
    read(n,m,p);
    using mt=static_modint<int,-1>;
    mt::setmod(p);
    vector<pair<mt,mt> > in(n);
    for(auto &[x,y]:in) y=read<int>();
    auto pushup=[](pair<mt,int> a,pair<mt,int> b) ->pair<mt,int> {return {a.first+b.first,a.second+b.second};};
    auto pushdown=[](pair<mt,mt> a,pair<mt,mt> b) ->pair<mt,mt> {return {a.first*b.first,a.second*b.first+b.second};};
    auto assign=[](pair<mt,int> a,pair<mt,mt> b) ->pair<mt,int> {return {a.first*b.first+mt(a.second)*b.second,a.second};};
    lazy_segment_tree<pair<mt,int>,pair<mt,mt>,decltype(pushup),decltype(pushdown),decltype(assign)> tr(in,{0,1},{1,0},pushup,pushdown,assign);
    while(m--){
        int op,x,y,k;
        read(op,x,y);
        if(op==1) read(k),tr.update(x-1,y-1,{k,0});
        else if(op==2) read(k),tr.update(x-1,y-1,{1,k});
        else write(tr.query(x-1,y-1).first.val(),'\n');
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