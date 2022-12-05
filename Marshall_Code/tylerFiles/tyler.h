// Including Libs
#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>

#ifndef TYLER_H
#define TYLER_H

class proj {
 
    public:
        void readFile(std::vector<char>& text, std::string filename, std::vector<int>& index);
        void rabinKarp(std::vector<char>& text, std::vector<char>& search);
        void boyerMoore(std::vector<char>& text, std::vector<char>& search);
        void writeFile(std::vector<char>& text, std::string outputName, std::vector<int>& index);
        std::vector<char> getPhrase();


};

#endif
