#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

map<set<int>, vector<int>> GeneDisData;

void ReportMode(){
    int gene_id, disease_code;
    set<int> geneID_set;
    while ( true ){
        cin >> gene_id;
        if (gene_id < 0){
            disease_code = gene_id;
            break;
        }
        geneID_set.insert(gene_id);
    }
    auto data_itr = GeneDisData.find(geneID_set);
    if ( data_itr == GeneDisData.end() )
        GeneDisData[geneID_set] = vector<int>{ disease_code };
    else {
        data_itr->second.push_back(disease_code);
        sort(data_itr->second.rbegin(), data_itr->second.rend());
    }
}

void printQuery(const vector<int>& Q){
    for (int GD : Q)    cout << GD << " ";
}

void QueryMode(){
    int gene_id;
    set<int> geneID_set;
    while ( true ){
        cin >> gene_id;
        if (gene_id == 0)   break;
        geneID_set.insert(gene_id);
    }
    auto data_itr = GeneDisData.find(geneID_set);
    if ( data_itr != GeneDisData.end() )
        printQuery( data_itr->second );
    else
        cout << "None";
    cout << "\n";
}

int main(){
    char mode;
    bool inputEnd = false;
    while (!inputEnd){
        cin >> mode;
        switch( mode ){
            case 'R':
                ReportMode();
                break;
            case 'Q':
                QueryMode ();
                break;
            case '$':
                inputEnd = true;
                break;
            default :
                cerr << "Input Error";
                break;
        }
    }
}