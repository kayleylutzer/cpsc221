/**
 * @file rgbtree.cpp
 * Implementation of rgbtree class.
 */

#include <utility>
#include <algorithm>
#include "rgbtree.h"

using namespace std;

const int k = 3; //dimension 

rgbtree::rgbtree(const map<RGBAPixel,string>& photos)
{

  for (const auto& [key, ignored] : photos) {
    tree.push_back(key);
  }
  buildTree(0, (int) tree.size() - 1, 0);

}

void rgbtree::buildTree(int start, int end, int dimension) 
{ 
  if(start < end) { 
    int median = (start + end)/2;
    quickSelect(start, end, median, dimension);
    buildTree(start, median - 1, (dimension+1) % k);
    buildTree(median + 1, end, (dimension+1) % k);
  } 
}

RGBAPixel rgbtree::findNearestNeighbor(const RGBAPixel & query) const
{

  if (tree.size() == 0) {
      return NULL; 
  }
  
  int index = tree.size()/2;
  return findNearestNeighborRec(query, 0, tree.size() - 1, 0);

}

RGBAPixel rgbtree::findNearestNeighborRec(const RGBAPixel& query, int start, int end, int dimension) const
{
	
	RGBAPixel inBest, outBest;
	
	if(start >= end)
		return tree[start];		//base case
	
	int median = (start + end)/2;
	RGBAPixel root = tree[median];
	int bestDist = distance(root, query);
	
	if(smallerByDim(query, root, dimension)) //if the query is smaller than the root in the given dimension, will return true
		inBest = findNearestNeighborRec(query, start, median - 1, (dimension + 1) % k);
	else
		inBest = findNearestNeighborRec(query, median + 1, end, (dimension + 1) % k);
		
	int tempDist = distance(inBest, query);
	if(bestDist > tempDist) //lower is better
		bestDist = tempDist;
		
	if(distToSplit(query, root, dimension) < bestDist){ //only enter the other tree if there's reason to
	
		if(smallerByDim(query, root, dimension))
			outBest = findNearestNeighborRec(query, median + 1, end, (dimension + 1) % k);
		else
			outBest = findNearestNeighborRec(query, start, median - 1, (dimension + 1) % k);
		
		int tempDist = distance(outBest, query);
		if(bestDist > tempDist) //lower is better
			bestDist = tempDist;
	
	}
	
	if(bestDist == distance(query, root))
		return root;
	else if(bestDist == distance(query, inBest))
		return inBest;
	else if(bestDist == distance(query, outBest))
		return outBest;
	else
		return query;
	
}

int rgbtree::distance (RGBAPixel a, RGBAPixel b) const {
		
  return ((int)a.r-(int)b.r)*((int)a.r-(int)b.r) + ((int)a.g-(int)b.g)*((int)a.g-(int)b.g) + ((int)a.b-(int)b.b)*((int)a.b-(int)b.b); 
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
	
  if (start == end)
	return void();

  int pivot = partition(start, end, d);
  
  if(pivot == k){
    return void();
  } else if (pivot < k ) { 
    quickSelect(pivot + 1, end, k, d);
  } else { 
    quickSelect(start, pivot - 1, k, d);
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
		
      if(smallerByDim(tree[i], tree[lo], d)){
		  p++; 
		  swap(tree[p], tree[i]); 
		}
	}
		  
    swap(tree[lo], tree[p]);
    return p;
	
}


/**
 * Helper function to help determine if the nearest neighbor could 
 * be on the other side of the KD tree.
 */
int rgbtree::distToSplit(const RGBAPixel& query, const RGBAPixel& curr, int dimension) const
{
	switch (dimension) {
		case 0:
			return ((int)query.r - (int)curr.r) * ((int)query.r - (int)curr.r);
		case 1:
			return ((int)query.g - (int)curr.g) * ((int)query.g - (int)curr.g);
		case 2:
			return ((int)query.b - (int)curr.b) * ((int)query.b - (int)curr.b);
	}

	return 0;

}

