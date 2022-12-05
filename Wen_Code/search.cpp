#include <iostream>
#include <fstream>
#include <string>

using namespace std;
void search(char pat[], char txt[], int q)
{
    int M = strlen(pat);
    int N = strlen(txt);
    int i, j;
    int p = 0; 
    int t = 0; 
    int h = 1;
 
    for (i = 0; i < M-1; i++)
        h = (h*d)%q;
 
    for (i = 0; i < M; i++)
    {
        p = (d*p + pat[i])%q;
        t = (d*t + txt[i])%q;
    }
 
    for (i = 0; i <= N - M; i++)
    {
        if ( p == t )
        {
            for (j = 0; j < M; j++)
            {
                if (txt[i+j] != pat[j])
                    break;
            }
 
            
            if (j == M)
                
                cou++;
        }
 
      
        if ( i < N-M )
        {
            t = (d*(t - txt[i]*h) + txt[i+M])%q;
 
            if (t < 0)
            t = (t + q);
        }
    }
}
rabinkarp search
void search{ char *txt, char *pat}
 {  
    int m = strlen(pat);
 
    int n = strlen(txt);
    
    inr badchar[NO_OF_CHARS];
    
    badCharHeuristic(pat, m, badchar);
    }
    int s=0;
    while( s <=(n-m)) 
    { int j = m-1;
    while(j >= 0 && pat[j] == txt[s+j])
            j--;
    if( j<0)
    { 
      co++;
      cout<<"Th number of matches of \""<<pat<<"\" is "<<cou<<endl;
    cou=0;
    };
      
     else
     s += (s+m < n)? m-badchar[txt[s+m]] : 1;
     }
