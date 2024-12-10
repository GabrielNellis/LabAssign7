#ifndef LabAssign7
#define LabAssign7
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <tuple>
#include <iterator>
#include <fstream> //for reading the text file
//#include "histograms.cpp"
struct funcObj {
    bool operator()(const std::string& a, const std::string& b) {
        return a.length() < b.length();
    }
};
using WORD = std::string; //for each word in the text file
using WORD_LIST = std::set<WORD>; //for each unique word in the text file
using WORD_FREQ_LIST = std::map<char, int>; //number of times each letter was used
using FREQ_WORD_LIST = std::multimap<int, WORD>; //number of times each word was used
using COUNTER = std::tuple<int, int, int>; //for counting letters, words, and lines
using LONGEST = std::priority_queue<WORD, std::vector<WORD>, funcObj>; //used for the histogram to help with the arrows...
//...since the word histogram is going to be horizontal
struct DICTION {
    COUNTER stats;
    WORD_LIST words;
    WORD_FREQ_LIST wordFreq;
    FREQ_WORD_LIST freqWord;
    LONGEST longWord;
};
//everything needs to be sorted ALPHABETICALLY
#endif LabAssign7

int maxWords(std::pair<const int, WORD>& e, int maxNum) { //used to get the word with the highest frequency and return the frequency
    return (e.first > maxNum ? e.first : maxNum);
}

void drawWords(DICTION& d) { //used for the word list (and horizontal histrogram)
    std::cout << "Word                         Frequency\n";
    std::cout << "--------------------------------------\n"; //38 dashes long
    int wordLength = 37-(d.longWord.top().length()); //37-longest word length to leave room for one number at the end
    int maxWord = 0; //used for the height of the histogram
    for (std::pair<const int, WORD> e : d.freqWord) { //specifying e for the function maxWords
        std::cout << e.second;
        maxWord = maxWords(e, maxWord); //getting the max word frequency while I am going through the list
        int difference = wordLength - e.second.length();
        for (int i = 0; i < difference; i++) std::cout << " "; //printing spaces between the word and number
        std::cout << e.first << "\n"; //------------------------- 25 dashes long
    }
    std::cout << "\nHistogram: \n";
    int longest = d.longWord.top().length();
    for (int i = maxWord; i > 0; i--) { //prints the lines I need for the histogram to show
        for (int j = 0; j < (15+longest); j++) std::cout << " "; //prints the initial spaces for the histogram
        for (auto e : d.freqWord) { //prints the stars for frequency used
            if (e.first >= i) std::cout << "* ";
            else std::cout << "  ";
        }
        std::cout << "\n";
    }
    for (int i = 0; i < (15 + (3 * d.words.size())); i++) { //just a big line of dashes based on the size of the words
        std::cout << "-";
    }
    std::cout << "\n";
    for (int i = 0; i < (15 + longest); i++) std::cout << " "; //to offset the up arrows
    for (int i = 0; i < d.words.size(); i++) std::cout << "^ ";
    std::cout << "\n";
    int counter = d.words.size(); //since I will decrement this and subtrace d.words.size() from this for the "/"'s
    int lines = 1;
    for (auto e : d.freqWord) { //printing the words, then arrows to their respective frequencies
        std::cout << e.second;
        for (int i = 0; i < (longest - e.second.length()); i++) std::cout << " ";
        for (int i = 0; i < 15; i++) std::cout << "-"; //to offset the arrows going up (also is the arrows going right)
        for (int i = 0; i < (d.words.size() - counter); i++) std::cout << "--";
        std::cout << "/ ";
        for (int i = 0; i < (d.words.size() - lines); i++) std::cout << "| ";
        std::cout << "\n";
        counter--;
        lines++;
    }
}

void drawLetters(DICTION& d) { //used for letter count (and vertical histogram)
    for (auto e : d.wordFreq) { //going through the letter map
        std::cout << e.first << " | ";
        for (int i = 0; i < 10 && i < e.second; i++) {
            std::cout << "*";
        }
        if (e.second > 10) {
            int a = e.second - 10;
            std::cout << " (" << a << ")";
        }
        std::cout << "\n";
    }
}

void showStats(DICTION& d) { //prints the data involving DICTION d
    std::cout << "Dictionary Stats: \nWords in Dictionary - "; //print the words in the dictionary here instead
    for (auto e : d.words) {
        std::cout << e << " ";
    }
    std::cout << "\n\n";
    std::cout << "Number of Letters: " << std::get<0>(d.stats) << "\n";
    std::cout << "Number of Words  : " << std::get<1>(d.stats) << "\n";
    std::cout << "Number of Lines  : " << std::get<2>(d.stats) << "\n \n"; 
    std::cout << "Letter Frequency: \n";
    drawLetters(d); 
    std::cout << "\nDictionary: \n";
    drawWords(d);
}

WORD getNextWord(DICTION& d, std::ifstream& file) { //going to be the ONLY time I read from the text file
    WORD w;
    char ch;
    bool inWord = false;
    file.get(ch);
    std::get<0>(d.stats)++;
    while (!file.eof()) { //while not at the end of the file
        if (isalpha(ch)) { // is ch in [A-Z, a-z]
            d.wordFreq[ch]++; //increments the letter that was used
            w.push_back(ch);
            inWord = true;
        }
        else if (inWord) {
            std::get<1>(d.stats)++;
            return w;
        }
        else if (ch == '\n') std::get<2>(d.stats)++; //gets all empty lines
        file.get(ch); //to keep the loop going
        std::get<0>(d.stats)++;
    }
    file.close(); //closes the text file after we're done reading from it (it only reaches this line when the file's empty)
    if (isalpha(ch)) std::get<1>(d.stats)++; //covers if the last letter is not from a-z or A-Z
    if (ch == '\n') std::get<2>(d.stats)++; //covers if the last letter is a new line
    return w;
}

FREQ_WORD_LIST::iterator findWord(WORD w, DICTION& d) {
    for (auto e = d.freqWord.begin(); e != d.freqWord.end(); e++) {
        if (w == e->second) return e;
    }
    return d.freqWord.end();
}

void buildDictionary(DICTION& d) {
    for (char c = 'a'; c <= 'z'; c++) { //loads the map with each char from a-z and A-Z
        d.wordFreq[c] = 0;
        d.wordFreq[char(toupper(c))] = 0;
    }
    std::ifstream file("text_file.txt");
    if (!file.eof()) std::get<2>(d.stats)++; //covers if the file is empty and if it isn't, then the first character starts the first line
    while (!file.eof()) {
        WORD tmp = getNextWord(d, file); //getting the word from the file
        d.words.insert(tmp); //automatically doesn't insert a second copy of the word
        FREQ_WORD_LIST::iterator t = findWord(tmp, d); //seeing if it's in the word list already
        FREQ_WORD_LIST::iterator e = d.freqWord.end();
        if (t == e) { //this line gives a massive error
            d.freqWord.insert({ 1, tmp }); //insert the new word into the word frequency list
        }
        else {
            int count = t->first;
            count++;
            d.freqWord.insert({ count, tmp }); //incrementing the count of that word in the list
            d.freqWord.erase(t);
        }
    }
    for (auto e : d.words) d.longWord.push(e); //since words has no duplicates in it
}

int main() {
    DICTION d;
    d.stats = { 0,0,0 }; //loading stats to be all 0
    buildDictionary(d); //loads d with everything about the text file
    showStats(d); //prints everything about d
    return 0;
}