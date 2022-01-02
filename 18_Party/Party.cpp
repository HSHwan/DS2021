#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <deque>
#define V_MAX 26
using namespace std;

int Tmin = 0;
vector<char> graph[V_MAX], Places;
char Friends[3], PartyPlace;

void inputGraph(){
    int vertex;
    cin >> vertex;
    cin >> Friends[0] >> Friends[1] >> Friends[2];

    char v, v_e;
    for(int i = 0; i < vertex; i++){
        cin >> v;
        Places.push_back(v);

        cin >> v_e;
        while(v_e != '$'){
            graph[v-'a'].push_back(v_e);
            cin >> v_e;
        }
    }
}

int BFS(char v, int fNum){
    if(v == Friends[fNum]) return 0;
    int t = 1;
    unordered_set<char> visited;
    deque<char> Q, nextQ;
    Q.push_back(v);
    visited.insert(v);

    while( !Q.empty() ){
        v = Q.front();
        Q.pop_front();
        for(auto& v_i : graph[v-'a']){
            if( v_i == Friends[fNum] )  return t;
            auto isVisited = visited.find(v_i);
            if( isVisited == visited.end() ){
                visited.insert(v_i);
                nextQ.push_back(v_i);
            }            
        }
        if( Q.empty() ){
            while(!nextQ.empty()){
                Q.push_back(nextQ.front());
                nextQ.pop_front();
            }
            t += 3;
        }
    }
    return -1;
}

int calcMaxT(char v){
    vector<int> times = { BFS(v, 0), BFS(v, 1), BFS(v, 2) };
    if (find(times.begin(), times.end(), -1) != times.end())    return -1;
    return *max_element(times.begin(), times.end());
}

void findPlace(){
    int t;
    for (auto& v : Places){
        t = calcMaxT(v);
        if (!Tmin){
            Tmin = t;
            if (t == -1)    PartyPlace = '@';
            else            PartyPlace =   v;
        }
        else if (t != -1 && (Tmin == -1 || t < Tmin)){
            Tmin = t;
            PartyPlace = v;
        }
        else if (t == Tmin && v < PartyPlace)   PartyPlace = v;
    }
}

void printPlace(){
    cout << PartyPlace << "\n" << Tmin;
}

int main(){
    inputGraph();
    findPlace ();
    printPlace();
}