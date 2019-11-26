//============================================================================
// Name        : QuickSortAlgorithm.h
// Author      : Marek Tomczyk
// Version     : 1.0
// Copyright   : Copyright (C) 2019 Marek Tomczyk. All rights reserved.
// Description : Quick sort algorithm header file
//============================================================================
#ifndef _ALGORITHM_QUICKSORTALGORITHM_H_
#define _ALGORITHM_QUICKSORTALGORITHM_H_

#include <algorithm>
#include "../SortAlgorithmBase.h"

class QuickSortAlgorithm : public SortAlgorithmBase
{
public:
	/// @brief Class constructor
	QuickSortAlgorithm()
		: SortAlgorithmBase("QuickSort") { }
	/// @brief Class destructor
	~QuickSortAlgorithm() = default;
	/// @brief Sort method
	void Sort(std::vector<std::byte>* chunk, unsigned int chunkCount) final;

private:
	/// @brief Quick sort method
	void qSort(std::vector<int>& dataToSort, int left, int right);
	/// @brief Partition data for sorting
	int partition(std::vector<int>& dataToSort, int left, int right);
};

#endif /* ALGORITHM_QUICKSORTALGORITHM_H_ */

//----------------------------------------------------------------------------
// End of file ---------------------------------------------------------------
//----------------------------------------------------------------------------