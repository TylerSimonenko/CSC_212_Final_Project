// Including Libs
#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>

// Function Prototyping
void readFile(std::vector<char>& text, std::string filename);
void writeFile(std::vector<char>& text, std::string outputName);
void rabinKarp(std::string search, std::string stringFull, int count);
void boyerMoore(std::string txt, std::string pat, int count);
void badCharHeuristic(std::string str, int size, int badchar[256]);



// Main Function
int main() {

    std::string filename;
    std::string outputName;
    std::vector<char> text;
    std::cout << "Please enter the input filename: ";
    std::cin >> filename;

    std::cout << "Please enter the output filename: ";
    std::cin >> outputName;

    readFile(text, filename);
    writeFile(text, outputName);

    
    //int count = 0;
    //std::string stringFull;
    //std::string search;
    //
    //std::cout << "Enter a string: ";
    //std::cin >> stringFull;

    //std::cout << "Enter the string to search for: ";
    //std::cin >> search;

    //rabinKarp(stringFull, search, count);
    //boyerMoore(stringFull, search, count);
}



// Read File Function
void readFile(std::vector<char>& text, std::string filename) {

    std::ifstream inFile(filename);
    std::string line;

    while (std::getline(inFile, line)) {
        std::istringstream stream(line);
        stream >> std::noskipws;
        char val;
        while (stream >> val) {
            text.push_back(val);
        }
    }
}



// Create final output file
void writeFile(std::vector<char>& text, std::string outputName) {
    // Open our file with write permissions
    std::ofstream output_file(outputName);

    // Use an iterator to traverse the outer dimension
    for (std::vector<char>::const_iterator i = (text).begin(); i != (text).end(); ++i) {
        // Use an interator to traverse the inner dimention
        output_file << *i;
    }

}








// Rabin-Karp Algorithm
void rabinKarp(std::string stringFull, std::string search, int count) {
    
    // Sizes of search string and full string
    int m = search.size();
    int n = stringFull.size();

    // Values
    int h = 1;
    int d = 256;
    int q = 103;

    // Find something here
    for (int i = 0; i < m - 1; i++) {
        h = (h * d) % q;
    }

    // Calculate hash value for search and stringFull
    int p = 0;
    int t = 0;
    for (int i = 0; i < m; i++) {
        p = (d * p + search[i]) % q;
        t = (d * t + stringFull[i]) % q;
    }

    // Find the match
    int i, j;
    for (i = 0; i <= n - m; i++) {
        if (p == t) {
            for (j = 0; j < m; j++) {
                if (stringFull[i + j] != search[j])
                    break;
            }

            if (j == m) {
                std::cout << "Pattern is found at position: " << i + 1 << std::endl;
                count++;
            }
        }

        if (i < n - m) {
            t = (d * (t - stringFull[i] * h) + stringFull[i + m]) % q;

            if (t < 0)
                t = (t + q);
        }
    }

    std::cout << "The pattern was found a total of " << count << " times!" << std::endl;

}



// Boyer-Moore Algorithm
void boyerMoore(std::string txt, std::string pat, int count) {
	int m = pat.size();
	int n = txt.size();

	int badchar[256];

	badCharHeuristic(pat, m, badchar);

	int s = 0;

	while (s <= (n - m)) {
		int j = m - 1;

		while (j >= 0 && pat[j] == txt[s + j])
			j--;

		if (j < 0) {
			std::cout << "Pattern occurs at shift: " << s << std::endl;
            count++;

			s += (s + m < n) ? m - badchar[txt[s + m]] : 1;

		}

        else {
            s += std::max(1, j - badchar[txt[s + j]]);
        }
	}

    std::cout << "The pattern was found a total of " << count << " times!" << std::endl;

}



// Bad Character Heuristic Method
void badCharHeuristic(std::string str, int size, int badchar[256]) {
    int i;

    for (i = 0; i < 256; i++)
        badchar[i] = -1;

    for (i = 0; i < size; i++)
        badchar[(int)str[i]] = i;
}


