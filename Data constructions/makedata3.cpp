#include <bits/stdc++.h>
#define rg register
using namespace std;

const int msiz=5e5+15,stp=5,stp2=10;
int num[msiz],ord[msiz];

int main(){
	//freopen("data.in","w",stdout);
	srand(time(0));
    int n=rand()%10+stp+1,m=rand()%10+stp+1;
    cout<<n<<' '<<m<<'\n';
	for(rg int i=1;i<=n;i++) num[i]=i;
	for(rg int i=2;i<=n;i++) ord[i]=i;
	random_shuffle(ord+2,ord+n+1);
	random_shuffle(num+1,num+n+1);
    for(rg int i=2;i<=n;++i) cout<<num[ord[i]]<<' '<<num[ord[i]-1]<<' '<<rand()%stp2+1<<'\n';
    for(rg int i=1;i<=m;++i) cout<<rand()%n+1<<' '<<rand()%n+1<<' '<<rand()%n+1<<'\n';
    //fclose(stdout);
    return 0;
} 
