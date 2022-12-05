using namespace std;
     int main()
     { using namespace std
      std::ifstream file;
    file.open("testfile.txt");
    
    file.getline(txt),
    clock_t begin = clock();
    search(txt,pat);
    clock_t end = clock();
    double passed_seconds = double(end - begin)*1000 / CLOCKS_PER_SEC;
    
    cout<<"Number of matches of \""<<pat<<"\" is "<<cou<<endl<<"Time taken:"<<elapsed_secs<<endl;
    
}
