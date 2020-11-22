
// File:        tileUtil.cpp
// Author:      Cinda
// Date:        2020-10-31
// Description: file handling functions that prepare data for the tiling algorithm


#include "tileUtil.h"

/**
 * Function tile:
 * @param PNG & target: an image to use as base for the mosaic. it's pixels will be
 *                      be replaced by thumbnail images whose average color is close
 *                      to the pixel.
 * @param rgbtree & ss: a kd-tree of RGBAPixels, used as a query structure for
 *                      nearest neighbor search. 
 * @param map<RGBAPixel, string> & photos: a map that takes a color key and returns the
 *                      filename of an image whose average color is that key.
 *
 * returns: a PNG whose dimensions are TILESIZE times that of the target. Each
 * pixel in the target is used as a query to ss.findNearestNeighbor, and the response
 * is used as a key in photos. 
 */

PNG tiler::tile(PNG & target, const rgbtree & ss, map<RGBAPixel,string> & photos){
    PNG returnImage = PNG(target.width() * TILESIZE, target.height()*TILESIZE);
    for(int i = 0; i < target.height(); i++ ) 
    { 
        for(int j = 0; j < target.width(); j++) 
        { 
            RGBAPixel key = ss.nearestNeighbour(&target.getPixel(i, j));
            PNG curr; curr.readFromFile(photos.get(key));
            int startHeight = i*TILESIZE; 
            int startWidth = j*TILESIZE;
            for(startHeight < startHeight + TILESIZE; startHeight++) 
            { 
                for(startWidth < startWidth + TILESIZE; startWidth++)
                { 
                    RGBAPixel* pixelInBiggerImage = returnImage.getPixel(startWidth, startHeight);
                    RGBAPixel* pixelInSmallerImage = curr.getPixel(startWidth%TILESIZE, startHeight%TILESIZE);
                    pixelInBiggerImage->r = pixelInSmallerImage->r;
                    pixelInBiggerImage->g = pixelInSmallerImage->g;
                    pixelInBiggerImage->b = pixelInSmallerImage->b;
                    pixelInBiggerImage->a = pixelInSmallerImage->a;
                }
            }
        }
    }
    return returnImage;
}

/* buildMap: function for building the map of <key, value> pairs, where the key is an
 * RGBAPixel representing the average color over an image, and the value is 
 * a string representing the path/filename.png of the TILESIZExTILESIZE image
 * whose average color is the key.
 * 
 * We've provided a bit of the C++ code that allows you to iterate over the files
 * in a directory. It is up to you to figure out what it means, and how to use it.
 * 
 * @param path is the subdirectory in which the tiles can be found. In our examples
 * this is imlib.
 *
*/
map<RGBAPixel, string> tiler::buildMap(string path) {

    map < RGBAPixel, string> thumbs;
    for (const auto & entry : fs::directory_iterator(path)) {
        PNG curr; curr.readFromFile(entry.path());
        int r,g,b = 0,0,0;
        int dims = curr.height() * curr.width();
        for(int y = 0; y < curr.height(); y++)
        {
            for(int x = 0; x < curr.width(); x++)
            { 
                RGBAPixel* pixel = curr.getPixel(x,y);
                r += pixel->r;
                g += pixel->g;
                b += pixel->b;
            }
        }
        RGBAPixel avgPixel = RGBAPixel(r/dims, g/dims, b/dims);
        thumbs.insert({ avgPixel, entry });
    }
    return thumbs;
}


