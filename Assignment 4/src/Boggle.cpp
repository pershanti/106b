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
    gameDictionary = dictionary;
    string boardLetters = boardText;
    if (boardText == ""){
        //generate shuffled board
        Vector<int> cubeNumbers;
        //generate the positions of each cube
        for (int i=0; i<16; i++){
            int randomint = randomInteger(0,15);
            cubeNumbers.add(randomint);
        }
        
        //choose the letters
        for(int num : cubeNumbers){
            string word = CUBES[num];
            int randNum = randomInteger(0,5);
            char pickedChar = word[randNum];
            boardLetters += pickedChar;
        }
    }
    //create the board grid
    currentBoard = Grid<char>(4,4);
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            currentBoard[i][j] = boardLetters[i*4 + j];
        }
    }
    cout << currentBoard.toString();
} 

char Boggle::getLetter(int row, int col) {
    if(currentBoard.inBounds(row,col)){
        return currentBoard.get(row,col);
    }
    throw;
}

bool Boggle::checkWord(string word) {
    if(word.length() > 3 && gameDictionary.contains(word) && ! guessedWords[word]){
        return true;
    }
    return false;   
}

bool Boggle::humanWordSearch(string word) {
    HashMap<Vector<int>,bool> checked;
    Vector<int>rowCol;
    int row;
    int col;
    //find the start letter
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            if(currentBoard[i][j] == toupper(word[0])){
                row = i;
                col = j;
                if (searchFunction(word,row,col,checked)){
                    humanScore += 1;
                    guessedWords.add(word,true);
                    playerWords.add(word);
                    return true;
                }
            }
        }
     }
    
    return false;
}

bool Boggle::searchFunction(string word, int row, int column, HashMap<Vector<int>,bool> checkedLetters) {
    Vector<int>rowCol;
    rowCol.add(row);
    rowCol.add(column);
    
    
    if(checkedLetters.get(rowCol)){
        return false;
    }
    else if(tolower(currentBoard.get(row,column)) != word[0]){
        //unhighlight letter
        return false;
    }
    else if(word.length() == 0){
        return true;
    }
    for(int i = row-1; i = row+1; i++){
        for(int j = column-1; j = column+1; j++){
            if(i != j){
                if(currentBoard.inBounds(i,j)){
                    Vector<int> rowColumn;
                    rowColumn.add(i);
                    rowColumn.add(j);
                    checkedLetters.add(rowColumn,true);
                    //highlight letter       
                    if(searchFunction(word.substr(1, word.length()-1), i, j, checkedLetters)){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

string Boggle::getPlayerWords(){
    return playerWords.toString();
}

int Boggle::getScoreHuman() {
    return humanScore;
}

Set<string> Boggle::computerWordSearch() {
    Set<string> all =  findAllWords("",0,0);
    computerScore = all.size();
    return all;
}

Set<string> Boggle::findAllWords(string current, int row, int column){
    
    bool isLegitSearchPath = false;
    Set<string> allWords;
    
    string newWord = current + currentBoard.get(row,column);
    if(gameDictionary.contains(toLowerCase(newWord)) && ! guessedWords.get(toLowerCase(newWord))){
        allWords.add(toLowerCase(newWord));
        guessedWords.add(toLowerCase(newWord), true);
    }
    
    for(string word : gameDictionary){
        if(startsWith(word, toLowerCase(word))){
            isLegitSearchPath = true;
        }
    }
    
    if(isLegitSearchPath){
        for(int i = row-1; i=row+1; i++){
            for(int j = column-1; j=column+1; j++){
                if(i != j && currentBoard.inBounds(i,j)){
                    allWords.addAll(findAllWords(newWord,i,j));
                }
            }
        }
    }

    return allWords;
}

int Boggle::getScoreComputer() {
    return computerScore;
}

ostream& operator<<(ostream& out, Boggle& boggle) {
    // TODO: implement
    return out;
}
