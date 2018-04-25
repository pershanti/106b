// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "lexicon.h"
#include "grid.h"
#include "shuffle.h"
#include "random.h"
#include "strlib.h"
#include "Boggle.h"
#include "map.h"
#include "hashmap.h"
#include "vector.h"
#include "set.h"
#include "bogglegui.h"

void playOneGame(Lexicon& dictionary) {
        
        string boardChar;
        cout << "Enter board size" <<endl;
        
        getline(cin,boardChar);
        
        string letters = "";
        int boardSize = stringToInteger(boardChar);
        
        if (boardSize != 16 && boardSize != 25){
            cout << "enter custom string"<<endl;
            getline(cin,letters);
        }
        
        Boggle newBoggle = Boggle(dictionary, letters);
        newBoggle.boardSize = boardSize;
        
        while(true){
            string guess;
            BoggleGUI::clearHighlighting();
            cout << "Enter a word. Or, press Enter to end your turn." << endl;
            
            getline(cin,guess);
            guess = toLowerCase(guess);
            
            if(guess.empty()){
                break;
            }
            
            if (newBoggle.checkWord(guess)){
                cout << "word is okay"<<endl;
                if (newBoggle.humanWordSearch(guess)){
                    cout << "You found a new word! " << toUpperCase(guess) << endl;
                    cout << "..." << endl;
                    cout << "Your words: " << newBoggle.getPlayerWords() << endl;
                    cout << "Your score: " << newBoggle.getScoreHuman() << endl;
                }
                else{
                    cout<<"Word Not Found"<<endl;
                }
            }
            
            else{
                cout << "Invalid word" << endl;
            }
        }
        
       cout << "broke while" <<endl;
       Set<string> restOfWords = newBoggle.computerWordSearch();
       cout<<"Computer Results:"<<endl;
       cout << restOfWords.toString() << endl;
       return;
    
}
