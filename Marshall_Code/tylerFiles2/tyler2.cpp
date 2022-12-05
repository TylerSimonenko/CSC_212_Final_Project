#include "tyler.h"

// Function Prototyping
void readFile(std::vector<char>& text, std::string filename, std::vector<int>& index);          // Read in .txt files
void writeFile(std::vector<char>& text, std::string outputName, std::vector<int>& index);       // Write out new .txt file
void rabinKarp(std::vector<char>& text, std::vector<char>& search);                             // Rabin-Karp method
void boyerMoore(std::vector<char>& text, std::vector<char>& search);                            // Boyer-Moore method
void badCharHeuristic(std::vector<char>& search, int size, int badchar[256]);                   // Component of Boyer-Moore method
// NAIVE METHOD     (Need to include this)

// READ FILE FUNCTION
void proj::readFile(std::vector<char>& text, std::string filename, std::vector<int>& index) {

    // Input stream
    std::ifstream inFile(filename);
    std::string line;
    
    // Getlines to fill "text" vector, use "index" to store locations of newlines
    while (std::getline(inFile, line)) {
        text.insert(text.end(), line.begin(), line.end());
        index.push_back(text.size());
    }

}

//GET SEARCH PHRASE FROM USER
std::vector<char> proj::getPhrase() {

    std::string strPhrase; 
    std::vector<char> phrase; 
    char phraseChar; 

    std::cout << "Enter the phrase you're looking for" << std::endl;
    std::cin >> strPhrase; 

    copy(strPhrase.begin(), strPhrase.end(), back_inserter(phrase)); //adds the string to the back of the char vector

    return phrase;
}

// WRITE FILE FUNCTION
void proj::writeFile(std::vector<char>& text, std::string outputName, std::vector<int>& index) {

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
std::vector<int> proj::rabinKarp(std::vector<char>& text, std::vector<char>& search, bool& found) {
    
    std::vector<int> foundIndex;
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
                foundIndex.push_back(i);
                found = 1;
            }
        }

        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + m]) % q;

            if (t < 0)
                t = (t + q);
        }
    }

    std::cout << "The pattern was found a total of " << count << " times!" << std::endl;

    return foundIndex; 
}



// BOYER-MOORE ALGORITHM        (Comment this out a bit more)
void proj::boyerMoore(std::vector<char>& text, std::vector<char>& search) {
	
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



//REPLACE THE SEARCH PHRASE WITH A NEW PHRASE
void proj::replace(std::vector<char>& text, std::vector<int> foundIndex, std::vector<char> search, bool found) {
    char yesOrNo;

    if (found == 1) {
        std::cout << "Would you like to replace the search phrase with another phrase in the text? (enter y for yes, n for no): " << std::endl;

        std::cin >> yesOrNo;

        if (yesOrNo == 'y') {
            std::string newPhrase;
            std::vector<char> nextPhrase;

            std::cout << "Enter the phrase you'd like to replace your search with: " << std::endl;

            std::cin >> newPhrase; 

            copy(newPhrase.begin(), newPhrase.end(), back_inserter(nextPhrase)); //adds the string to the back of the char vector

            std::cout << std::endl;
            for (int i = 0; i < foundIndex.size(); i++) {

                int curIndex = foundIndex[i];
                text.erase(text.begin() + curIndex, text.begin() + curIndex + search.size());
                text.insert(text.begin() + curIndex, nextPhrase.begin(), nextPhrase.end());

            }

        }
        
    }

}



// BAD CHARACTER HEURISTIC FOR B-M METHOD       (Comment out a bit more)
void badCharHeuristic(std::vector<char>& search, int size, int badchar[256]) {
    int i;

    for (i = 0; i < 256; i++)
        badchar[i] = -1;

    for (i = 0; i < size; i++)
        badchar[(int)search[i]] = i;
}

