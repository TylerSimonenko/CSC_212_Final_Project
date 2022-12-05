#include "search.h"

int main(){

    std::string word;
    std::string filename;
    std::cin >> word;
    std::cin >> filename;

    Search search(word, filename);
    search.setup();
    search.writeFile(word);

    return 0;
}
