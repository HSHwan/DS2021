#include <iostream>
#include <set>
#include <map>
#include <utility>
#define SET first
#define DATA second
using namespace std;

map<set<int>, set<int, greater<int>>> GeneDisData;

pair<set<int>, int> getInputData(){
    int gene_id, end_code;
    set<int> geneID_set;
    while ( true ){
        cin >> gene_id;
        if ( gene_id <= 0 ){
            end_code = gene_id;
            break;
        }
        geneID_set.insert(gene_id);
    }
    return make_pair(geneID_set, end_code);
}

void ReportMode(set<int> geneID_set, int disease_code){
    auto data_itr = GeneDisData.find(geneID_set);
    if ( data_itr == GeneDisData.end() )
        GeneDisData[geneID_set] = set<int, greater<int>>{ disease_code };
    else
        data_itr->DATA.insert(disease_code);
}

void printQuery(const set<int, greater<int>>& Q){
    for (int GD : Q)    cout << GD << " ";
}

void QueryMode(set<int> geneID_set){
    auto data_itr = GeneDisData.find(geneID_set);
    if ( data_itr != GeneDisData.end() )
        printQuery( data_itr->DATA );
    else
        cout << "None";
    cout << "\n";
}

int main(){
    char mode;
    while ( true ){
        cin >> mode;
        if (mode == 'R' || mode == 'Q'){
            pair<set<int>, int> input_data = getInputData();
            if (mode == 'R' && input_data.DATA < 0)
                ReportMode(input_data.SET, input_data.DATA);
            else if (mode == 'Q' && input_data.DATA == 0)
                QueryMode (input_data.SET);
            else break;
        }
        else if (mode == '$')   break;
        else {
            cerr << "Input Error";
            break;
        }
    }
}