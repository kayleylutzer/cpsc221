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
    if (!(column>=0 && (unsigned)column<im.width()))
        return;

    unsigned int col_bound = (column + width() > im.width())? im.width() : (column + width());

    for (unsigned int col = column; col<col_bound; col++){
        for (unsigned int row = 0; row<im.height(); row++){
        *(im.getPixel(col, row)) = data[row][col-(unsigned)column];
        }
    }
}

void Block::build(PNG &im, int column, int row, int width, int height)
{
    unsigned int col_bound = column + width;
    unsigned int row_bound = im.height();

    data.resize(im.height());
    for (unsigned int row=0; row<row_bound; row++){
        data[row].resize(width);
        for (unsigned int col=column; col<col_bound; col++){
            data[row][col-(unsigned)column] = *(im.getPixel(col, row));
        }
    }
    //cout << "block width " << data[0].size() << endl;
    //cout << "block height " << data.size() << endl;
}

void Block::flip()
{

}
