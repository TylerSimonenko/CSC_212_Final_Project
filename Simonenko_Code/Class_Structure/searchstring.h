#ifndef SEARCHSTRING_H
#define SEARCHSTRING_H

// Including Libs
#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>

// Class "searchstring"
class searchstring {

private:
    // Private variables
    int m_charNum = 256;            // Number of possible characters in text
    int m_ts;                       // Size of input text (text size)
    int m_ss;                       // Size of search phrase (search size)
    int m_prime = 103;              // Prime number used in hashing
    int m_badchar[256];             // Array for Bad Character Heuristic
    std::string m_type = ".txt";
    std::string m_inputFile;
    std::string m_outputFile;
    std::vector<int> m_RKIdx;       // Holds indexes of search string locations (Rabin-Karp)
    std::vector<int> m_BMIdx;       // Holds indexes of search string locations (Boyer-Moore)
    std::vector<int> m_writeIdx;
    std::vector<char> m_text;
    std::vector<char> m_search;

    // Private (internal) member functions
    void readFile();
    void getPhrase();
    void rabinKarp();
    void boyerMoore();
    void badCharHeuristic();
    void writeFile();
    void print(int count, std::vector<int> indexes);

public:
    // Constructor
    searchstring(std::string inputFile, std::string outputFile);

    // Functions called in "main_new.cpp"
    void runProject();

    //void replace(std::vector<char>& text, std::vector<int> index, std::vector<char> search, bool found);

};

#endif
