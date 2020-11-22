/**
 * @file rgbtree.cpp
 * Implementation of rgbtree class.
 */

#include <utility>
#include <algorithm>
#include "rgbtree.h"

using namespace std;

rgbtree::rgbtree(const map<RGBAPixel,string>& photos)
{
  for (const auto& [key, ignored] : photos) {
    tree.push_back(key);
  }
  buildTree(0, (int) tree.size()-1, 0);
}

void rgbtree::buildTree(int start, int end, int dimension) 
{ 
  if(start < end) { 
    int median = (start + end)/2;
    quickSelect(start, end, median, dimension);
    buildTree(start, median-1, (dimension+1)%3);
    buildTree(median+1, end, (dimension+1)%3);
  } 
}

RGBAPixel rgbtree::findNearestNeighbor(const RGBAPixel & query) const
{
  if (tree.size() == 0) {
      return NULL; 
  }
  return recursiveFindNearest(0, tree.size() - 1, query, INT_MAX);
}

RGBAPixel recursiveFindNearest(int start, int end, const RGBAPixel & query, int minDist)
{
  if (start < end){ 
    int mid = (start + end)/2;
      int midDist = distance(query, tree[mid]); 
      if (midDist < minDist) { 
        RGBAPixel right = recursiveFindNearest(mid + 1, end, query, midDist);
        RGBAPixel left = recursiveFindNearest(start, mid-1 , query, midDist);

        if (right != NULL) && (left != NULL) {
          if (midDist < distance(right, query)) 
          { 
            return (midDist < distance(left, query)) ? tree[mid] : left; 
          } 
          return right; 
        } else if (right != NULL ) { 
          return (midDist < distance(right, query)) ? tree[mid] : right;
        } else if (left != NULL ) { 
          return (midDist < distance(left, query)) ? tree[mid] : left; 
        }
      }
      return tree[mid];
  }
  return NULL;
}


int rgbtree::distance(RGBAPixel a, RGBAPixel b){
  return (a.r-b.r)**2 + (a.g-b.g)**2 + (a.b-b.b)**2; 
}

bool rgbtree::smallerByDim(const RGBAPixel & first,
                                const RGBAPixel & second, int curDim) const
{
  switch (curDim) { 
    case 0: 
      return first.r == second.r ? first < second : first.r < second.r;
    case 1:
      return first.g == second.g ? first < second : first.g < second.g;
    case 2:
      return first.b == second.b ? first < second : first.b < second.b;
  }
}

/**
 * This function splits the trees[start..end] subarray at position start k
 */
void rgbtree::quickSelect(int start, int end, int k, int d)
{
  int pivot = partition(start, end, d);
  if(pivot == k){
    return pivot;
  } else if (pivot < k ) { 
    return quickSelect(pivot + 1, end, k, d);
  } else { 
    return quickSelect(start, pivot-1, k, d);
  }
}


/**
 * This method does a partition around pivot and will be used 
 * in quick select. It uses tree[lo] as the default pivot.
 * It returns the index of the pivot in the updated vector.
 * You will likely need to modify and complete this code.
 */
int rgbtree::partition(int lo, int hi, int d) 
{
    int p = lo;
    for( int i=lo+1; i <= hi; i++ ){
      if(smallerByDim(tree[i], tree[lo], d)){p++; swap(tree[p], tree[i]); }
    swap(tree[lo], tree[p]);
    return p;
}


/**
 * Helper function to help determine if the nearest neighbor could 
 * be on the other side of the KD tree.
 */
int rgbtree::distToSplit(const RGBAPixel& query, const RGBAPixel& curr, int dimension) const
{
  

}

