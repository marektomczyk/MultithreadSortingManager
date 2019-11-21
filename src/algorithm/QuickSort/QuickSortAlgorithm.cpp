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
void QuickSortAlgorithm::Sort(std::vector<std::byte>* chunk, unsigned int chunkCount)
{
	if ( ( chunk != nullptr ) && ( !chunk->empty() ) )
	{
		Timer::TimeRecord record;
		//qSort(*chunk, 0, chunk->size() - 1);
		record.Stop();
		Timer::AddRecord(record);

		//ToolSet::WriteChunkIntoFile(*chunk, chunkCount);
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
void QuickSortAlgorithm::qSort(std::vector<int>& dataToSort, int left, int right)
{
	if ( left < right )
	{
		int pivotIndex = partition(dataToSort, left, right);
		qSort(dataToSort, left, pivotIndex - 1);
		qSort(dataToSort, pivotIndex, right);
	}
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
int QuickSortAlgorithm::partition(std::vector<int>& dataToSort, int left, int right)
{
	int pivotIndex = left + (right - left) / 2;
	int pivotValue = dataToSort[pivotIndex];
	int tmp;

	while ( left <= right )
	{
		while ( dataToSort[left] < pivotValue )
			left++;
		while ( dataToSort[right] > pivotValue )
			right--;

		if ( left <= right )
		{
			tmp = dataToSort[left];
			dataToSort[left] = dataToSort[right];
			dataToSort[right] = tmp;
			left++;
			right--;
		}
	}

	return left;
}
//----------------------------------------------------------------------------
// End of file ---------------------------------------------------------------
//----------------------------------------------------------------------------