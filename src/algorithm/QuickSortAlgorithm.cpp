//============================================================================
// Name        : QuickSortAlgorithm.h
// Author      : Marek Tomczyk
// Version     : 1.0
// Copyright   : Copyright (C) 2019 Marek Tomczyk. All rights reserved.
// Description : Quick sort algorithm source file
//============================================================================

#include "QuickSortAlgorithm.h"
#include <thread> // delete
#include <iostream> // delete

void QuickSortAlgorithm::Sort(const char * dataToSort, unsigned int chunkCount)
{
	std::cout << "ThreadID: " << std::this_thread::get_id() << " Sort algorithm: " << GetName() << std::endl; //delete
	//qSort(dataToSort, 0, std::strlen(dataToSort));
	std::this_thread::sleep_for(std::chrono::seconds(5));

	delete [] dataToSort;
	dataToSort = nullptr;
}

void QuickSortAlgorithm::qSort(std::vector<int> &dataToSort, int low, int high)
{
	if( low < high )
	{
		// TODO: logging
		return;
	}

	int pivot = partition(dataToSort, low, high);
	qSort(dataToSort, low, pivot - 1);
	qSort(dataToSort, pivot + 1, high);
}

const int QuickSortAlgorithm::partition(std::vector<int> &dataToSort, int low, int high)
{
  int left=low;
  int right=high;
  int v= dataToSort[left];

  while( left < right )
  {
      while( dataToSort[left] <= v)
      	left++;
      while( dataToSort[right] > v)
      	right--;

      if (left < right)
      {
      	std::swap(dataToSort[left], dataToSort[right]);
      }
  }

  std::swap(dataToSort[left], dataToSort[right]);
  return right;
}
