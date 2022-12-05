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
        std::vector<int> rabinKarp(std::vector<char>& text, std::vector<char>& search, bool& found, std::vector<int>& rowOcur, std::vector<int> index);
        void boyerMoore(std::vector<char>& text, std::vector<char>& search);
        void naive(std::vector<char> text, std::vector<char> search);
        void writeFile(std::vector<char>& text, std::string outputName, std::vector<int>& index, int phraseDif, std::vector<int> rowOcur);
        std::vector<char> getPhrase();
        void replace(std::vector<char>& text, std::vector<int> index, std::vector<char> search, bool found, int&phraseDif);



};

#endif
