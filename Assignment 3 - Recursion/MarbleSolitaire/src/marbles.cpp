/* TODO: This is the file you edit! (and the only file you edit)
 */

#include <iostream>
#include "grid.h"
#include "set.h"
#include "vector.h"
#include "simpio.h"
#include "console.h"
#include "random.h"
#include "gevents.h"
#include "filelib.h"
#include "shuffle.h"

#include "marbletypes.h"
#include "marblegraphics.h"
#include "compression.h"

using namespace std;

/* Provided helper functions (do not edit these, but you will call them) */
void makeMove(Move move, Grid<MarbleType>& board);
void undoMove(Move move, Grid<MarbleType>& board);
Vector<Move> findPossibleMoves(const Grid<MarbleType>& board);


/* Board: starting board that you should find a solution for.
 * ExploredBoards: a set of encoded boards which you have already checked. You
 *                 should use this to avoid doing duplicate work in your recursion.
 * MoveHistory: the current set of moves from the starting board that the
 *              recursion is considering--THIS IS INITIALLY EMPTY and you populate
 *              it essentially as a "return value" for the function.
 *
 * Return: You should return true or false of whether you were able to solve the
 *          starting board. If you return true, MoveHistory should contain the
 *          sequence of moves that arrives at the solution.
 */

//helper function to check if the board is empty

int numOccupied(Grid<MarbleType>& board){
    int numberFilled = 0;
    for(int i = 0; i< board.width(); i++){
        for(int j = 0; j< board.width(); j++){
            MarbleType marble = board.get(i,j);
            if (marble == MARBLE_OCCUPIED){
                numberFilled += 1;
            }
        }
    }
    return numberFilled;
}
bool solvePuzzle(Grid<MarbleType>& board, Set<uint32_t>& exploredBoards,
                 Vector<Move>& moveHistory){
    
    cout << "Number occupied: " << numOccupied(board) <<endl;
    //memoization
    uint32_t encoding = compressMarbleBoard(board);    
    if (exploredBoards.contains(encoding)){
        cout << "already checked" << endl;
        return false;
    }
    
    //if there is one marble left, you win
    if (numOccupied(board) == 1){
        cout << "returning win" <<endl;
        return true;
    } 
    
    //if we can't move, rule out this state (recursive backtracking)    
    Vector<Move> possibleMoves = findPossibleMoves(board);
    if (possibleMoves.isEmpty()) {
        cout << "no possible moves" << endl;
        return false;
    }
    exploredBoards.add(encoding);
    
    for (Move thisMove : possibleMoves){
        makeMove(thisMove, board);
        moveHistory.add(thisMove);
        cout << "checking this move: "<< thisMove <<endl;
        bool didWin = solvePuzzle(board, exploredBoards, moveHistory);
        if (didWin) {
            cout << "returning true" <<endl;
            moveHistory.add(thisMove);
            return true;
        }
        else{
            cout <<  "undoing move" <<endl;
            undoMove(thisMove, board);
            moveHistory.remove(moveHistory.size() - 1);
        }
    }
    return false;
}



/**********************************************************************************
 * YOU DO NOT NEED TO EDIT CODE BELOW THIS POINT                                  *
 * - however, you should use the functions below in your solvePuzzle function     *                                                        *                                                                   *
 * ********************************************************************************/

/* Performs the specified move on the board.
 * Precondition: this move must be valid.
 */
void makeMove(Move move, Grid<MarbleType>& board){
    int jumpedRow = move.startRow + (move.endRow - move.startRow) / 2;
    int jumpedCol = move.startCol + (move.endCol - move.startCol) / 2;
    board[move.startRow][move.startCol] = MARBLE_EMPTY;
    board[move.endRow][move.endCol] = MARBLE_OCCUPIED;
    board[jumpedRow][jumpedCol] = MARBLE_EMPTY;
}

/* Undoes the specified move on the board.
 * Note: it's important to realize that this method is
 * necessary because you have to replace the jumped marble
 * so you can't just call makeMove() with the start and end
 * locations swapped.
 */
void undoMove(Move move, Grid<MarbleType>& board){
    int jumpedRow = move.startRow + (move.endRow - move.startRow) / 2;
    int jumpedCol = move.startCol + (move.endCol-move.startCol) / 2;
    board[move.startRow][move.startCol] = MARBLE_OCCUPIED;
    board[move.endRow][move.endCol] = MARBLE_EMPTY;
    board[jumpedRow][jumpedCol] = MARBLE_OCCUPIED;
}

/* This examines the provided board and returns a Vector of
 * next moves that are possible for this board.
 */
Vector<Move> findPossibleMoves(const Grid<MarbleType>& board){
    Vector<Move> moves;
    for (int row=0; row<board.numRows(); row++){
        for (int col=0; col<board.numCols(); col++){
            if (board[row][col] == MARBLE_EMPTY) {
                if (row-2 >= 0 && board[row-2][col] == MARBLE_OCCUPIED
                        && board[row-1][col] == MARBLE_OCCUPIED){
                    moves.add(Move(row-2, col, row, col));
                }
                if (row+2 < board.numRows() && board[row+2][col] == MARBLE_OCCUPIED
                        && board[row+1][col] == MARBLE_OCCUPIED){
                    moves.add(Move(row+2, col, row, col));
                }
                if (col-2 >= 0 && board[row][col-2] == MARBLE_OCCUPIED
                        && board[row][col-1] == MARBLE_OCCUPIED){
                    moves.add(Move(row, col-2, row, col));
                }
                if (col+2 < board.numCols() && board[row][col+2] == MARBLE_OCCUPIED
                        && board[row][col+1] == MARBLE_OCCUPIED){
                    moves.add(Move(row, col+2, row, col));
                }
            }
        }
    }
    if (RANDOMIZED_POSSIBLE_MOVES) {
        shuffle(moves);
    }
    return moves;
}
