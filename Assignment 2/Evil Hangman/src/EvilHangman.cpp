/*
 * File: EvilHangman.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * [TODO: write some documentation!]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "Recorder.h"
#include "vector.h"
#include "lexicon.h"
#include "strlib.h"
#include "hashmap.h"
#include "random.h"

using namespace std;

struct Game
{
public:
    bool wonGame = false;
    bool ranOutOfTurns = false;
    Lexicon dictionary;
    int testSpaces;
    int spaces = 0;
    int turns;
    char guess;
    string guessAsString;
    bool knowTrick;
    Vector<int> addLetters;
    Vector<char> currentWordPattern;
    Lexicon masterWordList;
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    
    Game() {}
    
   
    void askForLength(){
        while (spaces == 0){
            cout << "Please input an integer for how long the word should be" << endl;
            cin >> testSpaces;
            for(string word : dictionary){
                if (word.length() == testSpaces){
                    spaces = testSpaces;
                    addLetters = Vector<int>(spaces, 0);
                    break;
                }
            }

        }
    }
    void askForTurns(){
        cout << "How many turns would you like?" << endl;
        cin >> turns;
    }
    void askForTrick(){
        char answer;
        cout << "Would you like to know how many words are left at any given time? y for yes, n for no." << endl;
        cin >> answer;
        if (answer == 'y'){
            knowTrick = true;
        }
        else{
            knowTrick = false;
        }
    }
    void assembleMasterWordList(){
        for(string word : dictionary){
            if (word.length() == spaces) {
                masterWordList.add(word);
            }
        }
    }
    
    int calculateBiggestGroup(){
        Lexicon withLex;
        Lexicon withoutLex;
        int withoutCount = 0;
        int withCount = 0;
        for(string word : masterWordList){
            if (stringContains(word, guessAsString)) {
                  withCount += 1;
                  withLex.add(word);
             }
            else{
                withoutCount +=1;
                withoutLex.add(word);
            }
        }
        if(withoutCount >= withCount) {
            cout << "Incorrect guess" << endl;
            masterWordList = withoutLex;
            return 1;
        }
        else {
            masterWordList = withLex;
            return 0;
        }
    }
    void createWordFamilies(){
        
        HashMap<Vector<int>,Vector<string>> families;
        //find all the words with guess in it
        //for each word, create a list of the spots where it has the letter
        //check the map to see if that list exists, and add the word to the list
        //if it doesn't exist, create a new entry for that family and a list with that word
        
        for (string word : masterWordList ){
            if (stringContains(word,guessAsString)){
                Vector<int> whereLetter;
                for (int c=0; c < word.length(); c++){
                    if (word[c] == guess){
                        whereLetter.add(c);
                    }
                }
                if(families.containsKey(whereLetter)){
                    families[whereLetter].add(word);
                }
                else{
                    Vector<string> newList;
                    newList.add(word);
                    families.add(whereLetter, newList);
                    
                }
            }
        }
        cout << families.keys() << endl;
        Vector<int> maxKey;
        int maxSize=0;
        //find the longest list
        for(Vector<int> family : families){
            if(families[family].size() > maxSize){
                maxSize = families[family].size();
                maxKey = family;
            }
        }
        masterWordList.clear();
        addLetters = maxKey;
        for (string word : families[maxKey]){
            masterWordList.add(word);
        }
    }
    
    void chooseAndDisplayResult(){
        for(int num : addLetters){
            currentWordPattern[num] = guess;
        }

    }
    
    int runGame(){
        dictionary = Lexicon("EnglishWords.dat");
        askForLength();
        askForTurns();
        askForTrick();
        assembleMasterWordList();
        currentWordPattern = Vector<char>(spaces,'-');
        
        for(int i=0; i<turns; i++){
            if(knowTrick){
                cout << "Words Left: " << masterWordList.size() << endl;
            }
            cout << "Turns left: " << i;
            cout << "Letters left: " << alphabet << endl;
            
            for(int i=0; i<currentWordPattern.size(); i++) {
                if(currentWordPattern[i] == '-'){
                    cout << "  ___  ";
                }
                else{
                    cout << currentWordPattern[i];
                }
            }
            
            cout << '\n';
            
            if(i == turns-1){
                cout << "last turn!";
            }
            //exhausted the alphabet
            if(alphabet.length() == 0){
                cout << "no more letters :( ";
                return 0;
            }
            
            guess = '-';

            cout << "Enter a guess." << endl;
            cin >>  guess;
            guess = tolower(guess);
            guessAsString = charToString(guess);
            
            while (! stringContains(alphabet, guessAsString)){
                cout << "You already guessed that letter!"<< endl;
                cin >>  guess;
                guess = tolower(guess);
                guessAsString = charToString(guess);
            }
            
            
            alphabet = stringReplace(alphabet,guessAsString,"");
            
            //ending the game
                 if(calculateBiggestGroup() == 0){
                     createWordFamilies();
                     chooseAndDisplayResult();
                     if(masterWordList.size() <= 2){
                         for(char letter : currentWordPattern){
                             if (letter == '-'){
                                 letter = guess;
                             }
                         }
                         string finalGuess = "";
                         for(char c : currentWordPattern){
                             finalGuess.push_back(c);
                         }
                         if (masterWordList.contains(finalGuess)){
                             cout << "You win!" << endl;
                             return 1;
                         }

                    }
                }
            }
        //ran out of turns
        cout << "no more letters :(";
        return 0;
     }
};

int main() {
    char playAgain;
    Game myNewGame = Game();
    int play = myNewGame.runGame();
    if (play == 0){
        cout << "You lost!!";
    }
    else if(play == 1){
        cout << "You won!!!!! Way to go!!!!";
    }
    cout << "Play again? y or n" << endl;  
    cin >> playAgain;
    if(playAgain == 'y'){
        myNewGame = Game();
    }
    
    return 0;
}

