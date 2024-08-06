#include <bits/stdc++.h>
#define rg register
using namespace std;

const int msiz=5e5+15,stp=499990,stp2=20,stp3=10000;
int fa[msiz],ord[msiz],lst[200],root;

int main(){
	//freopen("data.in","w",stdout);
	srand(time(0));
    int n=rand()%10+stp+1,m=rand()%10+stp+1,hav=rand()%min(n,stp2-3)+3;
    cout<<n<<' '<<m<<'\n';
    int root=rand()%n+1;
    for(rg int i=1;i<=hav;++i) lst[i]=root;
	for(rg int i=1;i<=n;i++) ord[i]=i;
	random_shuffle(ord+1,ord+n+1);
	for(rg int i=1;i<=n;i++){
		if(ord[i]==root) continue;
		int t1=rand()%hav+1;
		fa[ord[i]]=lst[t1],lst[t1]=ord[i];
	}
	random_shuffle(ord+1,ord+n+1);
    for(rg int i=1;i<=n;++i) if(root!=ord[i]) cout<<ord[i]<<' '<<fa[ord[i]]<<' '<<rand()%stp3+1<<'\n';
    for(rg int i=1;i<=m;++i) cout<<rand()%n+1<<' '<<rand()%n+1<<' '<<rand()%n+1<<'\n';
    //fclose(stdout);
    return 0;
} 
