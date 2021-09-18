#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
#define FOR(i,b,n) for (int i = b; i < n; i++)
#define ST first
#define ND second
#define pb push_back
#define mp make_pair
using namespace std;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct QComp {
    bool operator()(pii A, pii B){return (A.ST < B.ST);}
};
bool VComp (vi A, vi B){
    if(A[0] == B[0])    return A[1] > B[1]; 
    return A[0] < B[0];
}
int N, V = 0, H_i;
vector<vi> Bds;
vi Sky, Bt, Bd (3,0);
priority_queue<pii, vector<pii>, QComp> MaxH;

void input(){
    cin >> N;
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
    vi pBd(Bds[0]), nBd;
    Bt.resize(N+1); Bt[pBd[2]]++;
    Sky.pb(pBd[0]); V += pBd[1];
    MaxH.push(mp(0,N));
    FOR(i, 1, 2*N){
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
        if(Bt[pBd[2]] == Bt[nBd[2]] && Bt[pBd[2]] == 1){     // Case 1 : [[ or ]]
            if(pBd[0] == nBd[0] && (pBd[1] < nBd[1]))
                V  += nBd[1]-pBd[1];
            else if(Bt[pBd[2]] == 1 && (pBd[1] < nBd[1])){
                Sky.pb(V);
                Sky.pb(nBd[0]-pBd[0]);
                V = nBd[1]-pBd[1];
            }
            pBd = nBd;
        }
        else if(Bt[pBd[2]] > Bt[nBd[2]]){ // Case 2 : ] [
            if(pBd[0] != nBd[0]){
                Sky.pb(nBd[1]-MaxH.top().ST);
                Sky.pb(nBd[0]-pBd[0]);
            }
            V += nBd[1]-pBd[1];
            pBd = nBd;
        }
        else{                             // Case 3 : [ ] 
            if(pBd[2] == nBd[2]){
                Sky.pb(V); Sky.pb(nBd[0]-pBd[0]);
            }
        }
    }
    
}

void output(){
    for(int B : Sky)   cout << B << " ";
    for(vector<int> V : Bds){
        for (int i : V) cout << i << " ";
        cout << endl;
    }
}

int main(){
    input ();
    solve ();
    output();
}