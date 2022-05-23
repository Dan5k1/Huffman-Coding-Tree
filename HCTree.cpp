#include "HCTree.hpp"
#include <queue>
#include <vector>
#include <fstream>
#include <stack>
#include "Helper.hpp"
using namespace std;
vector<int> freqs;

void HCTree::build(const vector<int>& fqs) {
    freqs = fqs;
    priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pq;
    for (int i = 0; i < (int)freqs.size(); i++){ 
        if (freqs[i] > 0){
            HCNode* newNode = new HCNode(freqs[i], (unsigned char)i);
            leaves[i] = newNode;
            pq.push(newNode);
            cout << freqs[i] << " , " << i << endl;
            //cout << pq.top()->symbol << endl;
        }
    }
    while (pq.size() > 1){
        unsigned char symbol = pq.top()->symbol;
        cout << pq.top()->symbol << endl;
        int count = pq.top()->count;
        HCNode* newNode = new HCNode(count, symbol);
        newNode->c0 = pq.top();
        pq.top()->p = newNode;
        pq.pop();
        newNode->c1 = pq.top();
        count += pq.top()->count;
        pq.top()->p = newNode;
        pq.pop();
        newNode->count = count;
        pq.push(newNode);
        cout << "asd" << endl;
    }
    cout << "asd" << endl;
    if(pq.size() > 0){
        HCTree::root = pq.top();
    }
}
// void gothrough(HCNode* root){
//     if(root == NULL){
//         return;
//     }
//     gothrough(root->c0);
//     gothrough(root->c1);
// }
void HCTree::traverse(){
    //gothrough(root);
}
void HCTree::headerCreator(FancyOutputStream & out){
    // Header creator (dumb)
    for(int i = 0; i < 256; i++){
        out.write_int(freqs[i]);
    }
}

void deleteNodes(HCNode* node){
    if (node == NULL)
        return;
    deleteNodes(node->c0);
    deleteNodes(node->c1);
    delete node;
}

HCTree::~HCTree(){
    if (root == NULL){
        return;
    }else{
        deleteNodes(root);
    }
}

void HCTree::encode(unsigned char s, FancyOutputStream & out)const{
    stack<int> stacky;
    HCNode* node = leaves[s];
    while (node != root){
        if (node->p->c0 == node){
            stacky.push(0);
        }else{
            stacky.push(1);
        }
        node = node->p;
    }
    while (!stacky.empty()){
        out.write_bit(stacky.top());
        stacky.pop();
    }
}
unsigned char HCTree::decode(FancyInputStream & in)const{
    HCNode* node = root;
    while (node->c0 != NULL && node->c1 !=NULL){
        if (in.read_bit() == 0){
            node = node->c0;
        }else{
            node = node->c1;
        }
    }
    //cout << node->symbol << endl;
    return node->symbol;
}
