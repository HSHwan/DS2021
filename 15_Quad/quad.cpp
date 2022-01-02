#include <iostream>
#include <string>
#include <stack>
#define MAXSIZE 64
#define FOR(i,b,n) for (int i = (b); i < (n); i++)
using namespace std;
string Qts;
char Img[MAXSIZE][MAXSIZE];
int ImgSize;

struct Node {
    char pixel;
    int next;
    Node* childs[4];
    Node(){};
    Node(char _pixel) : pixel(_pixel), next(0){};
};

Node* Root = new Node('T');

void drawIMG(char pixel, int n, int row, int col){
    FOR(i, row, row + n){
        FOR(j, col, col + n)    Img[i][j] = pixel;
    }
}

void drawIMG(Node* pixels, int n, int row, int col){
    switch ( pixels->pixel ){
        case 'T': {
            int halfN = n/2;
            drawIMG(pixels->childs[0], halfN, row, col + halfN);
            drawIMG(pixels->childs[1], halfN, row, col);
            drawIMG(pixels->childs[2], halfN, row + halfN, col);
            drawIMG(pixels->childs[3], halfN, row + halfN, col + halfN);
            break;
        }
        case '0':
        case '1':
            drawIMG(pixels->pixel, n, row, col);
            break;
        default : break;
    }    
}

void printIMG(){
    FOR(i, 0, ImgSize){
        FOR(j, 0, ImgSize)  cout << Img[i][j];
        cout << "\n";
    }
}

void QTStoIMG(){
    cin >> Qts;
    if (Qts[0] == '0' || Qts[0] == '1'){
        drawIMG(Qts[0], ImgSize, 0, 0);
        printIMG();
        return;
    }

    stack<Node*> nodes;
    Node* curNode = Root;
    FOR(i, 1, Qts.length() - 1){
        switch ( Qts[i] ){
            case '(':
                curNode->childs[curNode->next] = new Node('T');
                nodes.push(curNode);
                curNode = curNode->childs[curNode->next++];
                break;
            case ')':
                curNode = nodes.top();
                nodes.pop();
                break;
            case '0':
            case '1':
                curNode->childs[curNode->next++] = new Node(Qts[i]);
                break;
            default : return;
        } 
    }
    drawIMG(Root, ImgSize, 0, 0);
    printIMG();
}

string getQTS(int n, int row, int col){
    string qts = "";
    qts += Img[row][col];
    FOR(i, row, row + n){
        FOR(j, col, col + n){
            if (Img[i][j] != qts[0]){
                int halfN = n / 2;
                qts  = "(";
                qts +=  getQTS(halfN, row, col + halfN) + \
                        getQTS(halfN, row, col) + \
                        getQTS(halfN, row + halfN, col) + \
                        getQTS(halfN, row + halfN, col + halfN);
                qts += ")";
                return qts;
            }
        }
    }
    return qts;
}

void IMGtoQTS(){
    string img_row;
    FOR(i, 0, ImgSize){
        cin >> img_row;
        FOR(j, 0, ImgSize)    Img[i][j] = img_row[j];
    }
    Qts = getQTS(ImgSize, 0, 0);
    cout << Qts;
}

int main(){
    int k;
    string strType;
    cin >> k >> strType;
    ImgSize = 1 << k;
    switch ( strType[0] ){
        case 'Q': QTStoIMG(); break;
        case 'I': IMGtoQTS(); break;
        default :             break;
    }
}