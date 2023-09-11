#include <iostream>
#include "geesespotter_lib.h"

//  g++ -o main geesespotter.cpp geesespotter_lib.cpp -std=c++11
// ./main.exe  

// allocate a char array with xdim * ydim elements initialized to 0
char *createBoard(std::size_t xdim, std::size_t ydim){

   char *board {new char[xdim*ydim]};

    for (int k {0}; k < xdim*ydim; ++k){
        board[k] = 0;
    }
   
    return board;
}

// deallocate the given board
void cleanBoard(char *board){

    delete[] board;
    board = nullptr; 

}

// print the contents of the board (*, M, numbers)
void printBoard(char *board, std::size_t xdim, std::size_t ydim){
    

        for (int j {0}; j < xdim*ydim; ++j){
           
           // prints marked bit
           if (board[j] & markedBit()){
                std::cout << 'M';
           } 
           // prints * for a hidden bit
           else if (board[j] & hiddenBit()){
                std::cout << '*';
           } 
           // prints field value
           else {
                std::cout << (board[j] & valueMask());
           }
       
            if ( (j+1)%xdim == 0 ){
                std::cout << "\n";
            }
        }

}

// computes the number of geese adjacent to that spot and returns the amount
void computeNeighbors(char *board, std::size_t xdim, std::size_t ydim){


    for (int k{0}; k < xdim*ydim; ++k){ 

        if (board[k] != 0b1001){   
            if (k == 0){ // left edge top
                if (board [k+1] == 0b1001){
                    ++board [k];
                }
                if (board [k+xdim] == 0b1001){
                    ++board [k];
                }
                if (board [k+xdim+1] == 0b1001){
                    ++board [k];
                }

            } else if (k == (xdim*ydim - xdim)){//left edge bottom
                if (board [k+1] == 0b1001){
                    ++board [k];
                }
                if (board [k-xdim] == 0b1001){
                    ++board [k];
                }
                if (board [k-xdim+1] == 0b1001){
                    ++board [k];
                }

            } else if (k == (xdim - 1)){ // right edge top
                if (board [k-1] == 0b1001){
                    ++board [k];
                }
                if (board [k+xdim] == 0b1001){
                    ++board [k];
                }
                if (board [k+xdim-1] == 0b1001){
                    ++board [k];
                }

            } else if (k == (xdim*ydim - 1)){ // right edge bottom
                if (board [k-1] == 0b1001){
                    ++board [k];
                }
                if (board [k-xdim] == 0b1001){
                    ++board [k];
                }
                if (board [k-xdim-1] == 0b1001){
                    ++board [k];
                }

            } else if (k % xdim == 0){ // left edge

                if (board [k+1] == 0b1001){
                    ++board [k];
                }
                if (board [k+xdim] == 0b1001){
                    ++board [k];
                }
                if (board [k+xdim+1] == 0b1001){
                    ++board [k];
                }
                if (board [k-xdim] == 0b1001){
                    ++board [k];
                }
                if (board [k-xdim+1] == 0b1001){
                    ++board [k];
                }

            } else if ((k%xdim) == xdim-1){ // right edge

                if (board [k-1] == 0b1001){
                    ++board [k];
                }
                if (board [k+xdim] == 0b1001){
                    ++board [k];
                }
                if (board [k+xdim-1] == 0b1001){
                    ++board [k];
                }
                if (board [k-xdim] == 0b1001){
                    ++board [k];
                }
                if (board [k-xdim-1] == 0b1001){
                    ++board [k];
                }

            } else if (k < xdim){ // top 
                if (board [k+1] == 0b1001){
                    ++board [k];
                }
                if (board [k-1] == 0b1001){
                    ++board [k];
                }
                if (board [k+xdim] == 0b1001){
                    ++board [k];
                }
                if (board [k+xdim+1] == 0b1001){
                    ++board [k];
                }
                if (board [k+xdim-1] == 0b1001){
                    ++board [k];
                }

            } else if (k -1 > xdim*ydim - xdim){// bottom
                if (board [k+1] == 0b1001){
                    ++board [k];
                }
                if (board [k-1] == 0b1001){
                    ++board [k];
                }
                if (board [k-xdim] == 0b1001){
                    ++board [k];
                }
                if (board [k-xdim+1] == 0b1001){
                    ++board [k];
                }
                if (board [k-xdim-1] == 0b1001){
                    ++board [k];
                }

            } else { // middle piece
                if (board [k+1] == 0b1001){
                    ++board [k];
                }
                if (board [k-1] == 0b1001){
                    ++board [k];
                }
                if (board [k+xdim] == 0b1001){
                    ++board [k];
                }
                if (board [k+xdim+1] == 0b1001){
                    ++board [k];
                }
                if (board [k+xdim-1] == 0b1001){
                    ++board [k];
                }
                if (board [k-xdim] == 0b1001){
                    ++board [k];
                }
                if (board [k-xdim+1] == 0b1001){
                    ++board [k];
                }
                if (board [k-xdim-1] == 0b1001){
                    ++board [k];
                }
            }
        }
        
    }
}

// hide all the field values
void hideBoard(char *board, std::size_t xdim, std::size_t ydim){

    for (int k {0}; k < xdim*ydim; ++k){
        
        board [k] |= 0x20;
       
    }

}

// reveals hidden unmarked fields
// revealling --> set hidden bit to 0 
// if the field is marked --> the function returns 1
// if the field is already revealed --> return 2
// if the field contains a goose --> return 9
// if the field contains 0 --> reveal all the 8 fields adjacent 
// else, return 0
int reveal(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){

    int k {0};
    
    k = (xdim*yloc)+xloc;


        // if the field is marked
        if (board[k] & markedBit()){
            return 1;
        } 
        // if the field is already revealed
        else if (!(board [k] & hiddenBit())){
            return 2;
        } 
        // if the field is a goose
        else if ((board[k] & valueMask()) == 0b1001){
            board[k] &= ~hiddenBit();
            return 9;
        }
        // if the field is 0, reveal all other adjacent fields
        else if ((board[k] & valueMask()) == 0b0000){
            board[k] &= ~hiddenBit();


            if (k == 0){ // left edge top
                board [k+1] &= ~hiddenBit();
                board [k+xdim] &= ~hiddenBit();
                board [k+xdim+1] &= ~hiddenBit();

            } else if (k == (xdim*ydim - xdim)){//left edge bottom
                board [k+1] &= ~hiddenBit();
                board [k-xdim] &= ~hiddenBit();
                board [k-xdim+1] &= ~hiddenBit();

            } else if (k == (xdim - 1)){ // right edge top
                board [k-1] &= ~hiddenBit();
                board [k+xdim] &= ~hiddenBit();
                board [k+xdim-1] &= ~hiddenBit();

            } else if (k == (xdim*ydim - 1)){ // right edge bottom
                board [k-1] &= ~hiddenBit();
                board [k-xdim] &= ~hiddenBit();
                board [k-xdim-1] &= ~hiddenBit();

            } else if (k % xdim == 0){ // left edge
                board [k+1] &= ~hiddenBit();
                board [k+xdim] &= ~hiddenBit();
                board [k+xdim+1] &= ~hiddenBit();
                board [k-xdim] &= ~hiddenBit();
                board [k-xdim+1] &= ~hiddenBit();

            } else if ((k%xdim) == xdim-1){ // right edge
                board [k-1] &= ~hiddenBit();
                board [k+xdim] &= ~hiddenBit();
                board [k+xdim-1] &= ~hiddenBit();
                board [k-xdim] &= ~hiddenBit();
                board [k-xdim-1] &= ~hiddenBit();

            } else if (k < xdim){ // top 
                board [k+1] &= ~hiddenBit();
                board [k-1] &= ~hiddenBit();
                board [k+xdim] &= ~hiddenBit();
                board [k+xdim+1] &= ~hiddenBit();
                board [k+xdim-1] &= ~hiddenBit();

            } else if (k -1 > xdim*ydim - xdim){// bottom
                board [k+1] &= ~hiddenBit();
                board [k-1] &= ~hiddenBit();
                board [k-xdim]&= ~hiddenBit();
                board [k-xdim+1] &= ~hiddenBit();
                board [k-xdim-1] &= ~hiddenBit();

            } else { // middle piece
                board [k+1] &= ~hiddenBit();
                board [k-1] &= ~hiddenBit();
                board [k+xdim] &= ~hiddenBit();
                board [k+xdim+1] &= ~hiddenBit();
                board [k+xdim-1] &= ~hiddenBit();
                board [k-xdim] &= ~hiddenBit();
                board [k-xdim+1] &= ~hiddenBit();
                board [k-xdim-1] &= ~hiddenBit();
            }
        } 
        // if the field has geese around it and was not revealed or marked
        else {
            board[k] &= ~hiddenBit();
        }

return 0;
}

// if the field is already revealed --> output that it cannot be marked and return 2
// otherwise, toggle the mark bit and return 0
    // if marked bit is on, toggle it off and vice versa
int mark(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){

        int k{0};

        // computing the k value on the array

        k = ((yloc) * xdim )+ xloc;

        // if it is already revealled
    if (board [k] & hiddenBit() != hiddenBit()){   // how to use this one
       
       std::cout << "Field Already Revealed";
        return 2;

    } else {

            board [k] ^= markedBit();
            return 0;
       
        
        
    }


}

// determines if all non-goose fields are revealed and game is won
bool isGameWon(char *board, std::size_t xdim, std::size_t ydim){

    int geese {0};

    for (int k{0}; k < xdim*ydim; ++k){

      // go through board, if board is not revealed, and not a geese then not won (return false) 
        if (board[k] & hiddenBit()){ 
            if ((board[k] & valueMask()) != 0b1001){
                return false;
            }
        
        } else if (board[k] & valueMask() == 0b1001){
            ++geese;

        }

    } 

    // game is automatically won if number of geese is the same as number of elements
    if (geese = xdim*ydim){
        return true;
    }

    return true;
}