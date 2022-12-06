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

    // Do Naive method
    naive();

    // Do Rabin-Karp method
    rabinKarp();

    // Do Boyer-Moore method
    boyerMoore();

    // Replace function
    replace();

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



// NAIVE ALGORITHM
void searchstring::naive() {

    // Header printout for algorithm
    std::cout << "\r\n\nNAIVE METHOD" << std::endl;

    // Preliminary
    int count = 0;
    int shiftNum = m_ts - m_ss;

    // Shift through entire text
    for (int i = 0; i <= shiftNum; i++) {
        int j;

        // Compare each character of search to text
        for (j = 0; j < m_ss; j++) {

            // If current character doesn't match between search/text
            if (m_text[i + j] != m_search[j])
                break;

        }

        // If all characters match
        if (j == m_ss) {

            // Push index value into "m_NIdx"
            m_NIdx.push_back(i);
            count++;

        }
    }

    // Print result
    print(count, m_NIdx);

}



// RABIN-KARP ALGORITHM
void searchstring::rabinKarp() {

    // Header printout for algorithm
    std::cout << "\r\n\nRABIN-KARP METHOD" << std::endl;

    // Preliminary
    int count = 0;
    int shiftNum = m_ts - m_ss;

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
                m_RKIdx.push_back(i);
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
    int shiftNum = m_ts - m_ss;

    // Preprocessing function for bad characters
    badCharHeuristic();

    // Processing loop
    while (s <= shiftNum) {

        // Define "j" as one less than the search string size
        int j = m_ss - 1;

        // Reduce the value of j as m_text character matches that of m_string
        while (j >= 0 && m_search[j] == m_text[s + j]) {
            j--;
        }

        // Pattern has been found at current location
        if (j < 0) {

            // Add "s" value to location vector
            m_BMIdx.push_back(s);
            count++;

            // Shift "s" so that next character in text aligns with the last occurrence within search
            if (s + m_ss < m_ts) {
                s += m_ss - m_badchar[m_text[s + m_ss]];
            }

            // Edge case for pattern occurring at end of text
            else {
                s += 1;
            }

        }

        // Shift search so bad character of text aligns with last occurrence within search (max used to get positive shift)
        else {
            s += std::max(1, j - m_badchar[m_text[s + j]]);
        }
    }

    // Print results
    print(count, m_BMIdx);
    std::cout << "\n\n";

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



// PRINT NAIVE/R-K/B-M SEARCH RESULTS
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
            if (i != indexes.size() - 1) {
                std::cout << indexes[i] << ", ";
            }
            else {
                std::cout << indexes[i];
            }

        }
    }
}



// REPLACE SEARCH PHRASE FUNCTION
void searchstring::replace() {

    // String "yesNo" to hold user input
    std::string yesNo;

    // Ask user to replace the search phrase
    if (m_NIdx.size() > 0 && m_RKIdx.size() > 0 && m_BMIdx.size() > 0) {
        
        // Print statement, take input
        std::cout << "\r\nWould you like to replace every instance of the search phrase in the given '.txt' file?\r\nType 'yes' or 'no' below:" << std::endl;
        std::getline(std::cin, yesNo);

        // YES
        if (yesNo == "yes") {

            // DELETE PHRASE FROM TEXT VECTOR        
            int count = 0;

            // Iterate through found index vector
            for (unsigned int i = 0; i < m_RKIdx.size(); i++) {

                // Erase the occurrence of the search phrase
                m_text.erase(m_text.begin() + m_RKIdx[i], m_text.begin() + m_RKIdx[i] + m_ss);

                // Recalculate index values to account for vector "shrinking" due to erasure
                if (i < m_RKIdx.size() - 1) {

                    // New index is now (previous index) - (size of deleted phrase)
                    for (unsigned int j = 1 + count; j < m_RKIdx.size(); j++) {
                        m_RKIdx[j] -= m_ss;         // Updated indexes for replacement!
                    }

                    // Step count so the for loop above edits only the subsequent indexes
                    count++;

                }
            }

            // User input replacement phrase
            count = 0;
            std::string phrase;
            std::cout << "Enter the replacement phrase: " << std::endl;
            std::getline(std::cin, phrase);

            // Copy user input into vector "replacement"
            std::vector<char> replacement;
            replacement.insert(replacement.end(), phrase.begin(), phrase.end());
            int rs = replacement.size();                    // Size of the replacement phrase

            // INSERT PHRASE FROM USER TO TEXT
            for (unsigned int i = 0; i < m_RKIdx.size(); i++) {
                m_text.insert(m_text.begin() + m_RKIdx[i], replacement.begin(), replacement.end());
                if (i < m_RKIdx.size()) {
                    for (unsigned int j = 1 + count; j < m_RKIdx.size(); j++) {
                        m_RKIdx[j] += rs;
                    }
                    count++;
                }
            }

            // Change index values of newline prints (For writeFile Function)
            changeNewline(rs);

        }


        // NO
        if (yesNo == "no") {
            std::cout << "The search phrase will not be replaced." << std::endl;
        }

    }
    
    else {
        std::cout << "The search phrase was never found. Check spelling or try a different phrase." << std::endl;
    }

}



// CHANGE NEWLINES INDEXES FUNCTION
void searchstring::changeNewline(int rs) {

    int newlineShift = rs - m_ss;
    for (unsigned int i = 0; i < m_RKIdx.size(); i++) {
        for (unsigned int j = 0; j < m_writeIdx.size(); j++) {
            m_writeIdx[j] += newlineShift;
        }
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
