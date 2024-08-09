//Author:xianrui5891
//Problem:splay
//Time:2024-07-31 21:01:08
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
//c++ standard requirement: gnu++17,gnu++20
//it has bugs in gcc compiler when it comes to gnu++23.Maybe it could be sovled by applying the latest gnu_g++.

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
,class assignment_oper=default_assignment_oper<answer_type,input_type>
,class compary_predicate=less<answer_type>> class splay:
public enable_shared_from_this<splay<answer_type,input_type,pushup_oper,pushdown_oper,assignment_oper,compary_predicate>>{//less时默认升序
protected:
    #define tp splay<answer_type,input_type,pushup_oper,pushdown_oper,assignment_oper,compary_predicate>
    using enable_shared_from_this<tp>::weak_from_this;
    pushup_oper pushup;
    pushdown_oper pushdown;
    assignment_oper assign;
    compary_predicate comp;
    answer_type answer_type_e;
    input_type input_type_e;
public:
    struct node:enable_shared_from_this<node>{
        uint cnt,size;
        answer_type val;
        input_type tag;
        bool reverse_tag;
        shared_ptr<node> ls,rs;
        variant<weak_ptr<node>,weak_ptr<tp>> fa;
        using enable_shared_from_this<node>::shared_from_this;

        inline node():cnt(),size(),val(),tag(),reverse_tag(false),ls(nullptr),rs(nullptr),fa(){};
        inline node(const answer_type &_val_,const input_type &e,int _size_=1):cnt(_size_),size(_size_),reverse_tag(false){val=_val_,tag=e;}

        inline bool is_root()const{return get_if<weak_ptr<node>>(&fa)==nullptr;}
        inline shared_ptr<node> get_fa(){
            if(is_root()) return nullptr;
            return get<weak_ptr<node>>(fa).lock();
        }
        inline tp& fndtree(){
            if(!is_root()) return get<weak_ptr<node>>(fa).lock()->fndtree();
            else return *get<weak_ptr<tp>>(fa).lock();
        }
        inline shared_ptr<node> fndroot(){
            if(!is_root()) return get<weak_ptr<node>>(fa).lock()->fndtree();
            else return shared_from_this();
        }
    };
    shared_ptr<node> rt;
    inline shared_ptr<node> apply_newnode(const input_type &x){return make_shared<node>(node(x,input_type_e));}
    inline shared_ptr<node> apply_newnode(const input_type &x,const uint &_size_){return make_shared<node>(node(x,input_type_e,_size_));}
    constexpr inline uint get_size(){return (rt==nullptr)?0:rt->size;}
    constexpr inline uint get_size(const shared_ptr<node>& ind){return ind==nullptr?0:ind->size;}
    constexpr inline uint get_cnt(const shared_ptr<node>& ind){return ind==nullptr?0:ind->cnt;}
    constexpr inline void set_tree(){if(rt!=nullptr) rt->fa=weak_from_this();}
    constexpr inline void set_tree(const shared_ptr<node>& ind){if(ind!=nullptr) ind->fa=weak_from_this();}
    constexpr inline bool is_root(const shared_ptr<node>& ind){return ind==nullptr||ind->is_root();}
protected:
    function<bool(const answer_type &,const answer_type &)> is_equal=[&](const answer_type &x,const answer_type &y)->bool {return !(comp(x,y)^comp(y,x));};
    function<bool(const answer_type &,const answer_type &)> strong_comp=[&](const answer_type &x,const answer_type &y)->bool {return comp(x,y)&&(!is_equal(x,y));};
    function<bool(const answer_type &,const answer_type &)> weak_comp=[&](const answer_type &x,const answer_type &y)->bool {return comp(x,y)||is_equal(x,y);};

    inline void real_pushdown(const shared_ptr<node>& ind){
        if(ind->reverse_tag){
            swap(ind->ls,ind->rs);
            if(ind->ls!=nullptr) ind->ls->reverse_tag^=true;
            if(ind->rs!=nullptr) ind->rs->reverse_tag^=true;
            ind->reverse_tag=false;
        }
        if constexpr(!is_same_v<pushdown_oper,default_empty<answer_type>>)
            if(ind->tag!=input_type_e){
                if(ind->ls!=nullptr) ind->ls->val=assign(ind->ls->val,ind->tag),ind->ls->tag=pushdown(ind->ls->tag,ind->tag);
                if(ind->rs!=nullptr) ind->rs->val=assign(ind->rs->val,ind->tag),ind->rs->tag=pushdown(ind->rs->tag,ind->tag);
                ind->tag=input_type_e;
            }
    }
    inline void real_pushup(const shared_ptr<node>& ind){
        ind->size=ind->cnt;
        if(ind->ls!=nullptr){
            ind->size+=ind->ls->size,ind->ls->fa=ind;
            if constexpr(!is_same_v<pushup_oper,default_empty<answer_type>>) ind->val=pushup(ind->ls->val,ind->val);
        }
        if(ind->rs!=nullptr){
            ind->size+=ind->rs->size,ind->rs->fa=ind;
            if constexpr(!is_same_v<pushup_oper,default_empty<answer_type>>) ind->val=pushup(ind->val,ind->rs->val);
        }
    }
protected: 
    inline void rotate(const shared_ptr<node> &ind){
        assert(!is_root(ind));
        auto&& fa=get<0>(ind->fa).lock();
        real_pushdown(fa),real_pushdown(ind);
        if(ind==fa->ls) fa->ls=ind->rs,ind->rs=fa;
        else fa->rs=ind->ls,ind->ls=fa;
        if(!is_root(fa)){
            auto&& anc=get<0>(ind->fa).lock();
            if(anc->ls==fa) anc->ls=ind;
            else anc->rs=ind;
            ind->fa=anc;
        }
        pushup(fa),pushup(ind);
    }
    inline void real_splay(const shared_ptr<node> &ind,shared_ptr<node>& _rt_){
        if(ind==nullptr) return;
        for(;!isroot(ind);rotate(ind)){
            if(auto& fa=get<0>(ind->fa).lock();!is_root(fa)) 
                rotate(((get<0>(fa->fa).lock()->ls==fa)^(fa->ls==ind))?ind:fa);
        }
        _rt_=ind,set_tree(_rt_);
    }
    inline void real_splay(const shared_ptr<node> &ind,const shared_ptr<node>& goal,shared_ptr<node>& _rt_){
        if(ind==nullptr) return;
        for(;!is_root(ind)||get<0>(ind->fa).lock()!=goal;rotate(ind)){
            if(auto&& fa=get<0>(ind->fa).lock();!is_root(fa)) 
                rotate(((get<0>(fa->fa).lock()->ls==fa)^(fa->ls==ind))?ind:fa);
        }
        if(goal==nullptr) _rt_=ind,set_tree(_rt_);
    }
public:
    inline void real_splay_rt(const shared_ptr<node> &ind){real_splay(ind,rt);}
    inline void real_splay_rt(const shared_ptr<node> &ind,const shared_ptr<node>& goal){real_splay(ind,goal,rt);}
public:
    inline void clear(){rt.reset();}
    inline shared_ptr<node> get_rt(){return rt;}
    inline void set_answer_type_e(const answer_type& answer_type_e_){answer_type_e=answer_type_e_;}
    inline void set_input_type_e(const input_type& input_type_e_){input_type_e=input_type_e_;}
    inline void set_pushup_oper(pushup_oper _oper){pushup=_oper;}
    inline void set_pushdown_oper(pushdown_oper _oper){pushdown=_oper;}
    inline void set_assignment_oper(assignment_oper _oper){assign=_oper;}
    inline void set_compary_predicate(compary_predicate _pred){comp=_pred;}
    constexpr inline void build(const vector<input_type>& in){
        if(rt!=nullptr) clear();
        if(!in.size()) return;
        function<void(shared_ptr<node>&,const uint&,const uint&)> real_build=[&](shared_ptr<node>& ind,const uint& l,const uint& r)->void {
            if(l>r) return;
            uint mid=(l+r)>>1;
            ind=apply_newnode(assign(answer_type_e,in[mid]));
            real_build(ind->ls,l,mid-1),real_build(ind->rs,mid+1,r);
            real_pushup(ind);
            return;
        };
        real_build(rt,0,in.size()-1);
        set_tree();
    }

    constexpr explicit inline splay():rt(nullptr){}
    constexpr explicit inline splay(pushup_oper _oper1,pushdown_oper _oper2,assignment_oper _oper3,compary_predicate _pred,answer_type e1=answer_type(),input_type e2=input_type()):
        pushup(_oper1),pushdown(_oper2),assign(_oper3),comp(_pred),answer_type_e(e1),input_type_e(e2),rt(nullptr){};
    constexpr explicit inline splay(input_type val,answer_type e1=answer_type(),input_type e2=input_type()):
        answer_type_e(e1),input_type_e(e2){rt(new node(assign(e1,val),input_type_e)),set_tree();}
    constexpr explicit inline splay(const vector<input_type>& in,answer_type e1=answer_type(),input_type e2=input_type()):
        answer_type_e(e1),input_type_e(e2),rt(nullptr){build(in);}
    constexpr explicit inline splay(shared_ptr<node>&& in,answer_type e1=answer_type(),input_type e2=input_type()):
        answer_type_e(e1),input_type_e(e2),rt(exchange(in,nullptr)){set_tree();}
    constexpr explicit inline splay(input_type val,pushup_oper _oper1,pushdown_oper _oper2,assignment_oper _oper3,compary_predicate _pred,answer_type e1=answer_type(),input_type e2=input_type()):
        pushup(_oper1),pushdown(_oper2),assign(_oper3),comp(_pred),answer_type_e(e1),input_type_e(e2){rt(new node(assign(e1,val),input_type_e)),set_tree();}
    constexpr explicit inline splay(const vector<input_type>& in,pushup_oper _oper1,pushdown_oper _oper2,assignment_oper _oper3,compary_predicate _pred,answer_type e1=answer_type(),input_type e2=input_type()):
        pushup(_oper1),pushdown(_oper2),assign(_oper3),comp(_pred),answer_type_e(e1),input_type_e(e2),rt(nullptr){build(in);}
    constexpr explicit inline splay(shared_ptr<node>&& in,pushup_oper _oper1,pushdown_oper _oper2,assignment_oper _oper3,compary_predicate _pred,answer_type e1=answer_type(),input_type e2=input_type()):
        pushup(_oper1),pushdown(_oper2),assign(_oper3),comp(_pred),answer_type_e(e1),input_type_e(e2),rt(exchange(in,nullptr)){set_tree();}
    constexpr inline splay(tp& _tr)=delete;
    constexpr inline splay(tp&& _tr)=default;

    constexpr inline splay& operator=(tp& _tr)=delete;
    constexpr inline splay& operator=(tp&& _tr)=default;
    constexpr inline tp& operator=(shared_ptr<node>&& _rt){rt=exchange(_rt,nullptr),set_tree();return *this;}
protected:
    inline uint get_rk(const shared_ptr<node>& ind,shared_ptr<node> &_rt_){
        if(ind==nullptr) return 0;
        real_splay(ind,_rt_);
        return get_size(ind->ls)+1;
    }
    
    template<typename binary_pred_for_answer_t> 
    inline uint get_rk_by_pred(const answer_type& val,shared_ptr<node>& _rt_,const binary_pred_for_answer_t& pred){
        shared_ptr<node> lst,ind=_rt_;
        uint res=0;
        while(ind!=nullptr){
            if(pred(ind->val,val)){
                lst=ind;
                res+=get_size(ind->ls)+ind->cnt;
                ind=ind->rs;
            }
            else ind=ind->ls;
        }
        real_splay(lst,_rt_);
        return res+1;
    }//排名从1开始
    inline uint get_rk(const answer_type& val,const shared_ptr<node>& ind){return get_rk_by_pred(val,ind,strong_comp);}

    inline shared_ptr<node> get_ptr_by_rk(uint k,shared_ptr<node>& _rt_){
        if(k<1||k>get_size(_rt_)) return nullptr;
        auto ind=_rt_;
        while(ind!=nullptr){
            uint lsiz=get_size(ind->ls);
            if(lsiz<k&&k<=lsiz+ind->cnt) return real_splay(ind,_rt_),ind;
            else if(k<=lsiz) ind=ind->ls;
            else k-=lsiz+ind->cnt,ind=ind->rs;
        }
        return nullptr;
    }//排名从1开始

    inline shared_ptr<node> prev(uint k,shared_ptr<node>& _rt_){return get_ptr_by_rk(k-1,_rt_);}
    inline shared_ptr<node> prev(const shared_ptr<node>& ind,shared_ptr<node>& _rt_){return get_ptr_by_rk(get_rk(ind,_rt_)-1,_rt_);}
    inline shared_ptr<node> prev(const answer_type& val,shared_ptr<node>& _rt_){return get_ptr_by_rk(get_rk(val,_rt_)-1,_rt_);}

    inline shared_ptr<node> next(uint k,shared_ptr<node>& _rt_){return get_ptr_by_rk(k+1,_rt_);}
    inline shared_ptr<node> next(const shared_ptr<node>& ind,shared_ptr<node>& _rt_){return get_ptr_by_rk(get_rk(ind,_rt_)+ind->cnt,_rt_);}//ind只能是存在的
    inline shared_ptr<node> next(const answer_type& val,shared_ptr<node>& _rt_){return get_ptr_by_rk(get_rk_by_pred(val,weak_comp,_rt_),_rt_);}

    inline shared_ptr<node> select(const uint& l,const uint& r,shared_ptr<node>& _rt_){
        auto pre_rk=get_ptr_by_rk(l-1,_rt_),pre_ind=prev(get_ptr_by_rk(l,_rt_),_rt_);
        if(pre_rk!=pre_ind){
            uint _tmp_rk=get_rk(pre_rk);
            auto newone=apply_newnode(pre_rk->val,pre_rk->cnt+_tmp_rk-l);
            pre_rk->cnt=l-_tmp_rk;
            newone->rs=pre->rs;
            pre_rs=newone;
            pushup(newone),pushup(pre_rk);
        }//拆点,把pre_rk这个点拆成两个 大小分别为 l-_tmp_rk,pre_rk->cnt+_tmp_rk-l
        auto nex_rk=get_ptr_by_rk(r+1,_rt_),nex_ind=nex(get_ptr_by_rk(r,_rt_),_rt_);
        if(nex_rk!=nex_ind){
            uint _tmp_rk=get_rk(nex_rk);
            auto newone=apply_newnode(nex_rk->val,r-_tmp_rk+1);
            nex_rk_cnt=nex_rk->cnt+_tmp_rk-r-1;
            newone->ls=nex_rk->ls;
            nex_rk->ls=newone;
            pushup(newone),pushup(nex_rk);
        }//同理 分别为 r-_tmp_rk+1,nex_rk->cnt+_tmp_rk-r-1
        //注意下方splay的东西
        eal_splay(pre_rk,_rt_),real_splay(nex_rk,pre,_rt_);
        auto ind=_rt_;
        for(tot==(uint)(pre_rk!=nullptr)+(uint)(nex_rk!=nullptr);tot;--tot) ind=ind->rs;
        return ind;
    }
    inline shared_ptr<node> select(const answer_type& val,shared_ptr<node>& _rt_){
        auto pre=prev(val,_rt_),nex=next(val);
        real_splay(pre,_rt_),real_splay(nex,pre,_rt_);
        auto ind=_rt_;
        for(tot==(uint)(pre!=nullptr)+(uint)(nex!=nullptr);tot;--tot) ind=ind->rs;
        return ind;
    }

    inline void insert(uint k,const shared_ptr<node>& _ptr_,shared_ptr<node>& _rt_){
        assert(k>=1&&k<=get_size(_rt_));
        shared_ptr<node> lst,ind=_rt_;
        k--;
        bool flg;
        while(ind!=nullptr){
            uint lsiz=get_size(ind->ls);
            lst=ind;
            if(lsiz<k&&k<=lsiz+ind->cnt){
                real_splay(ind,_rt_);
                break;
            }
            else if(k<=lsiz) ind=ind->ls;
            else k-=lsiz+ind->cnt,ind=ind->rs;
        }
        if(!flg) lst->ls=_ptr_;
        else _ptr_->rs=lst->rs,lst->rs=_ptr_;
        real_splay(_ptr_,_rt_);
    }//插到k+1位置上，标号1开始
    inline void insert(const shared_ptr<node>& _ptr_,shared_ptr<node>& _rt_){//ind->val可能不存在
        shared_ptr<node> lst,ind=_rt_;
        while(ind!=nullptr){
            lst=ind;
            if(pred(ind->val,_ptr_->val)) ind=ind->rs;
            else ind=ind->ls;
        }
        if(strong_comp(lst->val)) lst->rs=_ptr_;
        else lst.ls=_ptr_;
        real_splay(_ptr_,_rt_);
    }
    inline void insert(uint k,const input_type& val,shared_ptr<node>& _rt_){insert(k,apply_newnode(assign(answer_type_e,val)),_rt_);}
    inline void insert(const input_type& val,shared_ptr<node>& _rt_){insert(apply_newnode(assign(answer_type_e,val)),_rt_);}

    inline void erase(const shared_ptr<node>& ind,shared_ptr<node>& _rt_){//必然存在
        auto pre=prev(ind,_rt_);
        if(pre==nullptr) _rt_=ind->rs,set_tree(_rt_);
        else pre->rs=ind->rs,real_pushup(pre);
    }//删除单个指针，无视内部数值
    inline void erase(uint k,shared_ptr<node>& _rt_){
        auto&& ind=get_ptr_by_rk(k,_rt_);
        ind->cnt--,ind->size--;
        if(ind->cnt&&!is_root(ind)) pushup(get<weak_ptr<node>>(ind->fa).lock());
        else erase(ind,_rt_);
    }//只删除排名为k的（1个val）
    inline void erase(const answer_type& val,shared_ptr<node>& _rt_){
        auto ind=select(val,_rt_)->get_fa();
        if(ind==nullptr) _rt_=nullptr;
        else ind->ls=nullptr,real_pushup(ind);
    }//相同的数值全删

    inline void reverse(const shared_ptr<node>& _rt_){if(_rt_!=nullptr) _rt_->reverse_tag^=true;}
    inline void reverse(const uint& l,const uint& r,shared_ptr<node>& _rt_){
        auto &ind=select(l,r,_rt_);
        ind->reverse_tag^=true;
    }
    inline void modify(const input_type& val,const shared_ptr<node>& _rt_){if(_rt_!=nullptr) _rt_->val=assign(_rt_->val,val),_rt_->tag=pushdown(_rt_->tag,val);}
    inline void modify(const uint& l,const uint& r,const input_type& val,shared_ptr<node>& _rt_){
        auto &ind=select(l,r,_rt_);
        ind->val=assign(_rt_->val,val),ind->tag=pushdown(ind->tag,val);
    }

    inline void to_vector(vector<answer_type> &x,const shared_ptr<node>& ind){
        if(ind==nullptr) return;
        real_pushdown(ind),to_vector(x,ind->ls),x.pb(ind->val),to_vector(x,ind->rs);
    }
public:
    inline uint get_rk(const shared_ptr<node>& ind){
        if(ind==nullptr) return 0;
        real_splay(ind,rt);
        return get_size(ind->ls)+1;
    }

    template<typename binary_pred_for_answer_t> 
    inline uint get_rk_by_pred(const answer_type& val,const binary_pred_for_answer_t& pred){return get_rk_by_pred(val,rt,pred);}//排名从1开始
    inline uint get_rk(const answer_type& val){return get_rk_by_pred(val,rt,strong_comp);}
    inline shared_ptr<node> get_ptr_by_rk(uint x){return get_ptr_by_rk(x,rt);}//排名从1开始

    inline shared_ptr<node> prev(uint k){return get_ptr_by_rk(k-1);}
    inline shared_ptr<node> prev(const shared_ptr<node>& ind){return get_ptr_by_rk(get_rk(ind)-1);}
    inline shared_ptr<node> prev(const answer_type& val){return get_ptr_by_rk(get_rk(val)-1);}

    inline shared_ptr<node> next(uint k){return get_ptr_by_rk(k+1);}
    inline shared_ptr<node> next(const shared_ptr<node>& ind){return get_ptr_by_rk(get_rk(ind)+ind->cnt);}
    inline shared_ptr<node> next(const answer_type& val){return get_ptr_by_rk(get_rk_by_pred(val,weak_comp));}

    inline void insert(uint k,const shared_ptr<node>& _ptr_){insert(k,ptr,rt);}
    inline void insert(const shared_ptr<node>& _ptr_){insert(ptr,rt);}
    inline void insert(uint k,const input_type& val){insert(k,apply_newnode(assign(answer_type_e,val)),rt);}
    inline void insert(const input_type& val){insert(apply_newnode(assign(answer_type_e,val)),rt);}

    inline void erase(const shared_ptr<node>& ind){erase(ind,rt);}
    inline void erase(uint k){erase(k,rt);}
    inline void erase(const answer_type& val){erase(val,rt);}

    inline void reverse(){if(rt!=nullptr) rt->reverse_tag^=true;}
    inline void reverse(const uint& l,const uint& r){reverse(l,r,rt);}
    inline void modify(const input_type& val){if(rt!=nullptr) rt->val=assign(rt->val,val),rt->tag=pushdown(rt->tag,val);}
    inline void modify(const uint& l,const uint& r,const input_type& val){modify(l,r,val,rt);}
    
    inline pair<tp,tp> split(){
        
    }
    inline tp& merge(){

    }
    template<typename ...arg> inline tp& merge(tp&& _tree_,arg&& ...tree_2){merge(forward<tp>(_tree_)),merge(forward<tp>(tree_2)...); return *this;}

    inline void to_vector(vector<answer_type> &x){to_vector(x,rt);}
protected:
    #undef tp
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