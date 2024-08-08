//Author:xianrui5891
//Problem:fhq_treap
//Time:2024-07-17 10:49:27
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
,class compary_predicate=less<answer_type>> class fhq_treap:
public enable_shared_from_this<fhq_treap<answer_type,input_type,pushup_oper,pushdown_oper,assignment_oper,compary_predicate>>{//less时默认升序
protected:
    #define tp fhq_treap<answer_type,input_type,pushup_oper,pushdown_oper,assignment_oper,compary_predicate> 
    pushup_oper pushup;
    pushdown_oper pushdown;
    assignment_oper assign;
    compary_predicate comp;
    answer_type answer_type_e;
    input_type input_type_e;
    mt19937 rnd;
    using enable_shared_from_this<tp>::weak_from_this;
public:
    struct node:enable_shared_from_this<node>{
        int key;
        uint cnt,size;
        answer_type val;
        input_type tag;
        bool reverse_tag;
        shared_ptr<node> ls,rs;
        variant<weak_ptr<node>,weak_ptr<tp>> fa;
        using enable_shared_from_this<node>::shared_from_this;

        inline node():key(),cnt(),size(),val(),tag(),reverse_tag(false),ls(nullptr),rs(nullptr),fa(){};
        inline node(const answer_type &_val_,const input_type &e,int _key,int _size_=1):cnt(_size_),size(_size_),reverse_tag(false){key=_key,val=_val_,tag=e;}

        inline bool is_root(){return get_if<weak_ptr<node>>(&fa)==nullptr;}
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
    inline shared_ptr<node> apply_newnode(const answer_type &x){return make_shared<node>(node(x,input_type_e,rnd()));}
    inline shared_ptr<node> apply_newnode(const answer_type &x,const uint &_size_){return make_shared<node>(node(x,input_type_e,rnd(),_size_));}
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
    inline pair<shared_ptr<node>,shared_ptr<node>> split_by_rk(const uint& k,const shared_ptr<node>& ind){
        if(ind==nullptr) return make_pair<shared_ptr<node>,shared_ptr<node>>(nullptr,nullptr);
        real_pushdown(ind);
        uint lsiz=get_size(ind->ls);
        if (k<=0) return {nullptr,ind}; 
        else if(lsiz>=k){
            auto [x,y]=split_by_rk(k,ind->ls);
            ind->ls=y,real_pushup(ind);
            return {x,ind};
        }else if(lsiz+ind->cnt>k){
            auto ltree=apply_newnode(ind->val,k-lsiz);
            ind->cnt=ind->cnt+lsiz-k;
            ltree->ls=ind->ls,ind->ls=nullptr;
            real_pushup(ltree),real_pushup(ind);
            return {ltree,ind};
        }else if(lsiz+ind->cnt==k){
            auto rtree=ind->rs;
            ind->rs=nullptr,real_pushup(ind);
            return {ind,rtree};
        }else if(ind->size>k){
            auto [x,y]=split_by_rk(k-lsiz-ind->cnt,ind->rs);
            ind->rs=x,real_pushup(ind);
            return make_pair(ind,y);
        }else return {ind,nullptr};
    }//将小于等于k和大于k的分到两个子树
    template<typename binary_pred_for_answer_t> 
    inline pair<shared_ptr<node>,shared_ptr<node>> split_by_pred(const answer_type& _val_,const shared_ptr<node>& ind,const binary_pred_for_answer_t& pred){
        //pred判断 ind->val值在前，_val_值在后，满足在左，不满足在右
        if(ind==nullptr) return make_pair<shared_ptr<node>,shared_ptr<node>>(nullptr,nullptr);
        real_pushdown(ind);
        if(pred(ind->val,_val_)){
            auto [x,y]=split_by_pred(_val_,ind->rs,pred);
            ind->rs=x,real_pushup(ind);
            return {ind,y};
        }else{
            auto [x,y]=split_by_pred(_val_,ind->ls,pred);
            ind->ls=y,real_pushup(ind);
            return {x,ind};
        }
    }//将满足谓词的放到左边，不满足谓词的放右边

    inline shared_ptr<node> merge(const shared_ptr<node>& inx,const shared_ptr<node>& iny){
        if(inx==nullptr&&iny==nullptr) return nullptr;
        else if(inx==nullptr) return iny;
        else if(iny==nullptr) return inx;
        if(inx->key>iny->key){
            real_pushdown(inx),inx->rs=merge(inx->rs,iny),real_pushup(inx);
            return inx;
        }else{
            real_pushdown(iny),iny->ls=merge(inx,iny->ls),real_pushup(iny);
            return iny;
        }
    }//merge的主inx是左，iny是右,key大的在上
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
        stack<shared_ptr<node>> s;
        for(int x:in){
            shared_ptr<node> ptr1(new node(assign(answer_type_e,x),input_type_e,rnd())),ptr2(nullptr);
            while(!s.empty()&&s.top()->key<ptr1->key) ptr2=s.top(),s.pop(),real_pushup(ptr2);//key大的在上
            ptr1->ls=ptr2;
            if(ptr2!=nullptr) ptr2->fa=ptr1;
            if(!s.empty()) s.top()->rs=ptr1,ptr1->fa=s.top();
            s.push(ptr1);
            if(s.size()==1) rt=s.top();
        }
        while(!s.empty()) real_pushup(s.top()),s.pop();
        set_tree();
    }//key大的在上
    constexpr explicit inline fhq_treap():rnd(time(0)),rt(nullptr){}
    constexpr explicit inline fhq_treap(pushup_oper _oper1,pushdown_oper _oper2,assignment_oper _oper3,compary_predicate _pred,answer_type e1=answer_type(),input_type e2=input_type()):
        pushup(_oper1),pushdown(_oper2),assign(_oper3),comp(_pred),answer_type_e(e1),input_type_e(e2),rnd(time(0)),rt(nullptr){};
    constexpr explicit inline fhq_treap(input_type val,answer_type e1=answer_type(),input_type e2=input_type()):
        answer_type_e(e1),input_type_e(e2),rnd(time(0)){rt(new node(assign(e1,val),input_type_e,rnd())),set_tree();}
    constexpr explicit inline fhq_treap(const vector<input_type>& in,answer_type e1=answer_type(),input_type e2=input_type()):
        answer_type_e(e1),input_type_e(e2),rnd(time(0)),rt(nullptr){build(in);}
    constexpr explicit inline fhq_treap(shared_ptr<node>&& in,answer_type e1=answer_type(),input_type e2=input_type()):
        answer_type_e(e1),input_type_e(e2),rnd(time(0)),rt(exchange(in,nullptr)){set_tree();}
    constexpr explicit inline fhq_treap(input_type val,pushup_oper _oper1,pushdown_oper _oper2,assignment_oper _oper3,compary_predicate _pred,answer_type e1=answer_type(),input_type e2=input_type()):
        pushup(_oper1),pushdown(_oper2),assign(_oper3),comp(_pred),answer_type_e(e1),input_type_e(e2),rnd(time(0)){rt(new node(assign(e1,val),input_type_e,rnd())),set_tree();}
    constexpr explicit inline fhq_treap(const vector<input_type>& in,pushup_oper _oper1,pushdown_oper _oper2,assignment_oper _oper3,compary_predicate _pred,answer_type e1=answer_type(),input_type e2=input_type()):
        pushup(_oper1),pushdown(_oper2),assign(_oper3),comp(_pred),answer_type_e(e1),input_type_e(e2),rnd(time(0)),rt(nullptr){build(in);}
    constexpr explicit inline fhq_treap(shared_ptr<node>&& in,pushup_oper _oper1,pushdown_oper _oper2,assignment_oper _oper3,compary_predicate _pred,answer_type e1=answer_type(),input_type e2=input_type()):
        pushup(_oper1),pushdown(_oper2),assign(_oper3),comp(_pred),answer_type_e(e1),input_type_e(e2),rnd(time(0)),rt(exchange(in,nullptr)){set_tree();}
    constexpr inline fhq_treap(tp& _tr)=delete;
    constexpr inline fhq_treap(tp&& _tr)=default;

    constexpr inline fhq_treap& operator=(tp& _tr)=delete;
    constexpr inline fhq_treap& operator=(tp&& _tr)=default;
    constexpr inline tp& operator=(shared_ptr<node>&& _rt){rt=exchange(_rt,nullptr),set_tree();return *this;}
protected:
    template<typename binary_pred_for_answer_t> 
    inline uint get_rk_by_pred(const answer_type& val,shared_ptr<node> ind,const binary_pred_for_answer_t& pred){
        uint res=0;
        while(ind!=nullptr){
            if(pred(ind->val,val)) res+=get_size(ind->ls)+ind->cnt,ind=ind->rs;
            else ind=ind->ls;
        }
        return res+1;
    }//排名从1开始
    inline uint get_rk(const answer_type& val,const shared_ptr<node>& ind){return get_rk_by_pred(val,ind,strong_comp);}

    inline shared_ptr<node> get_ptr_by_rk(uint k,shared_ptr<node> ind){
        if(k<1||k>get_size(ind)) return nullptr;
        while(ind!=nullptr){
            uint lsiz=get_size(ind->ls);
            if(lsiz<k&&k<=lsiz+ind->cnt) return ind;
            else if(k<=lsiz) ind=ind->ls;
            else k-=lsiz+ind->cnt,ind=ind->rs;
        }
        return nullptr;
    }//排名从1开始

    inline shared_ptr<node> prev(uint k,const shared_ptr<node>& _rt_){return get_ptr_by_rk(k-1,_rt_);}
    inline shared_ptr<node> prev(const answer_type& val,const shared_ptr<node>& _rt_){return get_ptr_by_rk(get_rk(val,_rt_)-1,_rt_);}
    inline shared_ptr<node> next(uint k,const shared_ptr<node>& _rt_){return get_ptr_by_rk(k+1,_rt_);}
    inline shared_ptr<node> next(const answer_type& val,const shared_ptr<node>& _rt_){return get_ptr_by_rk(get_rk_by_pred(val,weak_comp,_rt_),_rt_);}

    inline void insert(const shared_ptr<node>& ind,shared_ptr<node>& _rt_){//ind->val可能不存在
        auto&& [x,y]=split_by_pred(ind->val,_rt_,strong_comp);
        _rt_=merge(merge(x,ind),y),set_tree(_rt_);
    }
    inline void insert(uint k,const shared_ptr<node>& ind,shared_ptr<node>& _rt_){
        auto&& [x,y]=split_by_rk(k,_rt_);
        _rt_=merge(merge(x,ind),y),set_tree(_rt_);
    }//插到k+1位置上，标号1开始
    inline void insert(const input_type& val,shared_ptr<node>& _rt_){insert(apply_newnode(assign(answer_type_e,val)),_rt_);}
    inline void insert(uint k,const input_type& val,shared_ptr<node>& _rt_){insert(k,apply_newnode(assign(answer_type_e,val)),_rt_);}

    inline void erase(const shared_ptr<node>& ind,shared_ptr<node>& _rt_){//必然存在
        uint rk_=get_rk(ind);
        auto&& [x,t]=split_by_rk(rk_-1,_rt_);
        auto&& [y,z]=split_by_rk(ind->cnt,t);
        _rt_=merge(x,z),set_tree(_rt_);
    }//删除相关的指针，哪怕有多个
    inline void erase(const uint& k,shared_ptr<node>& _rt_){
        auto&& [x,t]=split_by_rk(k-1,_rt_);
        auto&& [y,z]=split_by_rk(1,t);
        _rt_=merge(x,z),set_tree(_rt_);
    }//只删除排名为k的（1个val）
    inline void erase(const answer_type& val,shared_ptr<node>& _rt_){
        auto&& [x,t]=split_by_pred(val,_rt_,strong_comp);
        auto&& [y,z]=split_by_pred(val,t,weak_comp);
        _rt_=merge(x,z),set_tree(_rt_);
    }//相同的数值全删

    inline void reverse(const shared_ptr<node>& _rt_){if(_rt_!=nullptr) _rt_->reverse_tag^=true;}
    inline void reverse(const uint& l,const uint& r,shared_ptr<node>& _rt_){
        auto&& [x,t]=split_by_rk(l-1,_rt_);
        auto&& [y,z]=split_by_rk(r-l+1,t);
        if(y!=nullptr) y->reverse_tag^=true;
        _rt_=merge(x,merge(y,z)),set_tree(_rt_);
    }

    inline void modify(const input_type& val,const shared_ptr<node>& _rt_){if(_rt_!=nullptr) _rt_->val=assign(_rt_->val,val),_rt_->tag=pushdown(_rt_->tag,val);}
    inline void modify(const uint& l,const uint& r,const input_type& val,shared_ptr<node>& _rt_){
        auto&& [x,t]=split_by_rk(l-1,_rt_);
        auto&& [y,z]=split_by_rk(r-l+1,t);
        if(y!=nullptr) y->val=assign(y->val,val),y->tag=pushdown(y->tag,val);
        _rt_=merge(x,merge(y,z)),set_tree(_rt_);
    }

    inline void to_vector(vector<answer_type> &x,const shared_ptr<node>& ind){
        if(ind==nullptr) return;
        real_pushdown(ind),to_vector(x,ind->ls),x.pb(ind->val),to_vector(x,ind->rs);
    } 
public:
    inline pair<tp,tp> split_by_rk(const uint& k){
        auto&& [x,y]=split_by_rk(k,rt);
        rt=nullptr;
        return {tp(move(x),pushup,pushdown,assign,comp,answer_type_e,input_type_e),
                    tp(move(y),pushup,pushdown,assign,comp,answer_type_e,input_type_e)};
    }//将小于等于k和大于k的分到两个子树
    inline pair<tp,tp> split_lower_bound(const answer_type& val){
        auto&& [x,y]=split_by_pred(val,rt,strong_comp);
        rt=nullptr;
        return {tp(move(x),pushup,pushdown,assign,comp,answer_type_e,input_type_e),
                    tp(move(y),pushup,pushdown,assign,comp,answer_type_e,input_type_e)};
    }//小于此值的在左，大于等于此值的在右
    inline pair<tp,tp> split_upper_bound(const answer_type& val){
        auto&& [x,y]=split_by_pred(val,rt,weak_comp);
        rt=nullptr;
        return {tp(move(x),pushup,pushdown,assign,comp,answer_type_e,input_type_e),
                    tp(move(y),pushup,pushdown,assign,comp,answer_type_e,input_type_e)};
    }//小于等于此值的在左，大于此值的在右
    template<typename binary_pred_for_answer_t> 
    inline pair<tp,tp> split_by_pred(const answer_type& val,const binary_pred_for_answer_t& pred){
        auto&& [x,y]=split_by_pred(val,rt,pred);
        rt=nullptr;
        return {tp(move(x),pushup,pushdown,assign,comp,answer_type_e,input_type_e),
                    tp(move(y),pushup,pushdown,assign,comp,answer_type_e,input_type_e)};
    }//满足谓词pred(ind->val,val)关系的在左，否则在右

    inline tp& merge(tp&& _tree_){rt=merge(rt,_tree_.rt),set_tree();return *this;}//主在左，辅在右
    template<typename ...arg> inline tp& merge(tp&& _tree_,arg&& ...tree_2){merge(forward<tp>(_tree_)),merge(forward<tp>(tree_2)...);return *this;}
    inline tp& merge_with_order(tp&& _tree_){
        if(!comp(rt->val,_tree_.rt->val)) swap(rt,_tree_.rt);
        rt=merge(rt,_tree_.rt),set_tree();
        return *this;
    }

    inline uint get_rk(shared_ptr<node> ind){
        if(ind==nullptr) return 0;
        uint res=get_size(ind->ls)+1;
        while(!ind->is_root()){
            auto&& fa_ptr=get<weak_ptr<node>>(ind->fa).lock();
            if(fa_ptr->rs==ind) res+=(fa_ptr->size)-(ind->size);
            ind=fa_ptr;
        }
        return res;
    }

    template<typename binary_pred_for_answer_t> 
    inline uint get_rk_by_pred(const answer_type& val,const binary_pred_for_answer_t& pred){return get_rk_by_pred(val,rt,pred);}//排名从1开始
    inline uint get_rk(const answer_type& val){return get_rk_by_pred(val,rt,strong_comp);}
    inline shared_ptr<node> get_ptr_by_rk(uint x){return get_ptr_by_rk(x,rt);}//排名从1开始

    inline shared_ptr<node> prev(uint k){return get_ptr_by_rk(k-1);}
    inline shared_ptr<node> prev(const shared_ptr<node>& ind){return get_ptr_by_rk(get_rk(ind)-1);}
    inline shared_ptr<node> prev(const answer_type& val){return get_ptr_by_rk(get_rk(val)-1);}

    inline shared_ptr<node> next(uint k){return get_ptr_by_rk(k+1);}
    inline shared_ptr<node> next(const shared_ptr<node>& ind){return get_ptr_by_rk(get_rk(ind)+ind->cnt);}//ind只能是存在的
    inline shared_ptr<node> next(const answer_type& val){return get_ptr_by_rk(get_rk_by_pred(val,weak_comp));}

    inline void insert(const shared_ptr<node>& ind){insert(ind,rt);}
    inline void insert(uint k,const shared_ptr<node>& ind){insert(k,ind,rt);}
    inline void insert(const input_type& val){insert(apply_newnode(assign(answer_type_e,val)),rt);}
    inline void insert(uint k,const input_type& val){insert(k,apply_newnode(assign(answer_type_e,val)),rt);}

    inline void erase(const shared_ptr<node>& ind){erase(ind,rt);}
    inline void erase(const uint& k){erase(k,rt);}
    inline void erase(const answer_type& val){erase(val,rt);}

    inline void reverse(){if(rt!=nullptr) rt->reverse_tag^=true;}
    inline void reverse(const uint& l,const uint& r){reverse(l,r,rt);}

    inline void modify(const input_type& val){if(rt!=nullptr) rt->val=assign(rt->val,val),rt->tag=pushdown(rt->tag,val);}
    inline void modify(const uint& l,const uint& r,const input_type& val){modify(l,r,val,rt);}

    inline void to_vector(vector<answer_type> &x){to_vector(x,rt);}
    // inline ~fhq_treap(){
    //     cout<<this<<'\n';
    //     vector<answer_type> tmp;
    //     to_vector(tmp);
    //     for(answer_type& x:tmp) cout<<x<<' ';
    //     cout<<'\n';
    //     cout<<"has deleted\n";
    //     cout<<"________________________________________________________\n";
    // }
protected:
    #undef tp
};

// int main(){
//     //freopen("3391_4.in","r",stdin),freopen("1.ans","w",stdout);
//     int n,m;
//     cin>>n>>m;
//     vector<int> a(n,0);
//     iota(all(a),1);
//     auto assign=[]([[maybe_unused]]int x,int y){return y;};
//     default_empty<int> tmp1;
//     less<int> tmp2;
//     fhq_treap<int,int,default_empty<int>,default_empty<int>,decltype(assign)> tree(a,tmp1,tmp1,assign,tmp2);
//     for(int i=1;i<=m;++i){
//         int l,r;
//         cin>>l>>r;
//         auto&& [x,t]=tree.split_by_rk(l-1);
//         auto&& [y,z]=t.split_by_rk(r-l+1);
//         y.reverse();
//         tree.merge(move(x),move(y),move(z));
//     }
//     vector<int> res;
//     tree.to_vector(res);
//     for(int& x:res) cout<<x<<' ';
//     cout<<'\n';
//     return 0;
// }

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
    int n;
    cin>>n;
    auto assign=[]([[maybe_unused]]int x,int y){return y;};
    default_empty<int> tmp1;
    less<int> tmp2;
    fhq_treap<int,int,default_empty<int>,default_empty<int>,decltype(assign)> fhq_tr(tmp1,tmp1,assign,tmp2);
    while(n--){
        int opt,x;
        cin>>opt>>x;
        if(opt==1) fhq_tr.insert(x);
        else if(opt==2) fhq_tr.erase(fhq_tr.get_rk(x));
        else if(opt==3){
            cout<<fhq_tr.get_rk(x)<<'\n';
        }else if(opt==4){
            cout<<fhq_tr.get_ptr_by_rk(x)->val<<'\n';
        }else if(opt==5){
            cout<<fhq_tr.prev(x)->val<<'\n';
        }else{
            cout<<fhq_tr.next(x)->val<<'\n';
        }
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