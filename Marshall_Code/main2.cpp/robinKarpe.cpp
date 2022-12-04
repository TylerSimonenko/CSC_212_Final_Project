#include "robinKarpe.h"

using namespace std;

vector<char> proj::getText() {

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

vector<char> proj::getPhrase() {

    string strPhrase; 
    vector<char> phrase; 
    char phraseChar; 

    cout << "Enter the phrase you're looking for" << endl;
    cin >> strPhrase; 

    copy(strPhrase.begin(), strPhrase.end(), back_inserter(phrase)); //adds the string to the back of the char vector

    return phrase;
}

void proj::bmSearch(vector<char> text, vector<char> phrase, int mod) {


 
}

void proj::rkSearch(vector<char> text, vector<char> phrase, int mod) {

    int d = 256; 

    int phraseSize = phrase.size();
    int textSize = text.size();

    int phraseHash = 0;

    for (int i = 0; i < phraseSize; i++) {

        phraseHash += phrase[i];

    }

    for (int i = 0; i <= textSize - phraseSize; i++) { 
        int textHash = 0;

        for (int j = i; j < phraseSize + i; j++) {

            textHash += text[j];

        }

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

/*
        if (i < textSize - phraseSize) {

            textHash = (d * (textHash - text[i] * k) + text[i + phraseSize]) % mod;

            if (textHash < 0) {

                textHash = textHash + mod;

            }

        }
        */

    }

}
