// This is the .cpp file you will edit and turn in.
//
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

// Please feel free to add any other #includes you need!
#include "recursionproblems.h"
#include <cmath>
#include <iostream>
#include "hashmap.h"
#include "map.h"
#include "random.h"
using namespace std;


double weightOnKnees(int row, int col, const Vector<Vector<double> >& weights) {
    // TODO: write this function
    
    //return cases
    if(row >= weights.size() || col >= weights.size()){
        return 0.0;
    }
    //base case -> reached top of pyramid
    else if(row == 0 && col == 0){
        return weights[0][0];
    }
    else if (col == 0) {
        //if all the way to the left, return the one above and to the right
        return weights[row][col] + 0.5*weightOnKnees(row-1, col, weights);
    }
    
    else if (col == row){
        //if all the way to the right, return the one above and to the left
        return weights[row][col] + 0.5*weightOnKnees(row-1, col-1, weights);
    }
    else {
        return weights[row][col] + 0.5*weightOnKnees(row-1, col, weights) + 0.5*weightOnKnees(row-1, col-1, weights);
    }
    return 0.0;
}


void drawSierpinskiTriangle(GWindow& gw, double x, double y, int size, int order) {
   
    if (order < 0 || size < 0){
       throw "Invald parameters";
        return;
    }
    //base case
    if (order == 1){
        gw.drawLine(x, y, x+size, y);
        gw.drawLine(x+size, y, x + 0.5 * size, y + 0.866 * size);
        gw.drawLine(x + 0.5 * size, y + 0.866 * size, x, y);
        return;
    }
    else if (order > 1){
        drawSierpinskiTriangle(gw, x, y, 0.5*size, order-1);
        drawSierpinskiTriangle(gw, x + 0.5*size, y, 0.5*size, order-1);
        drawSierpinskiTriangle(gw, x +0.25*size, y + 0.433*size, 0.5*size, order-1 );
        return;
    }
    
}


