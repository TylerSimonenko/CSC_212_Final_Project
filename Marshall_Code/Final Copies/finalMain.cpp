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

    //Vector "rowOcur" to keep track of how many times w phrase is found in each row
    std::vector<int> rowOcur(index.size(), 0);
    

    // Do algorithms
    clock_t rkbegin = clock();
    std::vector<int> foundIndex = proj.rabinKarp(text, search, found, rowOcur, index);
    clock_t rkend = clock();

    double rkTime = double(rkend - rkbegin) * 1000 / CLOCKS_PER_SEC;

    clock_t bmbegin = clock();
    proj.boyerMoore(text, search);
    clock_t bmend = clock();

    double bmTime = double(bmend - bmbegin) * 1000 / CLOCKS_PER_SEC;

    clock_t nbegin = clock();
    proj.naive(text, search);
    clock_t nend = clock();

    double naiveTime = double(nend - nbegin) * 1000 / CLOCKS_PER_SEC;

    std::vector<double> times;
    times.push_back(rkTime);
    times.push_back(bmTime);
    times.push_back(naiveTime);

    for (int i = 0; i < 3; i++) {
        std::cout << times[i] << ' ';
    }

    //read/replace
    proj.replace(text, foundIndex, search, found, phraseDif);

    // Write output file
    proj.writeFile(text, outputName, index, phraseDif, rowOcur);

    return 0;
}
