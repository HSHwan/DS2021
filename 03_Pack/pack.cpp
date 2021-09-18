#include <iostream>
#include <deque>
#include <algorithm>
#define ST first
#define ND second
using namespace std;

deque<pair<int, int>> Packs;
deque<int> Costs;

int MaxLen = -1, NDSum = 0, MinCost;
int PackSet[4], Condt[4];

int Pow2(int num){ return num * num;}

void input(){
    pair<int,int> Pack;
    for (int i = 0; i < 3; i++){ 
        cin >> Pack.ST >> Pack.ND;
        if (Pack.ST < Pack.ND)  swap(Pack.ST, Pack.ND);
        if (Pack.ST > MaxLen){ // MAX -> Front
            MaxLen = Pack.ST;
            Packs.push_front(Pack);
        }
        else Packs.push_back(Pack);
        NDSum += Pack.ND;
    }
}

void ArraySet(){
    PackSet[0] = max(Packs[1].ND,  Packs[2].ND);
    PackSet[1] = max(Packs[1].ND,  Packs[2].ST);
    PackSet[2] = max(Packs[1].ST,  Packs[2].ND);
    PackSet[3] = max(Packs[1].ST,  Packs[2].ST);
    Condt  [0] =     Packs[1].ST + Packs[2].ST ;
    Condt  [1] =     Packs[1].ST + Packs[2].ND ;
    Condt  [2] =     Packs[1].ND + Packs[2].ST ;
    Condt  [3] =     Packs[1].ND + Packs[2].ND ;
}

void solution(){
    Costs.push_back(Pow2(MaxLen) + Pow2(NDSum)); // Three boxes arranged (minimum case)
    for (int i = 0; i < 4; i++){                 // Two boxes stacked at the longest box
        MinCost  = Pow2(Packs[0].ND + PackSet[i]);
        MinCost += Pow2(max(MaxLen, Condt[i]));
        Costs.push_back(MinCost);
    }
    for (int i = 1; i <= 2; i++){                // One of two boxes stacked at the longest box
        MinCost  = Pow2(MaxLen + Packs[i].ST);
        MinCost += Pow2(max(Packs[i].ND, NDSum-Packs[i].ND));
        Costs.push_back(MinCost);
        MinCost  = Pow2(MaxLen + Packs[i].ND);
        MinCost += Pow2(max(Packs[i].ST, NDSum-Packs[i].ND));
        Costs.push_back(MinCost);
    }
}

void output(){
    for (int cost : Costs){
        if (MinCost > cost) MinCost = cost;
    }
    cout << MinCost;
}

int main(){
    input   ();
    ArraySet();
    solution();
    output  ();
}