#include <iostream>
#include <list>
#include <vector>
#define REP(n) for (int i = 0; i < (n); i++)
using namespace std;
typedef list<int>::iterator lii;
int N, Work, Cut_i, Cut_j;
list<int> CardDeck;

int input(){
    string action;
    cin >> action;
    if      (action == "Shuffle")   return 0;
    else if (action == "Cut"    )   return 1;
    else                            return 2;
}

void create_deck(int card_num){
    for (int i = 1; i <= card_num; i++) CardDeck.push_back(i);
}

void shuffle_deck(){
    lii a_idx = CardDeck.begin(), b_idx = --CardDeck.end();
    advance(a_idx, N/2);
    REP( N/2 ){
        CardDeck.insert(a_idx, *b_idx);
        advance(a_idx, -2); 
        b_idx--;
        CardDeck.pop_back();
    }
}

void cut_deck(){
    cin >> Cut_i >> Cut_j;
    if (Cut_j == CardDeck.size())   return ;
    lii cut_bgn = CardDeck.begin(), cut_end = CardDeck.begin();
    advance(cut_bgn, Cut_i-1);
    advance(cut_end, Cut_j-0);
    CardDeck.splice(CardDeck.end(), CardDeck, cut_bgn, cut_end);
}

void show_deck(){
   lii card_idx = CardDeck.begin();
   advance(card_idx, N/2-1);
   vector<int> show_card {CardDeck.front(), *card_idx, CardDeck.back()};
   for (int card : show_card)   cout << card << " ";
}

int main(){
    cin >> N >> Work;
    create_deck( N );
    REP( Work ){
        switch( input() ){
            case 0 : shuffle_deck(); break;
            case 1 : cut_deck();     break;
            default:                 break;
        }
    }
    show_deck();
}