#include "robinKarpe.h"

using namespace std; 

int main() {

    proj proj;

    vector<char> text = proj.getText();
    vector<char> phrase = proj.getPhrase();

    int mod = INT_MAX;

    proj.rkSearch(text, phrase, mod);
    proj.bmSearch(text, phrase, mod);

    return 0;
}
