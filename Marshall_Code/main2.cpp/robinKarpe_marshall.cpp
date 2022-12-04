#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

#ifndef ROBINKARPE_H
#define ROBINKARPE_H

class proj {

    private: 

    public: 
        void rkSearch(vector<char> text, vector<char> phrase, int mod);
        void bmSearch(vector<char> text, vector<char> phrase, int mod);
        vector<char> getText();
        vector<char> getPhrase();


};

#endif
