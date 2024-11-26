#ifndef LabAssign7
#define LabAssign7
#include <iostream>
#include <vector>
#include <queue>
using WORD = string; //for each word in the text file
using WORD_LIST = set<WORD>; //for each unique word in the text file
using WORD_FREQ_LIST = map<char, int>; //number of times each letter was used
using FREQ_WORD_LIST = multimap<int, WORD>; //number of times each word was used
using COUNTER = tuple<int, int, int>; //for counting letters, words, and lines
using LONGEST = priority_queue<WORD>; //used for the histogram to help with the arrows
//since histogram is going to be horizontal, like the example
using namespace std;
//everything needs to be sorted ALPHABETICALLY
#endif LabAssign7
struct DICTION {
    COUNTER stats;
    WORD_LIST words;
    WORD_FREQ_LIST wordFreq;
    FREQ_WORD_LIST freqWord;
    LONGEST longWord;
}; 
WORD getNextWord(DICTION& d) {
    WORD w;
    char ch;
    bool inWord = false;
    std::cin.get(ch);
    while (!std::cin.eof())
    {
        if (isalpha(ch)) // is ch in [A-Z, a-z]
        {
            w.push_back(ch);
            inWord = true;
        }
        else if (inWord) return w;
        std::cin.get(ch);
    }
    return w;
}
int main()
{
    cout << "Hello World!\n";
}
