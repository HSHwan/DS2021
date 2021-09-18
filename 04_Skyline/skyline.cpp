#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
using namespace std;
#define FOR(i,b,n) for (int i = b; i < n; i++)
#define ST first
#define ND second
#define pb push_back
#define mp make_pair
typedef pair<int, int> pii;
typedef vector<int> vi;

struct QComp {
    bool operator()(pii A, pii B){return (A.ST <= B.ST);}
};
bool VComp (vi A, vi B){
    if(A[0] == B[0])    return A[1] >= B[1]; 
    return A[0] <= B[0];
}
int N, X_i, H_i; 
vector<vi> Bds;
vi Bt, Xy, Bd (3,0);
vector<pii> Sky;
priority_queue<pii, vector<pii>, QComp> MaxH;

void input(){
    cin >> N;
    Xy.resize(10000);
    FOR(i, 0, N){
        cin >> Bd[0] >> Bd[1] >> H_i;
        Bd[2] = i;
        Bds.pb(Bd);
        Bd[0] += H_i;
        Bds.pb(Bd);
    }
}

void solve(){
    sort(Bds.begin(),Bds.end(), VComp);
    vi nBd;
    Bt.resize(N+1);
    Sky.pb(mp(0,0));
    X_i = 0;
    MaxH.push(mp(0,N));
    FOR(i, 0, 2*N){
        nBd = Bds[i];
        Bt[nBd[2]]++;
        // 1 : Left Point, 2 : Right Point
        if(Bt[nBd[2]] == 1) MaxH.push(mp(nBd[1], nBd[2]));
        else{
            while(!MaxH.empty()){
                if (Bt[MaxH.top().ND] == 2)   MaxH.pop();
                else break;
            }
        }
        if(X_i < nBd[0] && nBd[1] >= MaxH.top().ST){
            if (!nBd[1]){
                continue;
            }
            else if (nBd[1] == MaxH.top().ST && Bt[nBd[2]] == 1){
                X_i = nBd[0];
                int num = MaxH.top().ND;
                MaxH.pop();
                if(nBd[1] > MaxH.top().ST){
                    Sky.pb(mp(X_i,MaxH.top().ST));
                    Sky.pb(mp(X_i,nBd[1]));
                }
                MaxH.push(mp(nBd[1],num));
            }
            else if (nBd[1] > MaxH.top().ST && Bt[nBd[2]] == 2){
                X_i = nBd[0];
                Sky.pb(mp(X_i,nBd[1]));
                Sky.pb(mp(X_i,MaxH.top().ST));
            }
            
        }
    }
}

void output(){
    for (int i = 0; i < Sky.size()-2; i+=2){
        cout << Sky[i+1].ST - Sky[i].ST << " ";
        cout << Sky[i+2].ND - Sky[i+1].ND << " ";
    }
}

int main(){
    input ();
    solve ();
    output();
}