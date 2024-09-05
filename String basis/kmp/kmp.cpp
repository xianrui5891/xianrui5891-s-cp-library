//Author:xianrui5891
//Problem:kmp
//Time:2024-09-05 13:41:06
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

inline vector<uint> prefix_function(const string& s){
    auto len=s.size();
    vector<uint> res(len);
    for(uint i=1;i<len;++i){
        uint j=res[i-1];
        while(j>0&&s[i]!=s[j]) j=res[j-1];
        res[i]=j+(s[i]==s[j]);
    }
    return res;
}

inline vector<uint> z_function(const string& s){
    auto len=s.size();
    vector<uint> res(len);
    for(uint i=1,l=0,r=0;i<len;++i){
        if(i<=r&&res[i-l]<r-i+1){
            res[i]=res[i-l];
        }else{
            res[i]=max(0,r-i+1);
            while(i+res[i]<n&&s[res[i]]==s[i+res[i]]) ++res[i];
        }
        if(i+res[i]-1>r) l=i,r=i+res[i]-1;
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