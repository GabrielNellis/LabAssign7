#ifndef histograms.cpp
#define histograms.cpp
#include <iostream>
#include "LabAssign7.cpp"
extern struct DICTION
#endif histograms.cpp
void drawWords(DICTION d) { //used for the word list (and horizontal histrogram)

}

void drawLetters(DICTION d) { //used for letter count (and vertical histogram)
	for (auto a : d.freqWord) { //going through the letter map
		
	}
}

void showStats(DICTION d) {
    cout << "Dictionary Stats \n \n"; //print the words in the dictionary here instead
    cout << "Number of Letters: " << d.stats.first << "\n";
    cout << "Number of Words  : " << d.stats.second << "\n";
    cout << "Number of Lines  : " << d.stats.third << "\n";
}