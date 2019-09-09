//============================================================================
// Name        : QuickSortAlgorithm.h
// Author      : Marek Tomczyk
// Version     : 1.0
// Copyright   : Copyright (C) 2019 Marek Tomczyk. All rights reserved.
// Description : Quick sort algorithm header file
//============================================================================
#ifndef _ALGORITHM_QUICKSORTALGORITHM_H_
#define _ALGORITHM_QUICKSORTALGORITHM_H_

#include "AlgorithmBase.h"
#include <algorithm>

class QuickSortAlgorithm : public AlgorithmBase
{
public:
	/// @brief Class constructor
	QuickSortAlgorithm()
		: AlgorithmBase("QuickSort") { }

	/// @brief Sort method
	virtual void Sort(const char * dataToSort, unsigned int chunkCount) override final;

	/// @brief Class destructor
	~QuickSortAlgorithm() = default;

private:
	/// @brief Quick sort method
	void qSort(std::vector<int> &dataToSort, int low, int high);
	/// @brief Partition data for sorting
	const int partition(std::vector<int> &dataToSort, int low, int high);
};

#endif /* ALGORITHM_QUICKSORTALGORITHM_H_ */
