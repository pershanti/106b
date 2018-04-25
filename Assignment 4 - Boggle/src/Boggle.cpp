// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "Boggle.h"
#include "lexicon.h"
#include "grid.h"
#include "shuffle.h"
#include "random.h"
#include "strlib.h"
#include "set.h"
#include "hashset.h"
#include "bogglegui.h"
#include "math.h"

// letters on all 6 sides of every cube
static string CUBES[16] = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

// letters on every cube in 5x5 "Big Boggle" version (extension)
static string BIG_BOGGLE_CUBES[25] = {
   "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
   "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
   "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
   "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
   "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

Boggle::Boggle(Lexicon& dictionary, string boardText) {
    BoggleGUI::initialize(sqrt(boardSize),sqrt(boardSize));   
    
    gameDictionary = dictionary;
    Vector<int> cubeNumbers;
    
        if(boardSize == 16){ 
            for (int i=0; i<16; i++){
                int randomint = randomInteger(0,15);
                cubeNumbers.add(randomint);
            }
            for(int num : cubeNumbers){
                string word = CUBES[num];
                int randNum = randomInteger(0,5);
                char pickedChar = word[randNum];
                boardText += pickedChar;
            }
            currentBoard = Grid<char>(4,4);
            for(int i=0; i<4; i++){
                for(int j=0; j<4; j++){
                    currentBoard[i][j] = boardText[i*4 + j];
                    BoggleGUI::labelCube(i,j,boardText[i*4 + j]);
                }
            }
        }
        
        else if (boardSize == 25){
            for (int i=0; i<25; i++){
                int randomint = randomInteger(0,24);
                cubeNumbers.add(randomint);
            }
            for(int num : cubeNumbers){
                string word = BIG_BOGGLE_CUBES[num];
                int randNum = randomInteger(0,5);
                char pickedChar = word[randNum];
                boardText += pickedChar;
            }
            currentBoard = Grid<char>(5,5);
            for(int i=0; i<5; i++){
                for(int j=0; j<5; j++){
                    currentBoard[i][j] = boardText[i*5 + j];
                    BoggleGUI::labelCube(i,j,boardText[i*5 + j]);
                }
            }
        }       
} 

char Boggle::getLetter(int row, int col) {
    if(currentBoard.inBounds(row,col)){
        return currentBoard.get(row,col);
    }
    throw;
}

bool Boggle::checkWord(string word) {
    if(word.length() > 3 && gameDictionary.contains(word) && ! guessedWords.containsKey(word)){
        return true;
    }
    return false;   
}

bool Boggle::humanWordSearch(string word) {
    HashMap<int, HashSet<int>> usedLetters;
    //find the start letter
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            if(currentBoard.inBounds(i,j)){
                if(currentBoard[i][j] == toupper(word[0])){
                    cout << i << "," << j << endl;
                    if(searchFunction(word,i,j,usedLetters)){
                        humanScore += 1;
                        BoggleGUI::setScore(humanScore,BoggleGUI::HUMAN);
                        playerWords.add(word);
                        guessedWords.add(word,true);  
                        BoggleGUI::recordWord(word,BoggleGUI::HUMAN);
                        return true;
                    }
                }
            }
        }
    }
    
    return false;
}

Vector<Vector<int>> Boggle::findNeighborCubes(int row, int col){
    int rowNext;
    int rowPrev;
    int colNext;
    int colPrev;
    
    Vector<int> rows;
    Vector<int>cols;
    
    rowNext = row + 1;
    rowPrev = row - 1;
    colNext = col + 1;
    colPrev = col - 1;
    
    
    
    if (rowPrev >= 0){
        rows.add(rowPrev);
    }
    
    rows.add(row);
    
    if (rowNext<currentBoard.height()){
        rows.add(rowNext);
    }
    
    
    if (colPrev >= 0){
        cols.add(colPrev);
    }
    
    cols.add(col);
    
    if (colNext < currentBoard.width()){
        cols.add(colNext);
    }
    
    Vector<Vector<int>> results;
    results.add(rows);
    results.add(cols);
    return results;
    
    
    
}

bool Boggle::searchFunction(string word, int row, int column, HashMap<int, HashSet<int>> usedLetters) {
    cout << "..." << endl;
    cout << word << endl;
    cout << "current "<< row << "," << column << endl;
    
    BoggleGUI::setHighlighted(row,column);

    if(toupper(word[0]) == currentBoard.get(row,column) && ! usedLetters[row].contains(column)){
        cout << "continue path" << endl;
        if(word.length() == 1){
            cout<< "found the last letter"<<endl;
            return true;
        }
        usedLetters[row].add(column);
        Vector<Vector<int>> neighbors = findNeighborCubes(row,column);
        Vector<int> rows = neighbors[0];
        Vector<int> cols = neighbors[1];
        for(int r : rows){
            for (int c: cols){
                if(!(r == row && c == column) && ! usedLetters[r].contains(c)){
                    if(searchFunction(word.substr(1,word.length()-1),r,c,usedLetters)){
                        return true;
                    }
                }
            }
        }
    }
    BoggleGUI::setHighlighted(row,column,false);
    usedLetters[row].remove(column);
    return false;
}

string Boggle::getPlayerWords(){
    return playerWords.toString();
}

int Boggle::getScoreHuman() {
    return humanScore;
}

Set<string> Boggle::computerWordSearch() {
    HashMap<int, HashSet<int>> usedLetters;
    Set<string> all;
    Set<string> allWords;
    for(int i=0; i<currentBoard.width(); i++){
        for(int j=0; j<currentBoard.height(); j++){
            all.addAll(findAllWords("",i,j, usedLetters, allWords));
        }
    }
    computerScore = all.size();
    BoggleGUI::setScore(computerScore,BoggleGUI::COMPUTER);
    return all;
}

Set<string> Boggle::findAllWords(string current, int row, int column, HashMap<int, HashSet<int>> usedLetters, Set<string> allWords){
    
    
    string newWord = toLowerCase(current + currentBoard.get(row,column));
    
    if(guessedWords.get(newWord)){
        return allWords;
    }

    if(gameDictionary.contains(newWord) && newWord.length() > 3){
        allWords.add(newWord);
        BoggleGUI::recordWord(newWord,BoggleGUI::COMPUTER);
    }
    
    guessedWords.add(newWord, true);
    usedLetters[row].add(column);
    BoggleGUI::setHighlighted(row,column);
    cout << newWord << endl;
    
    if(gameDictionary.containsPrefix(newWord)){
        Vector<Vector<int>> neighbors = findNeighborCubes(row,column);
        Vector<int> rows = neighbors[0];
        Vector<int> cols = neighbors[1];
        for(int r : rows){
            for (int c: cols){
                if(!(r == row && c == column) && ! usedLetters[r].contains(c)){
                    allWords.addAll(findAllWords(newWord,r,c, usedLetters, allWords));
                }
            }
        }
    }
    
    
    usedLetters[row].remove(column);
    BoggleGUI::setHighlighted(row,column, false);
    return allWords;
}

int Boggle::getScoreComputer() {
    return computerScore;
}

ostream& operator<<(ostream& out, Boggle& boggle) {
    int width = boggle.currentBoard.width();
    for(int i=0; i<width; i++){
        for(int j=0; j<width; j++){
            out << boggle.currentBoard.get(i,j) << " ";
            if(i == width-1){
                out <<endl;
            }
        }
    }
    return out;
}
