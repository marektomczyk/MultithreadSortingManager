//============================================================================
// Name        : MergeSortAlgorithm.cpp
// Author      : Marek Tomczyk
// Version     : 1.0
// Copyright   : Copyright (C) 2019 Marek Tomczyk. All rights reserved.
// Description : Merge sort algorithm source file
//============================================================================

#include "MergeSortAlgorithm.h"
#include "../../tools/ToolSet.h"
#include "../../timer/Timer.h"
#include "../../log/Logger.h"
#include <algorithm>

/*****************************************************************************
 *	@brief Sort given chunk of data and write it to new file
 *
 *	@param chunk - data to sort
 *	@param chunkCount - number of sorting chunk
 *
 *	@return None
 ****************************************************************************/
void MergeSortAlgorithm::Sort(
	std::vector<int>* chunk, unsigned int chunkCount)
{
	if ( ( chunk != nullptr ) && ( !chunk->empty() ) )
	{
		LOG_TRACE("Sorting stared");

		Timer::TimeRecord record;
		mSort(chunk->begin(), chunk->end());
		record.Stop();
		Timer::AddRecord(record);

		LOG_TRACE("Finished sorting");
		ToolSet::WriteChunkIntoFile(*chunk, chunkCount);
	}

	delete chunk;
}

/*****************************************************************************
 *	@brief Merge sort algorithm implementation
 *
 *	@param dataToSort - vector of data to sort
 *	@param left - left index of the sub-vector of vector to be sorted
 *	@param right - right index of the sub-vector of vector to be sorted
 *
 *	@return None
 ****************************************************************************/
void MergeSortAlgorithm::mSort(
	std::vector<int>::iterator first, std::vector<int>::iterator last)
{
	if ( last - first > 1 ) 
	{
		auto middle = first + ( last - first ) / 2;
		mSort(first, middle);
		mSort(middle, last);
		std::inplace_merge(first, middle, last);
	}
}

//----------------------------------------------------------------------------
// End of file ---------------------------------------------------------------
//----------------------------------------------------------------------------