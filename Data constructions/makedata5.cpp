#include <bits/stdc++.h>
#define rg register
using namespace std;

const int msiz=5e5+15,stp=499990,stp2=20,stp3=100000000;
int fa[msiz],ord[msiz],lst[100];
bool tag[msiz];

int main(){
	//freopen("data.in","w",stdout);
	srand(time(0));
    int n=rand()%10+stp+1,m=rand()%10+stp+1,hav=rand()%min(n,stp2-3)+3;
    cout<<n<<' '<<m<<'\n';
    for(rg int i=1;i<=n;++i) ord[i]=i;
    random_shuffle(ord+1,ord+n+1);
    for(rg int i=1;i<hav;++i) tag[ord[i]]=1;
    int root=ord[rand()%(n-hav)+hav+1],cnt=1;
    random_shuffle(ord+1,ord+n+1);
    lst[1]=root;
    for(rg int i=1;i<=n;++i){
    	if(ord[i]==root) continue;
    	if(cnt==1) fa[ord[i]]=lst[1],lst[1]=ord[i];
    	else{
    		int at=rand()%cnt+1;
    		fa[ord[i]]=lst[at],lst[at]=ord[i];
		}
    	if(tag[ord[i]]==1) lst[++cnt]=ord[i];
	}
	random_shuffle(ord+1,ord+n+1);
	for(rg int i=1;i<=n;++i) if(root!=ord[i]) cout<<ord[i]<<' '<<fa[ord[i]]<<' '<<rand()%stp3+1<<'\n';
    for(rg int i=1;i<=m;++i) cout<<rand()%n+1<<' '<<rand()%n+1<<' '<<rand()%n+1<<'\n';
	//fclose(stdout);
    return 0;
}
