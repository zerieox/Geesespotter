#ifndef GEESESPOTTER_LIB_H
#define GEESESPOTTER_LIB_H

#include <iostream>

int main();
bool game();
void startGame(char * & board, std::size_t & xdim, std::size_t & ydim, unsigned int & numgeese);
char getAction();
void actionShow(char * & board, std::size_t & xdim, std::size_t & ydim, unsigned int & numgeese);
void actionMark(char * board, std::size_t xdim, std::size_t ydim);
std::size_t readSizeT();
std::size_t xdim_max();
std::size_t ydim_max();
char markedBit();
char hiddenBit();
char valueMask();
void spreadGeese(char * board, std::size_t xdim, std::size_t ydim, unsigned int numgeese);

#endif
