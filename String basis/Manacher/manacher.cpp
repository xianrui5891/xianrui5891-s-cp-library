//Author:xianrui5891
//Problem:manacher
//Time:2024-09-05 15:08:37
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

inline string manacher_pretreatment(const string& s){
    auto len=s.size();
    string res(len<<1|1);
    for(int i=0;i<len;++i) res[i<<1]='#',res[i<<1|1]=s[i];
    res[len<<1]='#';
    return res;
}

inline vector<uint> palindrome_radius(const string& s){
    auto len=s.size();
    auto check=[&]->bool {
        auto len=s.size();
        for(int i=0;i<len;i+=2) if(s[i]!='#') return false;
        for(int i=1;i<len;i+=2) if(s[i]=='#') return false;
        return true;
    };
    assert(check());
    vector<uint> res(len);
    for(uint i=1,maxright=0,pos=0;i<len-1;++i){
        res[i]=maxright>i?min(maxright-i,res[(pos<<1)-i]):1;
        while((res[i]<len)&&(i-res[i]>=0)&&(i+res[i]<len)&&s[i+res[i]]==s[i-res[i]]) ++res[i];
        if(i+res[i]>max_right) pos=i,maxright=i+res[i];
    }
    return res;
}

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