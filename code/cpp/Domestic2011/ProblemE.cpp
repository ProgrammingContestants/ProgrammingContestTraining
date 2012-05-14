#include <vector>
#include <iostream>
#include <set>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pii;
#define FOR(i,a,n) for(int i=a;i<n;++i)
#define REP(i,n) FOR(i,0,n)
 
int h,w,s,total;
pii dp[32][32][32][32];
pii search(int x1,int y1,int x2,int y2,vvi &u){
    if(dp[x1][y1][x2][y2].first>0){
        return dp[x1][y1][x2][y2];
    }
    if(x1==x2&&y1==y2){
        return make_pair(1,total-u[x1][y1]);
    }
    int t=0;
    FOR(i,x1,x2+1)FOR(j,y1,y2+1)
        t+=u[i][j];
    pii best=make_pair(1,total-t);
    FOR(i,x1,x2){
        pii p1=search(x1,y1,i,y2,u),p2=search(i+1,y1,x2,y2,u);
        int ff=p1.first+p2.first,ss=max(p1.second,p2.second);
        if(ss>s)continue;
        if(best.first<ff||(best.first==ff&&best.second>ss)){
            best.first=ff;
            best.second=ss;
        }
    }
    FOR(i,y1,y2){
        pii p1=search(x1,y1,x2,i,u),p2=search(x1,i+1,x2,y2,u);
        int ff=p1.first+p2.first,ss=max(p1.second,p2.second);
        if(ss>s)continue;
        if(best.first<ff||(best.first==ff&&best.second>ss)){
            best.first=ff;
            best.second=ss;
        }
    }
    return dp[x1][y1][x2][y2]=best;
}
int main(){
    while(cin>>h>>w>>s,h){
        vvi u(w,vi(h,0));
        REP(i,h){
            REP(j,w){
                cin>>u[j][i];
            }
        }
        REP(i,32)REP(j,32)REP(k,32)REP(l,32)
            dp[i][j][k][l]=make_pair(0,0);
        total=0;
        REP(i,w)REP(j,h)
            total+=u[i][j];
        pii p=search(0,0,w-1,h-1,u);
        cout<<p.first<<" "<<s-p.second<<endl;
    }
}