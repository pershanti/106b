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

using namespace std;

int main() {

    //set up the dictionary
    Lexicon english("EnglishWords.dat");

    int testSpaces;
    int spaces = 0;
    //ask the user to input an integer (number of spaces)
    //check that there is a word of that length in the dictionary
    while (spaces == 0){
        cout << "Please input an integer for how long the word should be" << endl;
        cin >> testSpaces;
        for(string word : english){
            if (word.length() == testSpaces){
                spaces = testSpaces;
                break;
            }
            else{
                cout << "No english words of this length found." << endl;
            }
        }
    }

   //ask user to input a number of turns (integer)
    int turns;
    cout << "How many turns would you like?" << endl;
    cin >> turns;

    //ask if they would like to know number of remaining words
   string knowTrick;
   cout << "Would you like to know how many words are left at any given time? Y for yes, N for no." << endl;
   cin >> knowTrick;
   knowTrick = toLowerCase(knowTrick);


   //construct list of potential words
    Lexicon masterWordList;
    for(string word : masterWordList){
        if (word.length() == spaces) {
            masterWordList.add(word);
        }
    }

    string alphabet = "abcdefghijklmnopqrstuvwxyz";


   for(int i=0; i<turns; i++){]
       char guess;
       while (! stringContains(charToString(toLowerCase(guess)), alphabet)){
           cout << "Enter a letter to guess. If you're seeing this again, it means you already guessed that letter!";
           cin >>  guess;
       }
       guess = toLowerCase(guess);
       //create word families
   }

         //prompt user for letter
         //calculate largest pattern group of remaining words
         //tell user if correct or incorrect
         //fill in the spaces with that letter
         //remove the word from the remaining words
         //if length of remaining words == 1, end the game, tell them they lose, present the other word
         //print number of remaining words












    // [TODO: Fill this in!]
    // [TODO: Don't forget to call the recordTurnInfo function
    //        at the start of each turn and the recordGameEnd
    //        function at the end of the game! It's necessary
    //        for our autograders to function.]
    return 0;
}

