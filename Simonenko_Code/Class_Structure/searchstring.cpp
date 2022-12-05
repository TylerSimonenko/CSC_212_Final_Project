// Include header file
#include "searchstring.h"



// CONSTRUCTOR
searchstring::searchstring(std::string inputFile, std::string outputFile) {
    
    // Set private values
    this->m_inputFile = inputFile + m_type;
    this->m_outputFile = outputFile + m_type;

}



// RUN PROJECT
void searchstring::runProject() {

    // Read given file
    readFile();

    // Get search phrase
    getPhrase();

    // Do Rabin-Karp method
    rabinKarp();

    // Do Boyer-Moore method
    boyerMoore();

    // Write the new file
    writeFile();

}



// READ FILE FUNCTION
void searchstring::readFile() {

    // Input stream
    std::ifstream inFile(m_inputFile);
    std::string line;

    // Getlines to fill "text" vector, use "index" to store locations of newlines
    while (std::getline(inFile, line)) {
        m_text.insert(m_text.end(), line.begin(), line.end());
        m_writeIdx.push_back(m_text.size());
    }

    // Get size of input text
    this->m_ts = m_text.size();

}



//GET SEARCH PHRASE FROM USER
void searchstring::getPhrase() {

    // Create string "phrase"
    std::string phrase;

    // Ask user to input the phrase to search for (can include whitespaces)
    std::cout << "Enter the search phrase: " << std::endl;
    std::getline(std::cin, phrase);

    // Copy user input into vector<char> m_search
    m_search.insert(m_search.end(), phrase.begin(), phrase.end());

    // Get size of search phrase
    this->m_ss = m_search.size();

}



// RABIN-KARP ALGORITHM
void searchstring::rabinKarp() {

    // Header printout for algorithm
    std::cout << "\r\n\nRABIN-KARP METHOD" << std::endl;

    // Preliminary
    int count = 0;

    // H value used in computation
    int h = 1;
    for (int i = 0; i < m_ss - 1; i++) {
        h = (h * m_charNum) % m_prime;
    }

    // Calculate hash value for "m_search" and "m_text"
    int searchHash = 0;
    int textHash = 0;
    for (int i = 0; i < m_ss; i++) {
        searchHash = (m_charNum * searchHash + m_search[i]) % m_prime;
        textHash = (m_charNum * textHash + m_text[i]) % m_prime;
    }
    
    // Do algorithm
    int i, j;
    int shiftNum = m_ts - m_ss;                 // Find how many times the "window" is shifted through text

    // Iterates until end of text
    for (i = 0; i <= shiftNum; i++) {

        // If search/text hash values match
        if (searchHash == textHash) {
            for (j = 0; j < m_ss; j++) {

                // Check for matching characters one by one
                if (m_text[i + j] != m_search[j])
                    break;
            
            }

            // Once end of search has been reached
            if (j == m_ss) {

                // Push index "i" to vector "location"
                m_RKIdx.push_back(i + 1);
                count++;

            }
        }
        
        // Rehash next window, remove leading character and add trailing character
        if (i < m_ts - m_ss) {

            // Recalculated hash value of window of "m_text"
            textHash = (m_charNum * (textHash - m_text[i] * h) + m_text[i + m_ss]) % m_prime;

            // If hash is negative
            if (textHash < 0) {

                // Make textHash positive
                textHash = (textHash + m_prime);
            
            }    
        }
    }

    // Print result
    print(count, m_RKIdx);

}



// BOYER-MOORE ALGORITHM
void searchstring::boyerMoore() {

    // Header printout for algorithm
    std::cout << "\r\n\nBOYER-MOORE METHOD" << std::endl;

    // Preliminary
    int count = 0;                          // Number of times the pattern occurs
    int s = 0;                              // Shift value (location) of pattern
    //std::vector<unsigned int> location;     // Locations of found patterns as vector<int>

    // Preprocessing function for bad characters
    badCharHeuristic();

    // Processing loop
    while (s <= (m_ts - m_ss)) {

        // Define "j" as one less than the search string size
        int j = m_ss - 1;

        // Reduce the value of j as m_text character matches that of m_string
        while (j >= 0 && m_search[j] == m_text[s + j]) {
            j--;
        }

        // Pattern has been found at current location
        if (j < 0) {

            // Add "s" value to location vector
            m_BMIdx.push_back(s + 1);
            count++;

            // Shift "s" so that next character in text aligns with the last occurrence within search
            if (s + m_ss < m_ts) {
                s += m_ss - m_badchar[m_text[s + m_ss]];
            }

            // Edge case for pattern occurring at end of text
            else {
                s += 1;
            }
            //s += (s + m_ss < m_ts) ? m_ss - m_badchar[m_text[s + m_ss]] : 1;
        }

        // Shift search so bad character of text aligns with last occurrence within search (max used to get positive shift)
        else {
            s += std::max(1, j - m_badchar[m_text[s + j]]);
        }
    }

    // Print results
    print(count, m_BMIdx);

    // For print formatting
    std::cout << std::endl;

}



// BAD CHARACTER HEURISTIC FOR B-M METHOD
void searchstring::badCharHeuristic() {

    // Initializing all occurrences as -1
    for (int i = 0; i < 256; i++) {
        m_badchar[i] = -1;
    }

    // Fills bad character array with actual bad characters
    for (int i = 0; i < m_ss; i++) {
        m_badchar[(int)m_search[i]] = i;
    }

}



// WRITE FILE FUNCTION
void searchstring::writeFile() {

    // Open our file with write permissions
    std::ofstream output_file(m_outputFile);

    // Count letters traversed
    int count = 0;
    int j = 0;

    // Use an iterator to traverse the outer dimension
    for (std::vector<char>::const_iterator i = (m_text).begin(); i != (m_text).end(); ++i) {

        // Check if there are multiple newlines
        if (count == m_writeIdx[j] && m_writeIdx[j] == m_writeIdx[j + 1]) {
            int temp = j;
            int step = 1;

            // Count how many newlines in a row there are
            while (m_writeIdx[j] == m_writeIdx[j + 1]) {
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
        else if (count == m_writeIdx[j] && m_writeIdx[j] != m_writeIdx[j + 1]) {
            output_file << '\n';
            j++;
        }

        // Output the letter, step count
        output_file << *i;
        count++;

    }

}



// PRINT R-K / B-M SEARCH RESULTS
void searchstring::print(int count, std::vector<int> indexes) {
    // If the search string is never found
    if (count == 0) {
        std::cout << "The pattern was not found.\r\nTry checking the search phrase's spelling and try again." << std::endl;
    }

    else {
        // Print total number of occurrences and locations
        std::cout << "The pattern was found a total of " << count << " time(s) at the following indexes: ";
        for (unsigned int i = 0; i < indexes.size(); i++) {

            // Print formatting
            if (i + 1 != indexes.size()) {
                std::cout << indexes[i] << ", ";
            }
            else {
                std::cout << indexes[i];
            }

        }
    }
}
