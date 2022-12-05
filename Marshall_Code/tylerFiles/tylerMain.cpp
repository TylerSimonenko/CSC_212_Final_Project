#include "tyler.h"

int main() {

    proj proj;

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
    std::vector<char> search = proj.getPhrase();;

    // Read .txt file
    proj.readFile(text, filename, index); 

    // Do algorithms
    proj.rabinKarp(text, search);
    proj.boyerMoore(text, search);

    // Write output file
    proj.writeFile(text, outputName, index);

    return 0;
}
