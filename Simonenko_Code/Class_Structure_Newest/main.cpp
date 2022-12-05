// Include header file
#include "searchstring.h"

// Main function
int main(int argc, char** argv) {

    // Get files info from command line arguments
    std::string inputFile = argv[1];
    std::string outputFile = argv[2];

    // Create object "project" of class "searchstring"
    searchstring final(inputFile, outputFile);

    // Run the searchstring project
    final.runProject();

    // End of code
    return 0;

}
