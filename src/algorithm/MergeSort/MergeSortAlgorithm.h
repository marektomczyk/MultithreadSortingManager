//============================================================================
// Name        : MergeSortAlgorithm.h
// Author      : Marek Tomczyk
// Version     : 1.0
// Copyright   : Copyright (C) 2019 Marek Tomczyk. All rights reserved.
// Description : Merge sort algorithm header file
//============================================================================

#ifndef _ALGORITHM_MERGESORTALGORITHM_H_
#define _ALGORITHM_MERGESORTALGORITHM_H_

#include <algorithm>
#include "../SortAlgorithmBase.h"

class MergeSortAlgorithm : public SortAlgorithmBase
{
public:
	/// @brief Class constructor
	MergeSortAlgorithm()
		: SortAlgorithmBase("MergeSort") { }
	/// @brief Class destructor
	~MergeSortAlgorithm() = default;
	/// @brief Sort method
	void Sort(std::vector<int> * chunk, unsigned int chunkCount) final;

private:
	/// @brief Merge sort method
	void mSort(std::vector<int>::iterator first, std::vector<int>::iterator last);
};

#endif

//----------------------------------------------------------------------------
// End of file ---------------------------------------------------------------
//----------------------------------------------------------------------------