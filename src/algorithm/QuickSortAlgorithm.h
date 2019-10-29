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
#include "SortAlgorithmBase.h"

class QuickSortAlgorithm : public SortAlgorithmBase
{
public:
	/// @brief Class constructor
	QuickSortAlgorithm()
		: SortAlgorithmBase("QuickSort") { }

	/// @brief Sort method
	void Sort(const char * chunk, unsigned int chunkCount) final;

	/// @brief Class destructor
	~QuickSortAlgorithm() = default;

private:
	/// @brief Quick sort method
	void qSort(std::vector<int> &dataToSort, int low, int high);
	/// @brief Partition data for sorting
	const int partition(std::vector<int> &dataToSort, int low, int high);
};

#endif /* ALGORITHM_QUICKSORTALGORITHM_H_ */
