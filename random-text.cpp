// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "simpio.h"
#include "vector.h"
#include "map.h"
#include "random.h"

using namespace std;

void loadMap(Map< Vector<string>, Vector<string> > & map, string file, int x);
void printText(Map< Vector<string>, Vector<string> > & map, int x);

int main() {
    // Intro //
    cout << "Welcome to CS 106B Random Writer ('N-Grams')." << endl;
    cout << "This program makes random text based on a document." << endl;
    cout << "Give me an input file and an 'N' value for groups" << endl;
    cout << "of words, and I'll create random text for you." << endl;
    cout << "" << endl;

    // Get file name //
    string filename = promptUserForFile("Input file name? ", "Unable to open that file. Try again. ");

    // Get N value //
    int n = 0;
    while(true) {
        n = getInteger("Value of N?", "Illegal integer format. Try again");
        if(n >= 2) break;
        cout << "N must be 2 or greater." << endl;
    }

    cout << "" << endl;

    Map< Vector<string>, Vector<string> > nGrams;
    loadMap(nGrams, filename, n);


    int nWords = 0;
    while(true) {
        while(true) {
            nWords = getInteger("# of random words to generate (0 to quit)?", "Illegal integer format. Try Again.");
            if(nWords >= n || nWords == 0) break;
            cout << "Must be at least " + integerToString(n) + " words." << endl;
            cout << "" << endl;
        }
        if(nWords == 0) break;
        printText(nGrams, nWords);

    }



    cout << "Exiting." << endl;
    return 0;
}

void loadMap(Map< Vector<string>, Vector<string> > & map, string file, int x) {
    ifstream infile;
    infile.open(file.c_str());
    string current = "";
    string next = "";
    Vector<string> window;

    // Init window //
    for(int i = 0; i < x - 1; i++) {
        infile >> current >> ws;
        window += current;
    }

    while(!infile.eof()) {
        // Associate nth word with n-1 key in the map //
        infile >> next >> ws;
        map[window] += next;

        window.remove(0);
        current = next;
        window += current;
    }

    // Reset stream //
    infile.close();
    infile.open(file.c_str());

    // Wrap around //
    for(int i = 0; i < x - 1; i++) {
        infile >> next >> ws;
        map[window] += next;

        window.remove(0);
        current = next;
        window += current;
    }

    infile.close();
}

void printText(Map< Vector<string>, Vector<string> > & map, int x) {
    // Get random key //
    Vector< Vector<string> > randKeys = map.keys();
    int rand = randomInteger(0, randKeys.size() - 1);
    Vector<string> window = randKeys[rand];
    int wordCount = window.size();

    cout << "... ";

    for(string word : window) {
        cout << word + " ";
    }

    string next = "";

    while(wordCount < x) {
        rand = randomInteger(0, map[window].size() - 1);
        next = map[window][rand];
        cout << next + " ";
        window.remove(0);
        window += next;
        wordCount ++;
    }

    cout << "..." << endl;
    cout << "" << endl;

}
