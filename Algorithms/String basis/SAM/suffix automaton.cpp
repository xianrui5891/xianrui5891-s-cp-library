//Author:xianrui5891
//Problem:suffix automaton
//Time:2022-11-25 13:18:50
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

const int msiz=1e5+15;

template<int sz> suffix_automaton{
    int sz1,lst;
    struct node{
        
    }
}

int main(){
    
    return 0;
}