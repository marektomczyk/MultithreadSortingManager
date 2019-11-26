//============================================================================
// Name        : BitonicSort.h
// Author      : Marek Tomczyk
// Version     : 1.0
// Copyright   : Copyright (C) 2019 Marek Tomczyk. All rights reserved.
// Description : Bitonic sort algorithm header file
//============================================================================

#ifndef _ALGORITHM_BITONICSORTALGORITHM_H_
#define _ALGORITHM_BITONICSORTALGORITHM_H_

#include "../SortAlgorithmBase.h"

class BitonicSortAlgorithm : public SortAlgorithmBase
{
public:
	/// @brief Class default constructor
	BitonicSortAlgorithm()
		: SortAlgorithmBase("BitonicSort") { }
	/// @brief Class destructor
	~BitonicSortAlgorithm() = default;
	/// @brief Sort method
	void Sort(std::vector<std::byte>* chunk, unsigned int chunkCount) final;

private:
	/// @brief Bitonic sort algorithm implementation
	void bSort(std::vector<int>& chunk, int low, std::size_t size, bool asc);
	/// @brief Bitonic merge
	void bMerge(std::vector<int>& chunk, int low, std::size_t size, bool asc);
};

#endif /* _ALGORITHM_BITONICSORTALGORITHM_H_ */

//----------------------------------------------------------------------------
// End of file ---------------------------------------------------------------
//----------------------------------------------------------------------------