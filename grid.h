/*-------------------------------------------
Program 5 Part 1: Labryinth Game

The programming tasks involve object oriented programming to create a 4x4 grid maze game
where the player must collect 3 items placed in the maze to win.
The maze games are specified to my ID and there are two games;
A regular 4x4 maze and a twisty maze with 12 nodes but twisty directions 

Course: CS 211, Spring 2025, UIC
Author: Joe Wu
------------------------------------------- */
#pragma once

#include <iostream>
#include <exception>
#include <stdexcept>
#include <algorithm>

using namespace std;

template<typename T>
class Grid {
private:
    struct CELL {
        CELL* Next;
        T Val;
        size_t NumCols;  // total # of columns (0..NumCols-1)
        CELL(CELL* _Next = nullptr, T _Val = T(), size_t _NumCols = 0) {
            Next = _Next;
            Val = _Val;
            NumCols = _NumCols;
        }
    };
    
    size_t NumRows;  // total # of rows (0..NumRows-1)
    CELL** Rows;     // C array of linked lists
public:

    // default constructor: construct a 4x4 Grid with elements all defaulted to T value.
    Grid() {
        // initialize 4 rows
        Rows = new CELL*[4];
        NumRows = 4;
        
        // allocate the first cell of the linked list with default value:
        for (size_t r = 0; r < NumRows; ++r) {
            Rows[r] = new CELL(nullptr, T(), 4);
            CELL* cur = Rows[r];
            
            // create the linked list for this row.
            for(size_t c = 1; c < Rows[r]->NumCols; ++c) {
                cur->Next = new CELL(nullptr, T());
                cur = cur->Next;
            }
        }
        
    }
    
    // parameterized constructor: construct a Grid with R rows, C columns, and all elements are defaulted to T value.
    Grid(size_t R, size_t C) {
        
        NumRows = R;
        Rows = new CELL*[R];
        
        // allocate the first cell of the linked list with default value:
        for (size_t r = 0; r < NumRows; ++r) {
            Rows[r] = new CELL(nullptr, T(), C);
            CELL* cur = Rows[r];
            
            // create the linked list for this row.
            for(size_t c = 1; c < Rows[r]->NumCols; ++c) {
                cur->Next = new CELL(nullptr, T(), C);
                cur = cur->Next;
            }
        }
        
    }
    
    // destructor: free the memory associated to the vector.
    virtual ~Grid() {
        
      for (size_t r = 0; r < NumRows; ++r) {
            CELL* cur = Rows[r];
            
            while (cur != nullptr) {
                CELL* temp = cur;
                cur = cur->Next;
                delete temp;
            }
        }
        delete[] Rows;
    }
    
    

    // copy constructor: construct a Grid that contains a copy of an existing Grid.
    // Ex: when passing Grid as a parameter by value; void somefunction(Grid<int> G2)  <--- G2 is a copy:
    Grid(const Grid<T>& other) {
        
        NumRows = other.NumRows;
        Rows = new CELL*[NumRows];
        
        for (size_t r = 0; r < NumRows; ++r) {
            CELL* cur = other.Rows[r];
            Rows[r] = new CELL(nullptr, cur->Val, cur->NumCols);
            CELL* cpy = Rows[r];
            cur = cur->Next;
            
            while (cur != nullptr) {
                cpy->Next = new CELL(nullptr, cur->Val, cur->NumCols);
                cpy = cpy->Next;
                cur = cur->Next;
            }
        }
    }
    
    //
    // copy operator= : copy one grid to another when using "=" operator, i.e. this = other;
    //
    Grid& operator=(const Grid& other) {
        for (size_t r = 0; r < NumRows; ++r) {
            CELL* cur = Rows[r];
            while (cur != nullptr) {
                CELL* temp = cur;
                cur = cur->Next;
                delete temp;
            }
        }
        delete[] Rows;

        NumRows = other.NumRows;
        Rows = new CELL*[NumRows];
        
        for (size_t r = 0; r < NumRows; ++r) {
            CELL* cur = other.Rows[r];
            Rows[r] = new CELL(nullptr, cur->Val, cur->NumCols);
            CELL* cpy = Rows[r];
            cur = cur->Next;
            
            while (cur != nullptr) {
                cpy->Next = new CELL(nullptr, cur->Val, cur->NumCols);
                cpy = cpy->Next;
                cur = cur->Next;
            }
        }
        return *this;

    }
    
    //Returns the # of rows in the Grid
    size_t numrows() const {
        return NumRows;
    }
    
    // Returns the # of columns in row r. 
    size_t numcols(size_t r) const {
       return Rows[r]->NumCols; 
    }
    
    // Returns the total # of elements in the grid.
    size_t size() const {
        return NumRows * Rows[0]->NumCols;
    }
    
    
    // Returns a reference to the element at (r, c); allows for access to the element
    // ex: grid(r, c) = ...
    T& operator()(size_t r, size_t c) {
        if (r >= NumRows) throw out_of_range("Invalid row index");
        size_t col = Rows[r]->NumCols;
        if (c >= col) throw out_of_range("Invalid col index");
        
        CELL* cur = Rows[r];
        for (size_t i = 0; i < c; i++) {
            cur = cur->Next;
        }
        
        return cur->Val;  
    }
    
    // Outputs the contents of the grid
    void _output() {
        
        for (size_t i = 0; i < NumRows; i++) {
            CELL* cur = Rows[i];
            while (cur != nullptr) {
                cout << cur->Val << " ";
                cur = cur->Next;
            }
            cout << endl;
        }
        
    }
    
};
