// Including Libs
#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>

// Function Prototyping
void readFile(std::vector<char>& text, std::string filename, std::vector<int>& index);          // Read in .txt files
void writeFile(std::vector<char>& text, std::string outputName, std::vector<int>& index);       // Write out new .txt file
void rabinKarp(std::vector<char>& text, std::vector<char>& search);                             // Rabin-Karp method
void boyerMoore(std::vector<char>& text, std::vector<char>& search);                            // Boyer-Moore method
void badCharHeuristic(std::vector<char>& search, int size, int badchar[256]);                   // Component of Boyer-Moore method
// NAIVE METHOD     (Need to include this)


// Main Function
int main() {

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
    std::vector<char> search;

    // Read .txt file
    readFile(text, filename, index);

    // Search phrase (NEED THIS TO BE A USER INPUT TERM INSTEAD)
    search = {'t', 'h', 'e'};

    // Do algorithms
    rabinKarp(text, search);
    boyerMoore(text, search);

    // Write output file
    writeFile(text, outputName, index);

    return 0;
}



// READ FILE FUNCTION
void readFile(std::vector<char>& text, std::string filename, std::vector<int>& index) {

    // Input stream
    std::ifstream inFile(filename);
    std::string line;
    
    // Getlines to fill "text" vector, use "index" to store locations of newlines
    while (std::getline(inFile, line)) {
        text.insert(text.end(), line.begin(), line.end());
        index.push_back(text.size());
    }

}



// WRITE FILE FUNCTION
void writeFile(std::vector<char>& text, std::string outputName, std::vector<int>& index) {

    // Open our file with write permissions
    std::ofstream output_file(outputName);

    // Count letters traversed
    int count = 0;
    int j = 0;

    // Use an iterator to traverse the outer dimension
    for (std::vector<char>::const_iterator i = (text).begin(); i != (text).end(); ++i) {

        // Check if there are multiple newlines
        if (count == index[j] && index[j] == index[j + 1]) {
            int temp = j;
            int step = 1;

            // Count how many newlines in a row there are
            while (index[j] == index[j + 1]) {
                step++;
                j++;
            }

            // Reset "j" to original location
            j = temp;

            // Output as many newlines as there are in a row
            for (int i = 0; i < step; i++) {
                output_file << '\n';
                j++;
            }
        }

        // Check if there is a single newline
        else if (count == index[j] && index[j] != index[j + 1]) {
            output_file << '\n';
            j++;
        }
        
        // Output the letter, step count
        output_file << *i;
        count++;

    }

}



// RABIN-KARP ALGORITHM     (Comment this out a bit more)
void rabinKarp(std::vector<char>& text, std::vector<char>& search) {
    
    // Count number of occurrences
    int count = 0;

    // Sizes of search string and full string
    int m = search.size();
    int n = text.size();

    // Values
    int h = 1;
    int d = 256;            // Number of possible characters
    int q = 103;            // Prime number (higher reduces collisions)

    // Find something here
    for (int i = 0; i < m - 1; i++) {
        h = (h * d) % q;
    }

    // Calculate hash value for search and stringFull
    int p = 0;
    int t = 0;
    for (int i = 0; i < m; i++) {
        p = (d * p + search[i]) % q;
        t = (d * t + text[i]) % q;
    }

    // Find the match
    int i, j;
    for (i = 0; i <= n - m; i++) {
        if (p == t) {
            for (j = 0; j < m; j++) {
                if (text[i + j] != search[j])
                    break;
            }

            if (j == m) {
                std::cout << "Pattern is found at position: " << i + 1 << std::endl;
                count++;
            }
        }

        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + m]) % q;

            if (t < 0)
                t = (t + q);
        }
    }

    std::cout << "The pattern was found a total of " << count << " times!" << std::endl;

}



// BOYER-MOORE ALGORITHM        (Comment this out a bit more)
void boyerMoore(std::vector<char>& text, std::vector<char>& search) {
	
    // Count number of occurrences
    int count = 0;
    
    int m = search.size();
	int n = text.size();

	int badchar[256];

	badCharHeuristic(search, m, badchar);

	int s = 0;

	while (s <= (n - m)) {
		int j = m - 1;

		while (j >= 0 && search[j] == text[s + j])
			j--;

		if (j < 0) {
			std::cout << "Pattern occurs at index: " << s + 1 << std::endl;
            count++;

			s += (s + m < n) ? m - badchar[text[s + m]] : 1;

		}

        else {
            s += std::max(1, j - badchar[text[s + j]]);
        }
	}

    std::cout << "The pattern was found a total of " << count << " times!" << std::endl;

}



// BAD CHARACTER HEURISTIC FOR B-M METHOD       (Comment out a bit more)
void badCharHeuristic(std::vector<char>& search, int size, int badchar[256]) {
    int i;

    for (i = 0; i < 256; i++)
        badchar[i] = -1;

    for (i = 0; i < size; i++)
        badchar[(int)search[i]] = i;
}


