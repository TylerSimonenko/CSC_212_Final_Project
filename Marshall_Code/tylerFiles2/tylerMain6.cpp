#include "tyler.h"

int main() {

    proj proj;

    //Keeps track of if the phrase is found
    bool found = 0;

    int phraseDif = 0;

    // File handling
    std::string type = ".txt";
    std::string filename;
    std::string outputName;
    
    // Vector "index" to hold locations of newlines
    std::vector<int> index;

    //Vector "rowOcur" to keep track of how many times w phrase is found in each row
    std::vector<int> rowOcur;

    // Ask user for file name to read
    std::cout << "Please enter the input-file name (without file type): ";
    std::cin >> filename;
    filename += type;

    // Ask user for file name to write
    std::cout << "Please enter the output filename (without file type): ";
    std::cin >> outputName;
    outputName += type;

    // Create vector of chars "text" to hold all text from read file; "search" to hold the search pattern
    std::vector<char> text;
    std::vector<char> search = proj.getPhrase();

    // Read .txt file
    proj.readFile(text, filename, index); 

    // Do algorithms
    std::vector<int> foundIndex = proj.rabinKarp(text, search, found, rowOcur, index);
    proj.boyerMoore(text, search);
    proj.naive(text, search);

    //read/replace
    proj.replace(text, foundIndex, search, found, phraseDif);

    // Write output file
    proj.writeFile(text, outputName, index, phraseDif, rowOcur);

    return 0;
}
