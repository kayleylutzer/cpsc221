
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
    
	PNG returnImage = PNG(target.width() * TILESIZE, target.height() * TILESIZE);
    
	for(int i = 0; (unsigned) i < target.width(); i++ ) {
		
        for(int j = 0; (unsigned) j < target.height(); j++) {
			
            RGBAPixel key = ss.findNearestNeighbor(*target.getPixel(i, j));
            PNG curr; curr.readFromFile(photos[key]); 
			
			for(int x = 0; (unsigned) x < curr.width(); x++){
				
				for(int y = 0; (unsigned) y < curr.width(); y++){
			
				RGBAPixel* pixelInFinal = returnImage.getPixel(i * TILESIZE + x, j * TILESIZE + y);
				RGBAPixel* pixelInTarget = curr.getPixel(x, y);
				
				pixelInFinal->r = pixelInTarget->r;
				pixelInFinal->g = pixelInTarget->g;
				pixelInFinal->b = pixelInTarget->b;
				pixelInFinal->a = pixelInTarget->a;

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

	int r, g, b, x, y;

    map < RGBAPixel, string> thumbs;
    for (const auto & entry : fs::directory_iterator(path)) {
        PNG curr; curr.readFromFile(entry.path());
		
		r = 0;
		g = 0;
		b = 0; //resets all pixel values to re-use/add into the average RGBAPixel
		
		for(x = 0; (unsigned) x < curr.width(); x++){
			for(y = 0; (unsigned) y < curr.height(); y++){
					RGBAPixel *p = curr.getPixel(x, y);

					r += p->r;
					g += p->g;
					b += p->b;
				
			}
		}
		
		r = r / (x*y);
		g = g / (x*y);
		b = b / (x*y); //computes the average r, g, and b for the thumbnail
		
		RGBAPixel averageOfThumb(r, g, b);
		thumbs[averageOfThumb] = entry.path();

    }
    return thumbs;
}


