#include <iostream>
#include <algorithm>
#include <list>
#include <array>

#define minN    10
#define maxN    1000000
#define minK    5
#define maxK    10000
#define minID   1
#define maxID   10000
#define lvi     list<visitor>::iterator
#define lvbgn   lvst.begin()
#define lvend   lvst.end()
#define duo     pair<lvi, int>
#define lvrng   lvbgn,lvend

using namespace std;

class   visitor{
private:
    int id;
    int seat;
public:
    int Seat()  {   return seat;    }
    int ID()    {   return id;      }
    bool operator ==    (const int& id){
        return (this->ID() == id);
    }
    void Set(int nid, int ns){
        id = nid;
        seat = ns;
    }
    friend ostream& operator << (ostream& os, visitor& vs);
};

ostream& operator << (ostream& os, visitor& vs){
    os << vs.ID() << " " << vs.Seat()<<endl;
    return os;
}

int nSeat(lvi vbegin, lvi vend, lvi vi, int N){
    if(next(vi) == vend)
        return vbegin->Seat() + N;
    else
        return next(vi)->Seat();
}

int rsvSum(int reserve, int N){
    if(reserve > N)
        return reserve - N;
    else
        return reserve;
}


int rsvSeat(int sum, int N){
    if(sum % 2 == 0)
        return rsvSum(sum/2, N);
    else{
        return min(rsvSum(sum/2, N), rsvSum(sum/2+1, N));
    }
}

lvi rsvItr(lvi lsbegin, lvi nextitr, int sum, int N){
    if(sum / 2 > N)
        return lsbegin;
    else
        return nextitr;
}

lvi pItr(lvi lsbegin, lvi lsend, lvi vi){
    if(vi == lsbegin)
        return prev(lsend);
    else
        return prev(vi);
}

lvi nItr(lvi lsbegin, lvi lsend, lvi vi){
    if(next(vi) == lsend)
        return lsbegin;
    else
        return next(vi);
}

bool rcheck(int arg, int minArg, int maxArg){
    return ( minArg <= arg ) && ( arg <= maxArg );
}

void pushrsv(duo& rsv, list<duo>* list_ptr){
    if(rsv.second < list_ptr->front().second)
        list_ptr->push_front(rsv);
    else
        list_ptr->push_back(rsv);
    return ;
}

void makelist(int& maxdis, int& dis, list<duo> *list_ptr, int& sum,
              int& nx, lvi vi, lvi lsbegin, int& N, duo& rsv){
    if(maxdis <= dis){
        if(maxdis < dis){
            maxdis = dis;
            list_ptr->clear();  }
        sum = nx + vi->Seat();
        rsv = make_pair(rsvItr(lsbegin, next(vi),sum,N), rsvSeat(sum,N));
        pushrsv(rsv, list_ptr); }
    return ;
}

int main()
{
    int N, K, id;
    int maxdis, dis;
    int nx, sum, idx;
    visitor vst;
    duo rsv;

    list<visitor> lvst;
    list<duo> lrsv;
    list<duo> lrrsv;
    list<duo> *lptr;

    lvi fnd;
    lvi vi;

    array<int, 2> rnx;
    array<int, 2> rdis;
    array<lvi, 2> rvi;

    cin >> N;
    cin >> K;

    if( !rcheck(N, minN, maxN) || !rcheck(K, minK, maxK))
        return 0;
    for(int i =0; i<K; i++){
        cin >> id;
        if(!rcheck(id, minID, maxID))
            return 0;

        fnd = find(lvbgn, lvend, id);

        if(fnd != lvst.end()){
            rvi[0] = nItr(lvrng,fnd);
            rvi[1] = pItr(lvrng,fnd);
            lvst.erase(fnd);

            rnx[0] = nSeat(lvrng, rvi[0],N);
            rnx[1] = nSeat(lvrng, rvi[1],N);

            rdis[0] = rnx[0] - rvi[0]->Seat();
            rdis[1] = rnx[1] - rvi[1]->Seat();

            if(rdis[0] > rdis[1])
                idx = 0;
            else
                idx = 1;

            vi = rvi[idx];
            dis = rdis[idx];
            nx = rnx[idx];
            if(lrrsv.empty()){
                lrsv.clear();
                sum = nx + vi->Seat();
                rsv = make_pair(rsvItr(lvbgn, next(vi),sum,N),rsvSeat(sum,N));
                lrrsv.push_back(rsv);
                maxdis = dis;   }
            else
                makelist(maxdis, dis, &lrrsv, sum, nx, vi, lvbgn, N, rsv);
        }
        else if(lvst.size() <= N){
            if(lvst.empty()){
                    rsv = make_pair(lvst.begin(), 1);
                    lrsv.push_back(rsv);    }
            else if(lrsv.empty() && lrrsv.empty()){
                    maxdis  = 0;
                    for(vi = lvbgn; vi != lvend; vi++){
                        nx  = nSeat(lvrng, vi, N);
                        dis = nx - vi->Seat();
                        makelist(maxdis, dis, &lrsv, sum, nx, vi, lvbgn, N, rsv);   }
            }
            if(lrrsv.empty())
                lptr = &lrsv;
            else
                lptr = &lrrsv;

            vst.Set(id, lptr->front().second);
            lvst.insert(lptr->front().first, vst);
            lptr->pop_front();
            cout << vst;
        }
    }
    return 0;
}