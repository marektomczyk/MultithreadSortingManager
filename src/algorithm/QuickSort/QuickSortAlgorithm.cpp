//============================================================================
// Name        : QuickSortAlgorithm.h
// Author      : Marek Tomczyk
// Version     : 1.0
// Copyright   : Copyright (C) 2019 Marek Tomczyk. All rights reserved.
// Description : Quick sort algorithm source file
//============================================================================

#include "QuickSortAlgorithm.h"
#include "../../tools/ToolSet.h"
#include "../../timer/Timer.h"

/*****************************************************************************
 *	@brief Sort given chunk of data and write it to new file
 *
 *	@param chunk - data to sort
 *	@param chunkCount - number of sorting chunk
 *
 *	@return None
 ****************************************************************************/
void QuickSortAlgorithm::Sort(std::vector<int>* chunk, unsigned int chunkCount)
{
	if ((chunk != nullptr) && (!chunk->empty()))
	{
		Timer::TimeRecord record;
		qSort(*chunk, 0, chunk->size());
		record.Stop();
		Timer::AddRecord(record);

		ToolSet::WriteChunkIntoFile(*chunk, chunkCount);
	}

	delete chunk;
}

/*****************************************************************************
 *	@brief Quicksort algorithm implementation
 *
 *	@param dataToSort - vector of data to sort
 *	@param low -
 *	@param high -
 *
 *	@return None
 ****************************************************************************/
void QuickSortAlgorithm::qSort(std::vector<int>& dataToSort, int low, int high)
{
	if (low < high)
	{
		return;
	}

	int pivot = partition(dataToSort, low, high);
	qSort(dataToSort, low, pivot - 1);
	qSort(dataToSort, pivot + 1, high);
}

/*****************************************************************************
 *	@brief Partition data to sort
 *
 *	@param dataToSort - vector of data to sort
 *	@param low -
 *	@param high -
 *
 *	@return Pivot
 ****************************************************************************/
const int QuickSortAlgorithm::partition(std::vector<int>& dataToSort, int low, int high)
{
	int left = low;
	int right = high;
	int v = dataToSort[left];

	while (left < right)
	{
		while (dataToSort[left] <= v)
			left++;
		while (dataToSort[right] > v)
			right--;

		if (left < right)
		{
			std::swap(dataToSort[left], dataToSort[right]);
		}
	}

	std::swap(dataToSort[left], dataToSort[right]);
	return right;
}
//----------------------------------------------------------------------------
// End of file ---------------------------------------------------------------
//----------------------------------------------------------------------------