#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#define REP(n)  for (int i = 0; i < (n); i++)
#define NONEOUT() std::cout << "NONE\n";
using namespace std;
int Work, I, J;
list<char> DNA, Sub_DNA;
list<char>::iterator D_bgn, D_end;

void inputDNA(){
    string sub, file = "/NESPA/sapiens.txt";
    ifstream in(file);
    getline(in, sub); // first line : sequencing information
    while(!in.eof()){
        getline(in, sub);
        for (char ch : sub) DNA.push_back(ch);
    }
}

void set_iterator(){
    D_bgn = DNA.begin(); D_end = DNA.begin();
    advance(D_bgn, I-1);
    advance(D_end, J-0);
}

int choose_func(){
    vector<string> funcs {"front", "back", "cut", "double", "flip", "report"};
    string func_name;
    int func_number = 0;
    cin >> func_name >> I >> J;
    if (I > DNA.size() && func_name != funcs.back())    return -1;
    if (J > DNA.size()) J = DNA.size();
    for (string func : funcs){
        if (func_name == func){
            set_iterator();
            return func_number;
        }
        func_number++;
    }
    return -1;
}

void cut(){
    Sub_DNA.splice(Sub_DNA.begin(), DNA, D_bgn, D_end);
}

void front(){
    cut();
    DNA.insert(DNA.begin(), Sub_DNA.begin(), Sub_DNA.end());
}

void back(){
    cut();
    DNA.insert(DNA.end(), Sub_DNA.begin(), Sub_DNA.end());
}

void copy(){    // double(i, j)
    cut();
    D_end = DNA.begin();
    advance(D_end, I-1);
    REP(2)    DNA.insert(D_end, Sub_DNA.begin(), Sub_DNA.end());
}

void flip(){
    cut();
    D_end = DNA.begin();
    advance(D_end, I-1);
    Sub_DNA.reverse();
    DNA.insert(D_end, Sub_DNA.begin(), Sub_DNA.end());
}

void report(){
    if (I > DNA.size()){    // empty substring
        NONEOUT();
        return ;
    }
    REP(J-I+1){
        cout << *D_bgn;
        D_bgn++;
    }
    cout << "\n";
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    inputDNA();
    cin >> Work;
    REP(Work){
        switch (choose_func()){
            case 0 : front()  ; break;
            case 1 : back()   ; break;
            case 2 : cut()    ; break;
            case 3 : copy()   ; break;
            case 4 : flip()   ; break;
            case 5 : report() ; break;
            default:            break;
        }
        Sub_DNA.clear();
    }
}