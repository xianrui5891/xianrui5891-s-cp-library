//Author:xianrui5891
//Problem:basic segment tree
//Time:2022-12-23 19:15:04
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

template <typename answer_type,typename input_type
,class pushup_oper=default_pushup_oper<answer_type>
,class pushdown_oper=default_pushdown_oper<input_type>
,class assignment_oper=default_assignment_oper<answer_type,input_type> > class segment_tree{
protected://注意assign有返回值
    int size_,height;
    pushup_oper pushup;
    pushdown_oper pushdown;
    assignment_oper assign;
    answer_type answer_type_e;
    input_type input_type_e;
    std::vector<answer_type> nodes;
    std::vector<input_type> tags;

    inline int floor_log2(int x){return 32-__builtin_clz(x);}//其实是log2 floor +1,下方同理
    inline int ceil_log2(int x){return 32-__builtin_clz(x)+((x&-x)!=x);}

    inline void lazy_assign(int ind,input_type x){nodes[ind]=assign(nodes[ind],x),ind<size_?(tags[ind]=pushdown(tags[ind],x),void()):void();}
    inline void real_pushdown(int ind){
        if constexpr(!is_same_v<pushdown_oper,default_empty<answer_type>>)
            if(tags[ind]!=input_type_e) 
                lazy_assign(ind<<1,tags[ind]),lazy_assign(ind<<1|1,tags[ind]),tags[ind]=input_type_e;
    }
    inline void real_pushup(int ind){nodes[ind]=pushup(nodes[ind<<1],nodes[ind<<1|1]);}

    template<class unary_predicate_for_answer_t> inline void pushdown_until_all_true(int ind,unary_predicate_for_answer_t pred){
        if(ind>=size_||pred(nodes[ind])) return;
        if(!pred(nodes[ind<<1])) lazy_assign(ind<<1,tags[ind]);
        if(!pred(nodes[ind<<1|1])) lazy_assign(ind<<1|1,tags[ind]);
        tags[ind]=input_type_e;
    }
    inline void all_pushdown(int lid,int rid){
        if constexpr(is_same_v<pushdown_oper,default_empty<answer_type>>) return;
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
    inline const answer_type at(int x)const{return nodes.at(x+size_);}//从0开始
    inline void clear(){nodes=std::vector<answer_type>(size_*2,answer_type_e),tags=std::vector<input_type>(size_,input_type_e);}
    inline void resize(int x){size_=x,height=floor_log2(size_),clear();}
    inline void set_answer_type_e(answer_type answer_type_e_){answer_type_e=answer_type_e_;}
    inline void set_input_type_e(input_type input_type_e_){input_type_e=input_type_e_;}
    inline void set_pushup_oper(pushup_oper _oper){pushup=_oper;}
    inline void set_pushdown_oper(pushdown_oper _oper){pushdown=_oper;}
    inline void set_assignment_oper(assignment_oper _oper){assign=_oper;}
 
    constexpr inline void build(){
        for(int ind=size_-1;ind>0;--ind) nodes[ind]=pushup(nodes[ind<<1],nodes[ind<<1|1]);
    }
    constexpr inline void build(std::vector<input_type> in){
        int len=std::min((int)in.size(),size_);
        for(int i=0;i<len;++i) nodes[i+size_]=assign(nodes[i+size_],in[i]);
        build();
    }//vector从0开始整体送入segtree
    explicit inline segment_tree(){size_=0,height=0,answer_type_e=answer_type(),input_type_e=input_type();}
    explicit inline segment_tree(pushup_oper _oper1,pushdown_oper _oper2,assignment_oper _oper3):
    pushup(_oper1),pushdown(_oper2),assign(_oper3){
        size_=0,height=0,answer_type_e=answer_type(),input_type_e=input_type();
    }
    explicit inline segment_tree(int size__){size_=size__,height=floor_log2(size_),clear();}
    explicit inline segment_tree(std::vector<input_type> in){size_=in.size(),height=floor_log2(size_),clear(),build(in);}
    explicit inline segment_tree(int size__,answer_type answer_type_e_,input_type input_type_e_){
        size_=size__,height=floor_log2(size_),answer_type_e=answer_type_e_,input_type_e=input_type_e_,clear();
    }
    explicit inline segment_tree(std::vector<input_type> in,answer_type answer_type_e_,input_type input_type_e_){
        size_=in.size(),height=floor_log2(size_),answer_type_e=answer_type_e_,input_type_e=input_type_e_,clear(),build(in);
    }
    explicit inline segment_tree(int size__,answer_type answer_type_e_,input_type input_type_e_
    ,pushup_oper _oper1,pushdown_oper _oper2,assignment_oper _oper3):
    pushup(_oper1),pushdown(_oper2),assign(_oper3){
        size_=size__,height=floor_log2(size_),answer_type_e=answer_type_e_,input_type_e=input_type_e_,clear();
    }
    explicit inline segment_tree(std::vector<input_type> in,answer_type answer_type_e_,input_type input_type_e_
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
        for(int i=1;i<=height;++i) real_pushup(pos>>i);
    }
    inline void default_update(int pos,answer_type x){
        assert(pos>=0&&pos<size_);
        pos+=size_;
        for(int i=height;i>=1;--i) real_pushdown(pos>>i);
        nodes[pos]=x;
        for(int i=1;i<=height;++i) real_pushup(pos>>i);
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

#define segtree_template segment_tree<answer_type,input_type,pushup_oper,pushdown_oper,assignment_oper>
template <typename answer_type,typename input_type
,class pushup_oper=default_pushup_oper<answer_type>
,class pushdown_oper=default_empty<input_type>
,class assignment_oper=default_assignment_oper<answer_type,input_type> > class binary_search_segment_tree:
public segtree_template{
private:
    using p_=segtree_template;
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

    explicit inline binary_search_segment_tree(){size_=0,height=0,answer_type_e=answer_type(),input_type_e=input_type();}
    explicit inline binary_search_segment_tree(pushup_oper _oper1,pushdown_oper _oper2,assignment_oper _oper3):p_(_oper1,_oper2,_oper3){
        size_=0,height=0,answer_type_e=answer_type(),input_type_e=input_type();
    }
    explicit inline binary_search_segment_tree(int size__){size_=1<<ceil_log2(size__),height=floor_log2(size_),clear();}
    explicit inline binary_search_segment_tree(std::vector<input_type> in){size_=1<<ceil_log2(in.size()),height=floor_log2(size_),clear(),build(in);}
    explicit inline binary_search_segment_tree(int size__,answer_type answer_type_e_,input_type input_type_e_){
        size_=1<<ceil_log2(size__),height=floor_log2(size_),answer_type_e=answer_type_e_,input_type_e=input_type_e_,clear();
    }
    explicit inline binary_search_segment_tree(std::vector<input_type> in,answer_type answer_type_e_,input_type input_type_e_){
        size_=1<<ceil_log2(in.size()),height=floor_log2(size_),answer_type_e=answer_type_e_,input_type_e=input_type_e_,clear(),build(in);
    }
    explicit inline binary_search_segment_tree(int size__,answer_type answer_type_e_,input_type input_type_e_
    ,pushup_oper _oper1,pushdown_oper _oper2,assignment_oper _oper3):p_(_oper1,_oper2,_oper3){
        size_=1<<ceil_log2(size__),height=floor_log2(size_),answer_type_e=answer_type_e_,input_type_e=input_type_e_,clear();
    }
    explicit inline binary_search_segment_tree(std::vector<input_type> in,answer_type answer_type_e_,input_type input_type_e_
    ,pushup_oper _oper1,pushdown_oper _oper2,assignment_oper _oper3):p_(_oper1,_oper2,_oper3){
        size_=1<<ceil_log2(in.size()),height=floor_log2(size_),answer_type_e=answer_type_e_,input_type_e=input_type_e_,clear(),build(in);
    }

    template<class unary_predicate_for_answer_t> inline int min_left(int pos,unary_predicate_for_answer_t pred){
        assert(pos>=0&&pos<size_);
        if(!pred(nodes[pos+size_])) return pos+1;
        if(pos==0) return 0;
        pos+=size_;
        for(int i=height;i>=1;--i) real_pushdown(pos>>i);
        answer_type tmp=answer_type_e;
        ++pos;
        do{
            --pos;
            while((pos&1)&&pos>1) pos>>=1;
            answer_type&& t1=pushup(nodes[pos],tmp);
            if(!pred(t1)){
                while(pos<size_){
                    real_pushdown(pos),pos=pos<<1|1;
                    answer_type&& t2=pushup(nodes[pos],tmp);
                    if(pred(t2)) tmp=t2,--pos;
                }
                return pos-size_+1;
            }
            tmp=t1;
        }while((pos&-pos)!=pos);
        return 0;
    }//满足谓词的最小左边界
    template<class unary_predicate_for_answer_t> inline int max_right(int pos,unary_predicate_for_answer_t pred){
        assert(pos>=0&&pos<size_);
        if(!pred(nodes[pos+size_])) return pos-1;
        if(pos==size_-1) return size_-1;
        pos+=size_;
        if(!pred(nodes[pos])) return pos-size_-1;
        for(int i=height;i>=1;--i) real_pushdown(pos>>i);
        answer_type tmp=answer_type_e;
        do{
            while((pos&1)==0) pos>>=1;
            answer_type&& t1=pushup(tmp,nodes[pos]);
            if(!pred(t1)){
                while(pos<size_){
                    real_pushdown(pos),pos=pos<<1;
                    answer_type&& t2=pushup(tmp,nodes[pos]);
                    if(pred(t2)) tmp=t2,++pos;
                }
                return pos-size_-1;
            }
            tmp=t1,++pos;
        }while((pos&-pos)!=pos);
        return size_-1;
    }//满足谓词的最大右边界
};
#undef segtree_template

#define segtree binary_search_segment_tree

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
    int n,m;
    cin>>n>>m;
    vector<ll> in(n);
    for(auto &a:in) cin>>a;
    auto pushup=[](pair<ll,int> a,pair<ll,int> b) ->pair<ll,int> {return {a.first+b.first,a.second+b.second};};
    auto assign=[](pair<ll,int> a,ll b) ->pair<ll,int> {return {a.first+1ll*a.second*b,a.second};};
    plus<int> tmp;
    segtree<pair<ll,int>,ll,decltype(pushup),plus<int>,decltype(assign)> tr(in,{0,1},0,pushup,tmp,assign);
    while(m--){
        int op,x,y,k;
        cin>>op>>x>>y;
        if(op==1) cin>>k,tr.update(x-1,y-1,k);
        else cout<<tr.query(x-1,y-1).first<<'\n';
    }
    return 0;
}