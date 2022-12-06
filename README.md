# **CSC 212 - Final Project**
*Data Structures and Algorithms: String Search I*


**General Information:**

The group's final term project was to implement two different *string search* algorithms. These two algorithms, the **Rabin-Karp** method and the **Boyer-Moore** method, were implemented using general C++ data structures - mostly vectors and strings. To show more in depth analysis, the two algorithms mentioned were compared with the **Brute Force** method, also known as the **Naive Method** - this method is a much simpler and time inefficient approach to String Search, and had been implemented to provide a "baseline" of how quickly the other two algorithms should run. 


The goal of the group's project was to create an algorithm using the three String Search methods which would act as a "**find and replace**" function given an input text, say, through a given ".txt" file. The user could provide a text file, as long as they would like, provide a certain phrase as a string to find within the overall text file, replace that phrase with a secondary replacement phrase, and then view the updated output text file (maintaining space formatting and such). The code successfully finds every instance of a given phrase (case sensitive) within the text file and displays the total number of occurrences, the indexes in which the phrase occurs, and will replace a given phrase with a secondary replacement phrase given by the user. 


The code has been implemented in class/header structure, with each string algorithm separated to be within its own member function. The final iteration of the group's code can be found within the "FINAL_CODE/" folder within the repository. To use the code, one must define two command line arguments, taken in the format "input output". The "input" phrase is the name of the file being read into the program, and the "output" phrase is the name of the new edited text file that the algorithm will produce. All dependencies exist within the code itself - there is no need to download any other softwares/libraries to run the algorithm. As long as the text file (to be read by the program) exists within the program files, everything should work fine. 


The full functionality of the project is not entirely complete. While it is absolutely true that the **implementation of the three algorithms is successful**, the specific use case regarding certain text formatting can result in unwanted formatting issues. For example: The "find" functionality will always work, no matter the formatting of the input .txt file. Similarly, the "replace" functionality will also work, successfully replacing each occurrence of a given search phrase with a replacement phrase defined by the user. The replacement phrase need not be the same size as the search string, nor must it disallow whitespaces - if the user were to replace a search phrase "the" with the replacement phrase "THIS IS A NEW PHRASE", the algorithm completes this task. The issues lie in the "writeFile" formatting when reading in a text file that includes multiple newlines. For a single-line text file, the "writeFile" function works as intended. and the formatting of the original input file is preserved. Adversely, if the user reads in a text file that includes multiple newlines, AND the user would like to replace a search phrase with a replacement phrase of a different size, the **ooutput formatting** is the only thing that falters, and the formatting of the original text file is not preserved. It can be observed that both the "find" phrase and "replace" phrase funcionality works as intended.
