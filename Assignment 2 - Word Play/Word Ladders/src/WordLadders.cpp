/*
 * File: WordLadders.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "RecordLadders.h"
#include "vector.h"
#include "lexicon.h"
#include "queue.h"
#include "hashmap.h"
#include "strlib.h"

using namespace std;

int main() {

    //set up the dictionary
    Lexicon english("EnglishWords.dat");

    //create a list of used words
    HashMap<string, bool> usedWords;

    //define the alphabet
    string alphabet = "abcdefghijklmnopqrstuvwxyz";

    //ask for input of two words
    string wordA = "";
    string wordB = "";

    //prompt for a valid english word for each entry
    while(! english.contains(wordA)){
        cout << "Please enter a valid english word: " << endl;
        cin >> wordA;
    }

    while(! english.contains(wordB)){
        cout << "Please enter a valid english word2: "<< endl;
        cin >> wordB;
    }

    wordA = toLowerCase(wordA);
    wordB = toLowerCase(wordB);

    //add wordA to the list of used words
    usedWords.add(wordA, true);

    //compare the lengths of the words and return no ladder if different
    if(wordA.length() != wordB.length()){
        recordNoLadderBetween(wordA, wordB);
        cout << "no ladder found - words are different length";
        return 0;
    }

    //create a queue for the word ladders
    Queue<Vector<string>> ladderQueue = Queue<Vector<string>>();
    Vector<string> starter;
    starter.add(wordA);
    ladderQueue.add(starter);

    while(! ladderQueue.isEmpty()){
        //dequeue the first ladder
        Vector<string> ladder = ladderQueue.dequeue();
        string lastWord = ladder[ladder.size() - 1];
        //check if this ladder has the answer
        if (lastWord == wordB){
            recordLadderBetween(wordA, wordB, ladder);
            //print the ladder
            for(string word : ladder) {
                cout << word << ' ';
            }
            return 0;
        }
        int size = lastWord.size();
        //iterate through the word, changing letters one by one
        for (int i=0; i< size; i++){
            //iterate through the alphabet, creating 25 new words
            for (char c : alphabet){
                //copy the last word in the ladder
                string newWord = lastWord;
                //change a letter in the word
                //prevent duplicates
                if (newWord[i] != c){
                    newWord[i] = c;
                }
                //check if that word has been used
                if(! usedWords.containsKey(newWord)){
                    //check if that word is english
                    if(english.contains(newWord)){
                        //create a new word ladder
                        Vector<string> newLadder = ladder;
                        newLadder.add(newWord);
                        //add ladder to queue
                        ladderQueue.add(newLadder);
                        //add word to usedList
                        usedWords.add(newWord, true);
                    }
                }
            }
        }
    }

    // [TODO: Fill this in!]
    // Don't forget to call the recordLadderBetween and
    // recordNoLadderBetween functions in your solution!
    // We'll be using them to run automated tests on your
    // code.
    recordNoLadderBetween(wordA, wordB);
    cout << "no ladder found";
    return 0;
}
