#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#define REP(n) for (int i = 0; i < (n); i++)
using namespace std;
typedef tuple<int, int, string> mafia_info;
int N;
vector<mafia_info> Mafia_rank;

class Mafia {
public:
    Mafia* boss;
    vector<Mafia*> subords;
    string name;
    Mafia() : name(""), boss(nullptr){};
    Mafia(string _name) : name(_name), boss(nullptr){};
    void addSub(Mafia* sub){
        subords.push_back(sub);
    }
    void yesBoss(Mafia* boss){
        this->boss = boss;
    }
};

typedef vector<Mafia*>::iterator vMi;
vector<Mafia*> Mafia_list;

Mafia* checkMafia(string mafia_name){
    auto it = Mafia_list.begin();
    for (; it != Mafia_list.end(); it++){
        if((*it)->name == mafia_name)   break;
    }
    if (it == Mafia_list.end()){
        Mafia* new_mafia = new Mafia(mafia_name);
        Mafia_list.push_back(new_mafia);
        return Mafia_list.back();
    }
    else    return (*it);
}

int subNum(Mafia* mafia){
    int num = mafia->subords.size();
    for (Mafia* m_i : mafia->subords){
        num += subNum(m_i);
    }
    return num;
}

int bossDistance(Mafia* mafia){
    Mafia* next_boss = mafia->boss;
    int dist = 0;
    while(next_boss){
        next_boss = next_boss->boss;
        dist++;
    }
    return dist;
}

bool compareMafia(mafia_info m1, mafia_info m2){
    if (get<0>(m1) > get<0>(m2))    return true;
    else if (get<0>(m1) == get<0>(m2)){
        if (get<1>(m1) < get<1>(m2))        return true;
        else if (get<1>(m1) == get<1>(m2))  return get<2>(m1) < get<2>(m2);
    }
    return false;
}

void inputNode(){
    cin >> N;
    string person_name, boss_name;
    Mafia* person_i, * boss_i;
    vMi check_person, check_boss;
    REP(N-1){
        cin >> person_name >> boss_name;
        person_i = checkMafia(person_name);
        boss_i   = checkMafia(boss_name);
        person_i->yesBoss(boss_i);
        boss_i->addSub(person_i);
    }
}

void ranking(){
    mafia_info mafia_i;
    for (Mafia* mafia : Mafia_list){
        mafia_i = make_tuple(subNum(mafia), bossDistance(mafia), mafia->name);
        Mafia_rank.push_back(mafia_i);
    }
    sort(Mafia_rank.begin(), Mafia_rank.end(), compareMafia);
}

void printRank(){
    for (mafia_info m_i : Mafia_rank){
        cout << get<2>(m_i) << "\n";
    }
}

int main(){
    inputNode();
    ranking  ();
    printRank();
}