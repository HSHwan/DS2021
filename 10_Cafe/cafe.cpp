#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <list>
#include <utility>
#define MAX_ID 10000
#define F first
#define S second
#define FOR(i,b,n) for(int i = (b); i < (n); i++)
using namespace std;
typedef pair<int, int> pii;
typedef list<pii>::iterator lpi;
int N, K, ID, Seat_num;
array<int, MAX_ID+1> ID_check;
vector<int> Seat_in;
vector<pii> Guest_enter;
list<pii> Seat;

void input(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    cin >> N >> K;
    FOR(i,0,K){
        cin >> ID;
        Seat_in.push_back(ID);
    }
}

void guest_out(lpi begin, lpi end, int id){
    for (auto it = begin; it != end; it++){
        if(it->S == id){
            Seat.erase(it);
            return;
        }
    }
}

int assigned_seat(){
    if (Seat.size() == 1 && Seat.front().F == 1)   return N/2 + 1;
    pii two_seat, max_dis_seat = make_pair(1,0);
    two_seat.F = Seat.front().F;
    for (auto it = Seat.begin(); it != Seat.end(); it++){
        two_seat.S = it->F;
        if (two_seat.S - two_seat.F  > max_dis_seat.S){
            max_dis_seat.S = two_seat.S - two_seat.F;
            max_dis_seat.F = two_seat.F + max_dis_seat.S / 2;
        }
        two_seat.F = two_seat.S;
    }
    if (N + Seat.front().F - Seat.back().F > max_dis_seat.S){
        max_dis_seat.F = Seat.back().F + (N + Seat.front().F - Seat.back().F)/2;
        if (max_dis_seat.F > N) max_dis_seat.F %= N;
    }
    return max_dis_seat.F;
}

void solve(){
    FOR(i,0,K){
        ID_check[Seat_in[i]]++;
        if(Seat.empty()){
            Seat.push_back(make_pair(1, Seat_in[i]));
            Guest_enter.push_back(Seat.front());
        }    
        else if (!(ID_check[Seat_in[i]] % 2)){  // Guest OUT
            guest_out(Seat.begin(), Seat.end(), Seat_in[i]);
        }
        else if (Seat.size() < N){              // Guest IN
            Seat_num = assigned_seat();
            lpi seat_idx;
            for (seat_idx = Seat.begin(); seat_idx != Seat.end(); seat_idx++){
                if (seat_idx->F > Seat_num){
                    Guest_enter.push_back(make_pair(Seat_num, Seat_in[i]));
                    Seat.insert(seat_idx, Guest_enter.back());
                    break;
                }
            }
            if(seat_idx == Seat.end()){
                Guest_enter.push_back(make_pair(Seat_num, Seat_in[i]));
                Seat.push_back(Guest_enter.back());
            }
        }
    }
}

void output(){
    cout.tie(NULL);
    for (pii guest : Guest_enter)   cout << guest.S << " " << guest.F << "\n";
}

int main(){
    input ();
    solve ();
    output();
}