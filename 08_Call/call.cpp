#include <iostream>
#include <vector>
#include <stack>
#include <utility>
#define FOR(i,b,n) for(int i = (b); i < (n); i++)
using namespace std;
string Calls[26][31];
stack<pair<char, int>> F_call;
vector<string> Func_exec;
char Func_name;
int N, K1, K2, Call_idx, R_check[26];
bool Main_return = false, DeadLock = false;

void input(){
    cin >> N >> K1 >> K2;
    FOR(i,0,N){
        cin >> Func_name;
        FOR(j,0,31){
            cin >> Calls[Func_name-'A'][j];
            if (Calls[Func_name-'A'][j] == "$")  break;
        }
    }
}

string F_format(string exec_call){ // write an execution like 'F-act' style
    string Func_act;
    Func_act += Func_name;
    Func_act += "-" + exec_call;
    return Func_act;
}

void solve(){
    Func_name = 'M'; // first function : Main()
    Call_idx  =  0 ; // first index    : 0
    while(!Main_return){
        FOR(i,Call_idx,31){
            if(Calls[Func_name-'A'][i] == "$"){ // funtion return
                if (F_call.empty()) Main_return = true; // main() return
                else {                          // return to previous function
                    R_check[Func_name-'A']--;
                    Func_name = F_call.top().first ;
                    Call_idx  = F_call.top().second;
                    F_call.pop();
                }
                break;
            }
            else if(isupper( Calls[Func_name-'A'][i][0] )){    // funtion name (uppercase)
                if  (R_check[Calls[Func_name-'A'][i][0]-'A']){ // check if it is a recursive call
                    DeadLock = true; return;
                }
                else R_check[Calls[Func_name-'A'][i][0]-'A']++;
                F_call.push(make_pair(Func_name, i+1))  ;
                Func_name =  Calls[Func_name-'A'][i][0] ;
                Call_idx  =                          0  ;
                break;
            }
            else    Func_exec.push_back(F_format(Calls[Func_name-'A'][i])); // insert an execution
        }
    }
}

void output(){
    if(       DeadLock       ) {cout << "DEADLOCK"      << '\n'; return;}
    if(K1 <= Func_exec.size())  cout << Func_exec[K1-1] << '\n';
    else                        cout << "NONE"          << '\n';
    if(K2 <= Func_exec.size())  cout << Func_exec[K2-1] << '\n';
    else                        cout << "NONE"          << '\n';
}

int main(){
    input ();
    solve ();
    output();
}