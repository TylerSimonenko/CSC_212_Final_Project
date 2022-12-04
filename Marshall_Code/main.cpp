#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<char> getText() {

    string in_fname;
    cout << "Place desired file in same folder as program and enter file name: " << endl;

    cin >> in_fname;

    ifstream infile(in_fname);
    string row;

    vector<char> file; 

    while (getline(infile, row)) {

        int rowLen = row.length();
        for (int i = 0; i < rowLen; i++) { 

            file.push_back(row[i]);

        }

    }

    return file; 

}

vector<char> getPhrase() {

    vector<char> phrase; 
    char phraseChar; 
    cout << "Enter the phrase you're looking for" << endl;

    while (cin >> phraseChar) {
        
        phrase.push_back(phraseChar);

    }

    return phrase;
}

void bmSearch(vector<char> text, vector<char> phrase, int mod) {


 
}

void rkSearch(vector<char> text, vector<char> phrase, int mod) {

    int d = 256; 

    int phraseSize = phrase.size();
    int textSize = text.size();

    int phraseHash = 0;
    int textHash = 0;
    int k = 0;

    

    for (int i = 0; i < phraseSize; i++) {

        phraseHash += phrase[i];
        textHash += text[i];

    }

    for (int i = 0; i < phraseSize - 1; i++) {

        k = (k * d) % mod;

    }

    for (int i = 0; i <= textSize - phraseSize; i++) { 

        int j = 0; 
        if (phraseHash == textHash) { 

            for (j = 0; j < phraseSize; j++) {

                if (text[i + j] != phrase[j]) {

                    break;

                }

            }

            if (j == phraseSize) { 

                cout << "pattern found at index " << i << endl;

            } else {

                cout << "Pattern not found in the text" << endl;
            }

        }

        if (i < textSize - phraseSize) {

            textHash = (d * (textHash - text[i] * k) + text[i + phraseSize]) % mod;

            if (textHash < 0) {

                textHash = textHash + mod;

            }

        }

    }

}

int main() {

    vector<char> text = getText();
    vector<char> phrase = getPhrase();

    int mod = INT_MAX;

    rkSearch(text, phrase, mod);
    bmSearch(text, phrase, mod);

    return 0;
}
