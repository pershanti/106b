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

void playOneGame(Lexicon& dictionary) {

        Boggle newBoggle = Boggle(dictionary, "");
        
        while(true){
            string guess;
            
            cout << "Enter a word. Or, press Enter to end your turn." << endl;
            
            getline(cin,guess);
            guess = toLowerCase(guess);
            
            if(guess.empty()){
                break;
            }
            
            if (newBoggle.checkWord(guess)){
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
        
        
       Set<string> restOfWords = newBoggle.computerWordSearch();
       for (string word : restOfWords){
           cout << word << endl;
       }
       return;
    
}
