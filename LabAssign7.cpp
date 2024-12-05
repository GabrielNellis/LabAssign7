#ifndef LabAssign7
#define LabAssign7
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include "histograms.cpp"
#include "text_file.txt"
using WORD = std::string; //for each word in the text file
using WORD_LIST = set<WORD>; //for each unique word in the text file
using WORD_FREQ_LIST = map<char, int>; //number of times each letter was used
using FREQ_WORD_LIST = multimap<int, WORD>; //number of times each word was used
using COUNTER = tuple<int, int, int>; //for counting letters, words, and lines
using LONGEST = priority_queue<WORD>; //used for the histogram to help with the arrows
//since histogram is going to be horizontal, like the example
using namespace std;
//everything needs to be sorted ALPHABETICALLY
#endif LabAssign7
vector<std::string> test{"hello", "hi", "test", "test2", "test"};

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
    WORD_FREQ_LIST m;
    for (char c = 'a'; c != 'z'; c++) { //loads the map with each char from a-z
        m.insert({ c, 0 });
    }
    for (char c = 'A'; c != 'Z'; c++) { //loads the map with each char from A-Z (since the ASCII is 32 bits off)
        m.insert({ c,0 });
    }
    d.wordFreq = m;
    std::cin.get(ch); //initializes the while loop
    while (!std::cin.eof()) //while ???
    {
        if (isalpha(ch)) // is ch in [A-Z, a-z]
        {
            w.push_back(ch);
            inWord = true;
        }
        else if (inWord) return w;
        std::cin.get(ch); //keeps the loop going for the length of the text file
    }
    return w;
}

void showStats(DICTION d) {
    cout << "Dictionary Stats \n \n";
    cout << "Number of Letters: " << d.stats.first << "\n";
    cout << "Number of Words  : " << d.stats.second << "\n";
    cout << "Number of Lines  : " << d.stats.third << "\n";
}

DICTION buildDictionary(DICTION& d) {
    for (auto t : test) {

    }
}

int main()
{
    DICTION d{ {0,0,0} };
    buildDictionary(d);
    showStats(d);
    drawHistograms(d);
    return 0;
}
//for auto cmp=[](std::string left, std::string right){return left.length()<right.length()};