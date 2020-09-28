#include "block.h"
#include <cmath>
#include <iostream>

int Block::width() const
{
    if(data.size() == 0){
        return 0;
    }
  
    return data[0].size();
}

int Block::height() const
{
    return data.size();
}

void Block::render(PNG &im, int column, int row) const
{
    unsigned x_bound = (im.width() < column + width()) ? im.width() : column+width();
    unsigned y_bound = (im.height() < row + height()) ? im.height() : row+height();

    for (unsigned int y = row; (y < y_bound); y++)
    {
        for (unsigned int x = column; (x < x_bound); x++)
        {
            *(im.getPixel(x,y)) = data[y-row][x-column];
        }
    }
}

void Block::build(PNG &im, int column, int row, int width, int height)
{
    unsigned int x_bound = column + width;
    unsigned int y_bound = row + height;

    data.resize(height);

    for (unsigned int y=row; y < y_bound; y++)
    {
        data[y-row].resize(width);
        for (unsigned int x = column; x < x_bound; x++) 
        {
            data[y-row][x-column] = *(im.getPixel(x,y));
        }
    }
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp; 
}

void Block::flip()
{
    int rows = height();
    int columns = width();
    for (int column = 0; column < columns; column++)
    {
        for (int row = 0; row < rows/2; row++)
        {
            swap(data[row][column], data[rows-1-row][column]);
        }
    }
}


