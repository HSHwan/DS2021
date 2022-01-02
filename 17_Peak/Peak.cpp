#include <iostream>
#include <utility>
#include <queue>
#define F first
#define S second
using namespace std;

priority_queue<int, vector<int>, greater<int>> Time_bgn, Time_end;
pair<pair<int, int>, int> PeakTime = make_pair(make_pair(0, 0), 0);

void inputTime(){
    int N, t_bgn, t_end;
    cin >> N;
    for (int i = 0; i < N; i++){
        cin >> t_bgn >> t_end;
        Time_bgn.push(t_bgn);
        Time_end.push(t_end);
    }
}

bool isPeak(pair<int, int> t, int cnt){
    if (cnt == PeakTime.S){
        if (t.S - t.F == PeakTime.F.S - PeakTime.F.F)
            return t.S > PeakTime.F.S;
        return t.S - t.F > PeakTime.F.S - PeakTime.F.F;
    }
    return cnt > PeakTime.S;
}

void checkPeak(int t_bgn, int t_end, int cnt){
    pair<int, int> interval = make_pair(t_bgn, t_end);
    if(isPeak(interval, cnt))   PeakTime = make_pair(interval, cnt);
}

void findPeakTime(){
    queue<int> tPoint;
    while(!Time_bgn.empty()){
        if(Time_bgn.top() < Time_end.top()){
            tPoint.push(Time_bgn.top());
            Time_bgn.pop();
        }
        else {
            checkPeak(tPoint.back(), Time_end.top(), tPoint.size());
            tPoint.pop();
            Time_end.pop();
        }
    }
    if (!Time_end.empty())  checkPeak(tPoint.back(), Time_end.top(), tPoint.size());
}

void printPeakTime(){
    cout << PeakTime.F.F << " " << PeakTime.F.S;
}

int main(){
    inputTime()    ;
    findPeakTime() ;
    printPeakTime();
}