#include "geesespotter_lib.h"

char *createBoard(std::size_t xdim, std::size_t ydim)
{
    int size = xdim * ydim;
    char *array{new char[size]{}};
    int count = 0;
    ;
    for (int i = 0; i < size; i++)
    {
        array[i] = 0x0;
        if (count == 5)
        {
            count = 0;
        }
        count++;
    }

    return array;
}
void computeNeighbors(char *board, std::size_t xdim, std::size_t ydim)
{
    // go through board until we find 9
    int new_position = 0x0;
    for (int position = 0; position < xdim * ydim; position++)
    {
        if (board[position] == 9)
        {
            for (int y = -1; y <= 1; y++)
            { // y shifts and y dimensions
                for (int x = -1; x <= 1; x++)
                { // x shifts and x dimensions
                    // at index position, add xdim* outter for loop variable + inner for loop variable to positon
                    // at each new position, we are going to add the number 1
                    new_position = (xdim * y + x) + position;
                    int xloc = (position % xdim);
                    int yloc = (position / xdim);
                    // if its on the side borders; make sure xloc + xshift >= 0
                    // and that xloc + xshift < xdim
                    if (((xloc + x) >= 0) && ((xloc + x) < xdim) &&
                        ((yloc + y) >= 0) && ((yloc + y) < ydim) &&
                        (board[new_position] != 9))
                    {
                        board[new_position] += 0x1;
                    }
                    // if its at the top; make sure that yloc + yshift >= 0
                    //  and that yloc + yshift < ydim

                    // if at our new positions we find a 9, do not add 1
                    // IF ALL THESE CONDITIONS ARE TRUE
                    // ADD 1 TO THE ARRAY AT THE INDEX
                }
            }
            // i is our index of our board
            /*
            0 1 2   0 0 0       -xdim-1 -xdim -xdim+1       -4 -3 -2
            3 4 5   0 9 0   -->     -1          +1      --> -1  0 +1
            6 7 8   0 0 0       +xdim-1 +xdim +xdim+1       +2 +3 +4
            //hard
            */
        }
    }
}
void hideBoard(char *board, std::size_t xdim, std::size_t ydim)
{
    int size = xdim * ydim;
    for (std::size_t i = 0; i < size; i++)
    {
        board[i] |= hiddenBit();
    }
}
void cleanBoard(char *board)
{
    delete[] board;
    board = nullptr;
}
void printBoard(char *board, std::size_t xdim, std::size_t ydim)
{
    int size = xdim * ydim;
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        int field_value{board[i]};
        // skip to next line
        if (count == xdim)
        {
            std::cout << std::endl;
            count = 0;
        }
        // if (0010 xxxx) and (0010 0000) will give 0010 0000 which means it is hidden
        if (((board[i] & hiddenBit()) == hiddenBit()) && ((board[i] & markedBit()) != markedBit()))
        {
            std::cout << '*';
        }
        // This checks if board value has markedBit in it
        else if (((board[i] & markedBit()) == markedBit()) && ((board[i] & hiddenBit()) == hiddenBit()))
        {
            std::cout << 'M';
        }
        else
        {
            std::cout << field_value;
        }
        count++;
    }
}

int reveal(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc)
{
    int position = (yloc * xdim) + xloc;
    // return 1 if field is marked ( Your values will have flags on them now)
    if ((board[position] & markedBit()) == markedBit())
    {
        return 1;
    }
    // return 2 if the field is revealed (AKA, the hidden bit is = 0)
    else if ((board[position] & hiddenBit()) != hiddenBit())
    {
        return 2;
    }
    // return 9 and reveal the goose if the field is a goose (AKA, look at the value of your board, and if the value == 9, its a goose)
    else if ((board[position] & 0x9) == 0x9)
    {
        board[position] &= valueMask();
        return 9;
    }
    // if all of the above is false, then remove the hiddenBit
    else{
        if ((board[position] & valueMask()) == 0x0){
            for (int y = -1; y <= 1; y++)
            { // y shifts and y dimensions
                for (int x = -1; x <= 1; x++)
                { // x shifts and x dimensions
                    // at index position, add xdim* outter for loop variable + inner for loop variable to positon
                    // at each new position, we are going to add the number 1
                    int new_position = (xdim * y + x) + position;
                    int xloc = (position % xdim);
                    int yloc = (position / xdim);
                    // if its on the side borders; make sure xloc + xshift >= 0
                    // and that xloc + xshift < xdim
                    if (((xloc + x) >= 0) && ((xloc + x) < xdim) &&
                        ((yloc + y) >= 0) && ((yloc + y) < ydim) &&
                        ((board[new_position] & valueMask()) != 0x9))
                    {
                        board[new_position] = board[new_position] & ~hiddenBit();
                    }
                }
            }
        }
        else{
            board[position] = board[position] & ~hiddenBit();
        }
    }
    return 0;
}
int mark(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc)
{
    int end_point = (yloc * xdim) + xloc;

    if ((board[end_point] & hiddenBit()) == 0x0)
    {
        return 2;
    }
    // if board value (0010 xxxx) and (0001 0000) results in all 0 that means it is not marked and hidden
    else if ((board[end_point] & markedBit()) == 0x0)
    {
        board[end_point] = board[end_point] | markedBit();
        return 0;
    }
    // if board and markedBit results in markedBit that means the boardvalue is marked
    else if ((board[end_point] & markedBit()) == markedBit())
    {
        board[end_point] = board[end_point] & ~markedBit();
        return 0;
    }
    else
    {
        return 0;
    }
}
bool isGameWon(char *board, std::size_t xdim, std::size_t ydim)
{
    // Look through board;
    //  Determine if all the fields that are NOT Geese are revealed
    //  if all the revealed fields are not geeses then you win
    //  if any field is hidden and is not a goose, you have not won
    /*
     ***     111
     *** ->  1*1 Game is won
     ***     111
     */
    for (int i = 0; i < xdim * ydim; i++)
    {
        // if the board is hidden and the board value is not 9, then return game not won
        if (((board[i] & hiddenBit()) == hiddenBit()) && ((board[i] & 0x9) != 0x9))
        {
            return false;
        }
    }
    return true;
}
