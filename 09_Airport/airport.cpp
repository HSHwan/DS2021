#include <iostream>
#include <vector>
#include <queue>
#define FOR(i,b,n) for (int i = (b); i < (n); i++)
using namespace std;
typedef queue<int> Qi;
Qi Take_off;
vector<Qi> Runway;
int Airport_ID, Airport_number, Idx_min, ID_min = 10001;

void input(){
    cin >> Airport_number;
    FOR(i,0,Airport_number){
        Qi Airports;
        while(true){
            cin >> Airport_ID;
            Airports.push(Airport_ID);
            if (!Airport_ID)    break;
        }
        Runway.push_back(Airports);  
    }
}

void solve(){
    while(true){
        Idx_min = -1;
        ID_min = 10001;
        FOR(i,0,Airport_number){
            if (Runway[i].front() && Runway[i].front() < ID_min){
                Idx_min = i;
                ID_min = Runway[i].front();
            }
        }
        if (Idx_min != -1){
            Take_off.push(Runway[Idx_min].front());
            Runway[Idx_min].pop();
        }
        else    break;
    }
}

void output(){
    while(!Take_off.empty()){
        cout << Take_off.front() << "\n";
        Take_off.pop();
    }    
}

int main(){
    input ();
    solve ();
    output();
}