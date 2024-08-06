#include <bits/stdc++.h>
#define rg register
using namespace std;

const int stp=5,stp2=10;
int fa[500005],f[500005],ord[500005];

int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}

int main(){
	//freopen("data.in","w",stdout);
    srand(time(0));
    int n=rand()%10+stp+1,m=rand()%10+stp+1;
    for(rg int i=1;i<=n;++i)fa[i]=i;
    int root=rand()%n+1;
    cout<<n<<' '<<m<<'\n';
    for(rg int i=1;i<=n;++i){
        if(i==root) continue;
        int father;
        do{
			father=rand()%n+1;
		}while(find(i)==find(father));
        f[i]=father,fa[find(i)]=find(father);
    }
    for(rg int i=1;i<=n;i++) ord[i]=i;
	random_shuffle(ord+1,ord+n+1);
    for(rg int i=1;i<=n;++i) if(root!=ord[i]) cout<<ord[i]<<' '<<f[ord[i]];
    //fclose(stdout);
    return 0;
}
