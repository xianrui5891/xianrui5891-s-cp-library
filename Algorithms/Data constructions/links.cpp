#include <bits/stdc++.h>
#define rg register
using namespace std;

const int stp=500000;
int fa[500005],ord[500005];

int main(){
	//freopen("data.in","w",stdout);
    srand(time(0));
    int n=stp,m=500000;
    for(rg int i=1;i<=n;++i)fa[i]=i;
    int root=rand()%n+1;
    for(rg int i=3;i<=n;i++) ord[i]=i;
	random_shuffle(ord+3,ord+n+1);
    cout<<n<<' '<<m<<'\n';
    cout<<1<<' '<<2<<' '<<5000000<<'\n';
    for(rg int i=3;i<=n;++i){
        cout<<ord[i]-1<<' '<<ord[i]<<' '<<1<<'\n';
    }
    for(rg int i=1;i<=m;++i) cout<<1<<' '<<stp<<' '<<stp<<'\n';
    //fclose(stdout);
    return 0;
}
