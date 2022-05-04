// Header file for functions used in paging system simulation code
// By Alexia Perez, 127008512

#ifndef MAIN_CPP_PAGINGSYSTEM_H
#define MAIN_CPP_PAGINGSYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

/* General Functions */
void newInputFile(); // generates a new text file with 100 random integers from 0-15
void getRefs(int references[], char *filename); // saves every line in the input file as a new element of an array
void makeTable(int tableName[], int size); // creates empty paging table to be filled using chosen algorithm
void printTime(); // prints current timestamp
void printTable (int table[], int size); // prints current table contents
int getAlgChoice(); // to determine which algorithm to be used
int getNumFrames(); // gets number of frames from user input (either 4 or 8)
/* FIFO Functions */
int FIFO(int frames, int references[]); // runs the FIFO algorithm for each entry in input text file
/* LRU Functions */
int findLRU(const int timeTable[], int size); // finds the index to place new page into for LRU
int LRU(int frames, int references[]); // runs the LRU algorithm for each entry in input text file
/* 2nd Chance Functions */
int findPage(int page, const int secondChanceTable[], int refBits[], int frames); // find a page in the current page table
int replacePage (int page, int secondChanceTable[], int refBits[], int frames, int location); // replaces page in page table with current referenced one
int secondChance(int frames, int references[]); // runs the 2nd chance algorithm for each entry in input text file
#endif //MAIN_CPP_PAGINGSYSTEM_H
