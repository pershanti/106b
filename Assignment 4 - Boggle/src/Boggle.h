// This is a .h file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include "lexicon.h"
#include "grid.h"
#include "shuffle.h"
#include "random.h"
#include "strlib.h"
#include "map.h"
#include "hashmap.h"
#include "vector.h"
#include "hashset.h"
#include "bogglegui.h"

using namespace std;

class Boggle {
public:
    Boggle(Lexicon& dictionary, string boardText = "");
    int boardSize = 16;
    char getLetter(int row, int col);
    bool checkWord(string word);
    bool humanWordSearch(string word);
    Set<string> computerWordSearch();
    int getScoreHuman();
    int getScoreComputer();
    string getPlayerWords();
    bool searchFunction(string word, int row, int column, HashMap<int, HashSet<int>>  usedLetters);
    Set<string> findAllWords(string current, int row, int column, HashMap<int, HashSet<int> > usedLetters, Set<string> allWords);
    Vector<Vector<int>> findNeighborCubes(int row, int col);

    // TODO: add any other member functions/variables necessary
    friend ostream& operator<<(ostream& out, Boggle& boggle);

private:
    Grid<char> currentBoard;
    int humanScore = 0;
    int computerScore = 0;
    HashMap<string, bool> guessedWords;
    Vector<string> playerWords;
    Vector<string> computerWords;
    Lexicon gameDictionary;
    
};

#endif // _boggle_h
