#include <iostream>
#include "HCTree.hpp"
#include "Helper.hpp"
using namespace std;

vector<int> getFreqs(FancyInputStream& inFile){
    vector<int> freqs;
    for (int i = 0; i <256; i++){
        freqs.push_back(0);
        //cout << i << endl;
    }
    //cout << inFile.read_byte() << endl;
    
    for(int i =0; i < inFile.filesize();i++){
        freqs[inFile.read_byte()]++;
        //cout << inFile.read_byte() << endl;
    } 
    cout << freqs[10] << endl;
    return freqs;
}
void compress(const char* inputFile, const char* outputFile){
    //const char* outF = argv[2];
    FancyInputStream inStr (inputFile);
    FancyOutputStream outStr (outputFile);
    //cout << argv[1] << endl;
    HCTree* ht = new HCTree();
    ht->build(getFreqs(inStr));
    // Here we create the header:
    ht->headerCreator(outStr);
    inStr.reset();
    // Now we encode the file:
    cout << inStr.filesize();
    for(int i =0; i < inStr.filesize();i++){
        ht->encode(inStr.read_byte(), outStr);   
    } 
}
int main(int argc, char* argv[]) {
    if (argc != 3 ){
        cout << "Wrong number of arguments" << endl;
        return 0;
    }
    const char* inF = argv[1];
    const char* outF = argv[2];
    //FancyOutputStream outStr = FancyOutputStream(argv[2]);
    compress(inF, outF);
}

