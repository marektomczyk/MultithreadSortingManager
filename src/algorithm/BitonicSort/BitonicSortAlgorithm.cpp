//============================================================================
// Name        : BitonicSort.cpp
// Author      : Marek Tomczyk
// Version     : 1.0
// Copyright   : Copyright (C) 2019 Marek Tomczyk. All rights reserved.
// Description : Bitonic sort algorithm source file
//============================================================================

#include "BitonicSortAlgorithm.h"
#include "../../tools/ToolSet.h"
#include "../../timer/Timer.h"
#include "../../log/Logger.h"

/*****************************************************************************
 *	@brief Sort given chunk of data and write it to new file
 *
 *	@param chunk - data to sort
 *	@param chunkCount - number of sorting chunk
 *
 *	@return None
 ****************************************************************************/
void BitonicSortAlgorithm::Sort(
	std::vector<int>* chunk, unsigned int chunkCount)
{
	if ( ( chunk != nullptr ) && ( !chunk->empty() ) )
	{
		LOG_TRACE("Sorting stared");

		Timer::TimeRecord record;
		bSort(*chunk, 0, chunk->size(), true);
		record.Stop();
		Timer::AddRecord(record);

		LOG_TRACE("Finished sorting");
		ToolSet::WriteChunkIntoFile(*chunk, chunkCount);
	}

	delete chunk;
}

/*****************************************************************************
 *	@brief Bitonic sort algorithm implementation
 *
 *	@param dataToSort - vector of data to sort
 *	@param low - 
 *	@param size - size of vector
 *	@param asc - true when ascending / false when descending sort
 *
 *	@return None
 ****************************************************************************/
void BitonicSortAlgorithm::bSort(
	std::vector<int>& chunk, int low, std::size_t size, bool asc)
{
	if ( size > 1 )
	{
		int pivot = size / 2;
		bSort(chunk, low, pivot, true);
		bSort(chunk, low + pivot, pivot, false);
		bMerge(chunk, low, size, asc);
	}
}


/*****************************************************************************
 *	@brief Bitonic merge
 *
 *	@param dataToSort - vector of data to sort
 *	@param low -
 *	@param size - size of vector
 *	@param asc - true when ascending / false when descending sort
 *
 *	@return None
 ****************************************************************************/
void BitonicSortAlgorithm::bMerge(
	std::vector<int>& chunk, int low, std::size_t size, bool asc)
{
	if ( size > 1 )
	{
		int pivot = size / 2;
		for ( int i = low; i < low + pivot; i++ )
		{
			if ( asc == (chunk[i] > chunk[i + pivot]) )
				std::swap(chunk[i], chunk[i + pivot]);
		}
		bMerge(chunk, low, pivot, asc);
		bMerge(chunk, low + pivot, pivot, asc);
	}
}
//----------------------------------------------------------------------------
// End of file ---------------------------------------------------------------
//----------------------------------------------------------------------------