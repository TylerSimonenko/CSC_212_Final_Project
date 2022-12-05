#include "search.h"

Search::Search(std::string word, std::string filename){
    this-> word = word;
    this-> filename = filename;
}

void Search::getFileContent(std::string fileName, std::vector< char > & vec){
    std::ifstream file;
    file.exceptions(
            std::ifstream::badbit
            | std::ifstream::failbit
            | std::ifstream::eofbit);
    file.open(fileName, std::ifstream::in | std::ifstream::binary);
    file.seekg(0, std::ios::end);
    std::streampos length(file.tellg());
    if (length){
        file.seekg(0, std::ios::beg);
        vec.resize(static_cast<std::size_t>(length));
        file.read(&vec.front(), static_cast<std::size_t>(length));
    }
}

void Search::naiveSearch(std::string pat, std::vector< char > txt, std::vector < int > &holdPos){
    int patternSize = pat.size();
    int textSize = txt.size();

    for (int i = 0; i <= textSize - patternSize; i++) {
        int j;
        for (j = 0; j < patternSize; j++)
            if (txt[i + j] != pat[j])
                break;
        if (j == patternSize){
            holdPos.push_back(i);
        }
    }
}

int Search::findMax(int a, int b){
    return (a > b) ? a : b;
}

void Search::badCharHeuristic(std::string str, int size, int badchar[256]){
    for (int i = 0; i < 256; i++){
        badchar[i] = -1;
    }
    for (int i = 0; i < size; i++){
        badchar[(int) str[i]] = i;
    }
}

void Search::search(std::vector< char > txt, std::string pat, std::vector < int > &holdPos){
    int patternSize = pat.size();
    int textSize = txt.size();
    int s = 0;

    int badchar[256];

    badCharHeuristic(pat, patternSize, badchar);

    while (s <= (textSize - patternSize)){
        int j = patternSize - 1;

        while (j >= 0 && pat[j] == txt[s + j]) {
            j--;
        }

        if (j < 0){
            holdPos.push_back(s);
            s += (s + patternSize < textSize) ? patternSize - badchar[txt[s + patternSize]] : 1;
        }
        else {
            s += findMax(1, j - badchar[txt[s + j]]);
        }
    }
}


void Search::rabinKarp(std::string pattern, std::vector< char > text, int q, std::vector < int > &holdPos){
    int patternSize = pattern.length();
    int textSize = text.size();
    int i, j;
    int patternHashVal = 0;
    int textHashVal = 0;
    int h = 1;

    for (i = 0; i < patternSize - 1; i++){
        h = (h * 10) % q;
    }
    for (i = 0; i < patternSize; i++){
        patternHashVal = (10 * patternHashVal + pattern[i]) % q;
        textHashVal = (10 * textHashVal + text[i]) % q;
    }
    for (i = 0; i < textSize - patternSize; i++){
        if (patternHashVal == textHashVal){
            for (j = 0; j < patternSize; j++) {
                if (text[i + j] != pattern[j]) {
                    break;
                }
            }
            if (j == patternSize){
                holdPos.push_back(i);
            }
        }
        if (i < textSize - patternSize){
            textHashVal = (10 * (textHashVal - text[i] * h) + text[i + patternSize]) % q;
            if (textHashVal < 0) {
                textHashVal = (textHashVal + q);
            }
        }
    }
}

void Search::writeFile(std::string filename) {
    std::ofstream output_file(filename);

    for (int c = 0; c < Search::vec.size(); c++) {
        output_file << Search::vec[c];
    }
}

void Search::setup(){
    getFileContent(Search::filename, Search::vec);
    rabinKarp(Search::word, Search::vec, 13, Search::holdPos);
    search(Search::vec, Search::word, Search::holdPos);
    naiveSearch(Search::word, Search::vec, Search::holdPos);
    for (int c = 0; c < Search::holdPos.size(); c++) {
        std::cout << Search::holdPos[c] << std::endl;
    }
}
