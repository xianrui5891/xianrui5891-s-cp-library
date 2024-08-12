#include <bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define lll __int128
#define db double
#define gc getchar
#define pc putchar
#define rg register
using namespace std;

inline ll read(){
    ll t1=0,t2=1;
    char t3=gc();
    for(;!isdigit(t3);t3=gc()) if(t3=='-') t2=-1;
    for(;isdigit(t3);t3=gc()) t1=(t1<<1)+(t1<<3)+(t3^48);
    return t2*t1;
}

template<typename T>
inline void write(T t1){
    if(t1<0) t1=-t1,pc('-');
    if(t1>9) write(t1/10);
    pc(t1%10+'0');
}

const int msiz=20;
int n;

int tot,rt;
struct splaytree{
	int lc,rc,siz,fa,cnt,val;
	inline void get(int x){
		lc=rc=siz=fa=0,siz=cnt=1,val=x;
	}
	inline void clear(){
		lc=rc=siz=fa=cnt=val=0;
	}
};
splaytree tr[msiz];

#define ls tr[ind].lc
#define rs tr[ind].rc
#define faa tr[ind].fa
#define chk(ind) (tr[tr[ind].fa].rc==ind)

inline void pushup(int ind){
	tr[ind].siz=tr[ls].siz+tr[rs].siz+tr[ind].cnt;
}

inline int newnode(int x){
	tr[++tot].get(x);
	return tot;
}

inline void rotate(int ind){
	assert(faa!=0);
	int x=faa,y=tr[x].fa,k=chk(ind);
	chk(x)?(tr[y].rc=ind):(tr[y].lc=ind),faa=y;
	if(k) tr[x].rc=ls,tr[ls].fa=x,ls=x;
	else tr[x].lc=rs,tr[rs].fa=x,rs=x;
	tr[x].fa=ind,pushup(x),pushup(ind);
}

//inline void splay(int ind,int g){
//	if(!ind) return;
//	while(faa!=g){
//		int x=faa,y=tr[x].fa;
//		if(y!=g) ((tr[y].lc==x)^(tr[x].lc==ind))?rotate(ind):rotate(x);
//		rotate(ind);
//	}
//	if(!g) rt=ind;
//}

inline void splay(int ind,int g){
	if(!ind) return;
	for(rg int f=faa;f=faa,f!=g;rotate(ind))
		if(tr[f].fa!=g) rotate((chk(f)^chk(ind))?ind:f);
	if(!g) rt=ind;
}

inline void insert(int x){
	if(!rt) return rt=newnode(x),void();
	int ind=rt,f=0;
	while(ind&&tr[ind].val!=x) f=ind,ind=(x>tr[ind].val?rs:ls);
	if(ind) ++tr[ind].cnt;
	else{
		ind=newnode(x),faa=f;
		x>tr[f].val?(tr[f].rc=ind):(tr[f].lc=ind);
	}
	splay(ind,0);
}

inline int qryrnk(int k){
	int res=0,ind=rt;
	while(ind){
		if(k<tr[ind].val) ind=ls;
		else{
			res+=tr[ls].siz;
			if(k==tr[ind].val) return splay(ind,0),res+1;
			res+=tr[ind].cnt,ind=rs;
		}
	}
}

inline int qrykth(int k){
	int ind=rt;
	while(ind){
		if(k<=tr[ls].siz) ind=ls;
		else{
			k-=tr[ind].cnt+tr[ls].siz;
			if(k<=0) return splay(ind,0),tr[ind].val;
			ind=rs;
		}
	}
}

inline int qrypre(int k){
	int ind=tr[rt].lc;
	if(!ind) return tr[ind].val;
	while(rs) ind=rs;
	return splay(ind,0),ind;
}

inline int qrynxt(int k){
	int ind=tr[rt].rc;
	if(!ind) return tr[ind].val;
	while(ls) ind=ls;
	return splay(ind,0),ind;
}

inline void delet(int x){
	qryrnk(x);
	int ind=rt;
	if(tr[rt].cnt>1) return --tr[rt].cnt,pushup(rt),void();
	if(!ls&&!rs) return tr[ind].clear(),rt=0,void();
	if(!ls) return rt=rs,tr[rt].fa=0,tr[ind].clear(),void();
	if(!rs) return rt=ls,tr[rt].fa=0,tr[ind].clear(),void();
	int ty=qrypre(x);
	splay(ty,0),tr[rs].fa=ty,tr[ty].rc=rs,tr[ind].clear();
	pushup(ty);
}  

int main(){
	n=read();
	while(n--){
		int op=read(),x=read();
		if(op==1) insert(x);
		if(op==2) delet(x);
		if(op==3) write(qryrnk(x)),pc('\n');
		if(op==4) write(qrykth(x)),pc('\n');
		if(op==5) insert(x),write(tr[qrypre(x)].val),pc('\n'),delet(x);
		if(op==6) insert(x),write(tr[qrynxt(x)].val),pc('\n'),delet(x);
	}
	return 0;
}
